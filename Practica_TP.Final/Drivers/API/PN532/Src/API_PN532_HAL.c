/*
 * API_PN532_HAL.c
 *
 *  Created on: Jul 6, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_PN532_HAL.h"

/*----------------------------------------------------------------------------*/

/* Extern public variables----------------------------------------------------*/

extern I2C_HandleTypeDef hi2c1;

/*----------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define TIMEOUT 500

/*----------------------------------------------------------------------------*/

/* Hardware Specific API code ------------------------------------------------*/

/**
  * @brief  ...
  * @param  delay: ...
  * @retval None.
  */
void API_PN532_HAL_Delay(uint32_t delay)
{
  HAL_Delay(delay);
}

/**
  * @brief  ...
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  payload: ...
  * @retval None.
  */
bool API_PN532_HAL_I2C_Write(uint8_t address, uint8_t *query, uint16_t querySize)
{
  if(HAL_I2C_Master_Transmit(&hi2c1, address<<1, query, querySize, TIMEOUT)==HAL_OK)
    return true;
  else
	return false;
}



bool API_PN532_HAL_I2C_Read(uint8_t address, uint8_t *response, uint16_t responseSize)
{
  if(HAL_I2C_Master_Receive(&hi2c1, address<<1, response, responseSize, TIMEOUT)==HAL_OK)
    return true;
  else
	return false;
}


/*----------------------------------------------------------------------------*/
