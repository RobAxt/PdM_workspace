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

const uint8_t WAKEUPcMD[] = {0x55, 0x55, 0x00, 0x00};

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

}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
int8_t API_PN532_ReadTag(tag_t tag)
{

}
