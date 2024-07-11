/*
 * API_PN532.c
 *
 *  Created on: Jul 6, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_PN532.h"
#include "API_PN532_HAL.h"

/*----------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

static const uint8_t ACKNOLEDGE[]          = {0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00};
static const uint8_t FIRMWARE[]            = {0x00, 0x00, 0xFF, 0x02, 0xFE, 0xD4, 0x02, 0x2A, 0x00};
static const uint8_t INlISTpASSIVEtARGET[] = {0x00, 0x00, 0xFF, 0x04, 0XFC, 0XD4, 0x4A, 0x01, 0x00, 0xE1, 0x00};

#define MAXrESPONSEsIZE 64
#define ACKsIZE          6

/*----------------------------------------------------------------------------*/


/* Private types -------------------------------------------------------------*/

typedef struct
{
  uint8_t uid[MAXUIDsIZE];
  uint8_t size;
} PN532_Tag_t;

typedef struct
{
  uint8_t ic;
  uint8_t version;
  uint8_t revision;
  uint8_t support;
} PN532_Firmware_t;

struct PN532_s
{
  PN532_Tag_t tag;
  PN532_Firmware_t firmware;
};

typedef struct
{
  uint8_t preamble[2]; //PreAmble
  uint8_t len;         //Length
  uint8_t lcs;          //Length CheckSum
  uint8_t tfi;         //Frame Identifier
  uint8_t pd0;         //0x03
  uint8_t ic;          //0x32
  uint8_t version;     //0x01
  uint8_t revision;    //0x06
  uint8_t support;     //0x07
  uint8_t dcs;         //Data CheckSum
  uint8_t postamble;   //PostAmble
} PN532_Firmware_Response_t;

typedef struct
{
  uint8_t preamble[2]; //PreAmble
  uint8_t len;         //Length
  uint8_t lcs;         //Length CheckSum
  uint8_t tfi;         //Frame Identifier

  uint8_t dcs;         //Data CheckSum
  uint8_t postamble;   //PostAmble
} PN532_Tag_Response_t;

/*----------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

static PN532_Error_t API_PN532_SendCommand(uint8_t *command, const uint8_t size);
static PN532_Error_t API_PN532_ReceiveAck(void);
static PN532_Error_t API_PN532_ReceiveResponse(uint8_t *response, uint8_t size);

/*----------------------------------------------------------------------------*/

/* API code ------------------------------------------------------------------*/

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
uint8_t API_PN532_GetTag(PN532_t instance, uint8_t *uid, const uint8_t size)
{
  if(size >= instance->tag.size)
	memcpy(uid, &instance->tag.uid, instance->tag.size);

  return instance->tag.size;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
uint8_t API_PN532_GetIC(PN532_t instance)
{
  return instance->firmware.ic;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
uint8_t API_PN532_GetVersion(PN532_t instance)
{
  return instance->firmware.version;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
uint8_t API_PN532_GetRevision(PN532_t instance)
{
  return instance->firmware.revision;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
uint8_t API_PN532_GetSupport(PN532_t instance)
{
  return instance->firmware.support;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
PN532_t API_PN532_Init()
{
  static struct PN532_s this = {0};

  uint8_t response[MAXrESPONSEsIZE] = {0};
  PN532_Firmware_Response_t tmp = {0};

  if(PN532oK == API_PN532_SendCommand((uint8_t *)FIRMWARE, sizeof(FIRMWARE)))
  {
    API_PN532_HAL_Delay(10);
    if(PN532oK == API_PN532_ReceiveAck())
    {
      API_PN532_HAL_Delay(10);
      if(PN532oK == API_PN532_ReceiveResponse((uint8_t *)response, sizeof(response)))
      {
		memcpy(&tmp, &response[1], sizeof(PN532_Firmware_Response_t));
		
		this.firmware.ic       = tmp.ic;
		this.firmware.version  = tmp.version;
		this.firmware.revision = tmp.revision;
        this.firmware.support  = tmp.support;
		
	  }
    }
  }
  return &this;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
PN532_Error_t API_PN532_ReadTag(PN532_t instance)
{
  uint8_t response[MAXrESPONSEsIZE] = {0};
  PN532_Tag_Response_t tmp = {0};

  if(PN532oK == API_PN532_SendCommand((uint8_t *)INlISTpASSIVEtARGET, sizeof(INlISTpASSIVEtARGET)))
  {
    API_PN532_HAL_Delay(10);
    if(PN532oK == API_PN532_ReceiveAck())
    {
      API_PN532_HAL_Delay(10);
      if(PN532oK == API_PN532_ReceiveResponse((uint8_t *)response, sizeof(response)))
      {
		memcpy(&tmp, &response[1], sizeof(PN532_Tag_Response_t));

       //TODO: Copy response array to instance->tag.uid and size structure

	  }
    }
  }
  return PN532oK;
}

/*----------------------------------------------------------------------------*/

/* Private API code ----------------------------------------------------------*/

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
static PN532_Error_t API_PN532_SendCommand(uint8_t *command, const uint8_t size)
{
	return API_PN532_HAL_I2C_Write(PN532aDDRESS, command, size)? PN532oK : PN532bADcOMMAND;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
static PN532_Error_t API_PN532_ReceiveAck(void)
{
  uint8_t acknowledge[ACKsIZE] = {0};
  
  if(!API_PN532_HAL_I2C_Read(PN532aDDRESS, acknowledge, ACKsIZE))
  {
    return PN532bADrESPONSE;
  }
  
  if(!memcmp(acknowledge, ACKNOLEDGE, sizeof(ACKNOLEDGE)))
  {
    return PN532bADaCK;
  }
  
  return PN532oK;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
static PN532_Error_t API_PN532_ReceiveResponse(uint8_t *response, uint8_t size)
{
  return API_PN532_HAL_I2C_Read(PN532aDDRESS, response, size) ? PN532oK : PN532bADrESPONSE;
}

/*----------------------------------------------------------------------------*/
