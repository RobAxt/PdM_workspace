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

static const uint8_t PREAMBLEsTART[]       = {0x00, 0x00, 0xFF};
static const uint8_t ACKNOLEDGE[]          = {0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00};
static const uint8_t FIRMWARE[]            = {0x00, 0x00, 0xFF, 0x02, 0xFE, 0xD4, 0x02, 0x2A, 0x00};
static const uint8_t SAMCONFIG[]           = {0x00, 0x00, 0xFF, 0x03, 0xFD, 0xD4, 0x14, 0x01, 0x17, 0x00};
static const uint8_t INlISTpASSIVEtARGET[] = {0x00, 0x00, 0xFF, 0x04, 0XFC, 0XD4, 0x4A, 0x01, 0x00, 0xE1, 0x00};

#define MAXrESPONSEsIZE 32
#define NOtAGpRESENT   128
#define ACKsIZE          6
#define ZERO             0

/*----------------------------------------------------------------------------*/


/* Private types -------------------------------------------------------------*/

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
  uint8_t preamble;    //PreAmble
  uint8_t start[2];    //Start of Packet Code
  uint8_t len;         //Length
  uint8_t lcs;         //Length CheckSum
  uint8_t tfi;         //Frame Identifier
  uint8_t cmd;         //0x03
  uint8_t ic;          //0x32
  uint8_t version;     //0x01
  uint8_t revision;    //0x06
  uint8_t support;     //0x07
  uint8_t dcs;         //Data CheckSum
  uint8_t postamble;   //PostAmble
} PN532_Firmware_Response_t;

typedef struct
{
  uint8_t preamble;    //PreAmble
  uint8_t start[2];    //Start of Packet Code
  uint8_t len;         //Length
  uint8_t lcs;         //Length CheckSum
  uint8_t tfi;         //Frame Identifier
  uint8_t cmd;         //0x4B
  uint8_t nbtg;        //Number of Tag Readed
  uint8_t index;       //Tag index
  uint8_t pd3;
  uint8_t pd4;
  uint8_t pd5;
  uint8_t size;         //Tag size
  uint8_t tag0;
  uint8_t tag1;
  uint8_t tag2;
  uint8_t tag3;
  uint8_t dcs;         //Data CheckSum
  uint8_t postamble;   //PostAmble
} PN532_Tag_Response_t;

/*----------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

static PN532_Error_t API_PN532_SendCommand(uint8_t *command, const uint8_t size);
static PN532_Error_t API_PN532_ReceiveAck(void);
static PN532_Error_t API_PN532_ReceiveResponse(uint8_t *response, uint8_t size);
static PN532_Error_t API_PN532_Transaction(uint8_t *command, size_t commandSize, uint8_t *response, size_t responseSize);

/*----------------------------------------------------------------------------*/

/* API code ------------------------------------------------------------------*/

/**
  * @brief  function to retrieve the current tad readed
  * @param  PN532_t instance: pointer to the hidden structure.
  * @param  uint8_t *uid: poiter to the allocated array that will contain the tad uid
  * @param  const uint8_t size: the size of the tag uid
  * @retval uint8_t: if ok, return the size of the uid tag; otherwise, it indicates that
  *                  the instance was not initialized.

  */
uint8_t API_PN532_GetTag(PN532_t instance, uint8_t *uid, const uint8_t size)
{
  if(NULL != instance)
  {
    if(size >= instance->tag.size)
      memcpy(uid, &instance->tag.uid, instance->tag.size);
    return instance->tag.size;
  }
  return NOTiNITIALIZED;
}

/**
  * @brief  Get the IC version
  * @param  PN532_t instance: pointer to the hidden structure.
  * @retval uint8_t: return IC version if ok; otherwise it will indicate that the instance was
  *                  not initialized..
  */
uint8_t API_PN532_GetIC(PN532_t instance)
{
  if(NULL != instance)
  {
    return instance->firmware.ic;
  }
  return NOTiNITIALIZED;
}

/**
  * @brief  Get the firmware version
  * @param  PN532_t instance: pointer to the hidden structure.
  * @retval uint8_t: return firmware version if ok; otherwise it will indicate that the instance was
  *                  not initialized..
  */
