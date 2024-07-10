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

static const uint8_t WAKEUPcMD[] = {0x55, 0x55, 0x00, 0x00};
static const uint8_t FIRMWARE[]  = {0x00, 0x00, 0xFF, 0x02, 0xFE, 0xD4, 0x02, 0x2A, 0x00};
static const uint8_t CONFIGSAM[] = {0x00, 0x00, 0xFF, 0x03, 0xFD, 0xD4, 0x14, 0x01, 0x17, 0x00};
static const uint8_t INlISTpASSIVEtARGET[] = {0x00, 0x00, 0xFF, 0x04, 0XFC, 0XD4, 0x4A, 0x01, 0x00, 0xE1, 0x00};

/*----------------------------------------------------------------------------*/


/* Private types -------------------------------------------------------------*/

struct tag_s
{
  uint8_t UId[MAXUIDsIZE];
  uint8_t size;
};

/*----------------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

struct tag_s currentTag = {0};

/*----------------------------------------------------------------------------*/

/* API code ------------------------------------------------------------------*/

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
int8_t API_PN532_GetTag(tag_t tag, uint8_t *UId, const uint8_t size)
{
  if(size >= tag->size)
	memcpy(UId, tag->UId, tag->size);
  else
	return APIpN532eRROR;
  return tag->size;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
void API_PN532_SetTag(tag_t tag, const uint8_t * const UId, const uint8_t size)
{
  if(MAXUIDsIZE >= size)
	memcpy(tag->UId, UId, tag->size);
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
void API_PN532_Init(tag_t tag)
{
//  API_PN532_HAL_I2C_Write(PN532aDDRESS, WAKEUPcMD, sizeof(WAKEUPcMD)/sizeof(uint8_t));

  uint8_t response[64] = {0};

  API_PN532_HAL_I2C_Write(PN532aDDRESS, FIRMWARE, sizeof(FIRMWARE)/sizeof(uint8_t));
  API_PN532_HAL_Delay(10);
  API_PN532_HAL_I2C_Read(PN532aDDRESS, response,7);
  API_PN532_HAL_Delay(10);
  API_PN532_HAL_I2C_Read(PN532aDDRESS, response, 13);

  for(uint8_t i=0; i<=13; i++)
    printf(" %02X", response[i]);
  printf("\r\n");
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
int8_t API_PN532_ReadTag(tag_t tag)
{
  return 7;
}