uint8_t API_PN532_GetVersion(PN532_t instance)
{
  if(NULL != instance)
  {
    return instance->firmware.version;
  }
  return NOTiNITIALIZED;
}

/**
  * @brief  Get the IC revision
  * @param  PN532_t instance: pointer to the hidden structure.
  * @retval uint8_t: return IC revision if ok; otherwise it will indicate that the instance was
  *                  not initialized..
  */
uint8_t API_PN532_GetRevision(PN532_t instance)
{
  if(NULL != instance)
  {
    return instance->firmware.revision;
  }
  return NOTiNITIALIZED;
}

/**
  * @brief  Get the type of tags supported
  * @param  PN532_t instance: pointer to the hidden structure.
  * @retval uint8_t: return the type of tags supported if ok; otherwise it will indicate
  *                  that the instance was not initialized..
  */
uint8_t API_PN532_GetSupport(PN532_t instance)
{
  if(NULL != instance)
  {
    return instance->firmware.support;
  }
  return NOTiNITIALIZED;
}

/**
  * @brief  Initialize the elements of the structure and send the SAM Config
  *         command to the PN532 to enable the reading of the tags.
  * @param  None
  * @retval PN532_t: returns the pointer to the hidden structure
  */
PN532_t API_PN532_Init(void)
{
  static struct PN532_s this = {0};

  uint8_t response[MAXrESPONSEsIZE] = {0};
  PN532_Firmware_Response_t tmp = {0};

  // Send FIRMWARE command
  if(PN532oK == API_PN532_Transaction((uint8_t *)FIRMWARE, sizeof(FIRMWARE), (uint8_t *)response, MAXrESPONSEsIZE))
  {
    //Looking for the beginning of the frame, the first byte used to be garbage and we have to find the correct alignment using the preamble bytes.
    uint8_t offset=0;
    while(memcmp(&response[offset], PREAMBLEsTART, sizeof(PREAMBLEsTART)) && offset < (sizeof(PN532_Firmware_Response_t)-sizeof(PREAMBLEsTART)))
      offset++;
    //Once the correct alignment is found, we can store the received bytes in the structure for easy decode.
    memcpy(&tmp, &response[offset], sizeof(PN532_Firmware_Response_t));
		
		this.firmware.ic       = tmp.ic;
		this.firmware.version  = tmp.version;
		this.firmware.revision = tmp.revision;
    this.firmware.support  = tmp.support;
  }

  memset(response, ZERO, sizeof(response));

  // Send SAMCONFIG command
  if(PN532oK != API_PN532_Transaction((uint8_t *)SAMCONFIG, sizeof(SAMCONFIG),(uint8_t *)response, sizeof(response)))
  {
    memset(&this, ZERO, sizeof(this));
    return NULL;
  }

  return &this;
}

/**
  * @brief  Read the UID of the Tag if it is present.
  * @param  PN532_t instance: pointer to the hidden structure.
  * @retval PN532_Error_t: enum that indicates the status of the transaction with the PN532.
  */
PN532_Error_t API_PN532_ReadTag(PN532_t instance)
{
  uint8_t response[MAXrESPONSEsIZE] = {0};
  PN532_Tag_Response_t tmp = {0};
  PN532_Error_t result = PN532nOTiNITIALIZED;

  if(NULL == instance)
  {
      return result;
  }

  result = API_PN532_Transaction((uint8_t *)INlISTpASSIVEtARGET, sizeof(INlISTpASSIVEtARGET), (uint8_t *)response, MAXrESPONSEsIZE);

  if(PN532oK == result)
  {
    if(NOtAGpRESENT != response[1])
    {
      //Looking for the beginning of the frame, the first byte used to be garbage and we have to find the correct alignment using the preamble bytes.
      uint8_t offset=0;
      while(memcmp(&response[offset], PREAMBLEsTART, sizeof(PREAMBLEsTART)) && offset < (sizeof(PN532_Tag_Response_t)-sizeof(PREAMBLEsTART)))
        offset++;
      //Once the correct alignment is found, we can store the received bytes in the structure for easy decode.
		  memcpy(&tmp, &response[offset], sizeof(PN532_Tag_Response_t));

		  //TODO: generic tag uid size...
      instance->tag.size   = tmp.size;
      instance->tag.uid[0] = tmp.tag0;
      instance->tag.uid[1] = tmp.tag1;
      instance->tag.uid[2] = tmp.tag2;
      instance->tag.uid[3] = tmp.tag3;

      result = PN532oK;
    }
    else
    {
      memset(&instance->tag, ZERO, sizeof(instance->tag));
      result = PN532nOtAG;
    }
  }

  return result;
}

/*----------------------------------------------------------------------------*/

/* Private API code ----------------------------------------------------------*/

/**
  * @brief  Encapsulated the writing of a command frame.
  * @param  uint8_t *command: pointer to the allocated buffer with the correct size.
  * @param  uint8_t size: size of the stored buffer.
  * @retval PN532_Error_t: enum that indicates the status of the transaction with the PN532.
  */
static PN532_Error_t API_PN532_SendCommand(uint8_t *command, const uint8_t size)
{
	return API_PN532_HAL_I2C_Write(PN532aDDRESS, command, size)? PN532oK : PN532bADcOMMAND;
}

/**
  * @brief  Validates that the frame received is a correct acknowledge.
  * @param  None.
  * @retval PN532_Error_t: enum that indicates the status of the transaction with the PN532.
  */
static PN532_Error_t API_PN532_ReceiveAck(void)
{
  uint8_t acknowledge[ACKsIZE+1] = {0};
  
  if(!API_PN532_HAL_I2C_Read(PN532aDDRESS, acknowledge, ACKsIZE))
  {
    return PN532bADrESPONSE;
  }
  //Looking for the beginning of the frame, the first byte used to be garbage and we have to find the correct alignment using the preamble bytes.
  uint8_t offset=0;
  while(memcmp(&acknowledge[offset], PREAMBLEsTART, sizeof(PREAMBLEsTART)) && offset < (sizeof(ACKNOLEDGE)-sizeof(PREAMBLEsTART)))
    offset++;
  //Once the correct alignment is found, we can check that the bytes received are the same as those of the acknowledgment frame.
  if(memcmp(&acknowledge[offset], ACKNOLEDGE, sizeof(ACKNOLEDGE)))
  {
    return PN532bADaCK;
  }
  
  return PN532oK;
}

/**
  * @brief  Encapsulated the reading of a response frame.
  * @param  uint8_t *response: pointer to the allocated buffer with the correct size.
  * @param  uint8_t size: size of the stored buffer.
  * @retval PN532_Error_t: enum that indicates the status of the transaction with the PN532.
  */
static PN532_Error_t API_PN532_ReceiveResponse(uint8_t *response, uint8_t size)
{
  return API_PN532_HAL_I2C_Read(PN532aDDRESS, response, size) ? PN532oK : PN532bADrESPONSE;
}

/**
  * @brief  Implements the logic transaction.
  * @param  uint8_t *command: pointer to the allocated buffer with the correct size.
  * @param  uint8_t commandSize: size of the stored buffer.
  * @param  uint8_t *response: pointer to the allocated buffer with the correct size.
  * @param  uint8_t responseSize: size of the stored buffer.
  * @retval PN532_Error_t: enum that indicates the status of the transaction with the PN532.
  */
static PN532_Error_t API_PN532_Transaction(uint8_t *command, size_t commandSize, uint8_t *response, size_t responseSize)
{
  if(NULL != command && NULL != response && ZERO < commandSize && MAXrESPONSEsIZE >= responseSize)
  {
    if(PN532oK == API_PN532_SendCommand(command, commandSize))
     {
       API_PN532_HAL_Delay(10);
       if (PN532oK == API_PN532_ReceiveAck())
       {
         API_PN532_HAL_Delay(50);
         if(PN532oK == API_PN532_ReceiveResponse(response, responseSize))
         {
           return PN532oK;
         }
         return PN532bADrESPONSE;
       }
       return PN532bADaCK;
     }
    return PN532bADcOMMAND;
  }
  return PN532nOTiNITIALIZED;
}
/*----------------------------------------------------------------------------*/
