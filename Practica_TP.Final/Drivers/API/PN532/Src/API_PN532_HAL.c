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
  * @brief  Encapsulates the hardware specific call to a blocking delay
  * @param  uint32_t delay: delay in miliseconds.
  * @retval None.
  */
void API_PN532_HAL_Delay(uint32_t delay)
{
  HAL_Delay(delay);
}

/**
  * @brief  Encapsulates the hardware specific call to the I2C Master Transmit
  * @param  uint8_t address: address of the I2C device.
  * @param  uint8_t *query: pointer to the allocated buffer with the correct size.
  * @param  uint16_t querySize: size of bytes to write.
  * @retval bool_t: returns true if the query was sent, otherwaise false
  */
bool_t API_PN532_HAL_I2C_Write(uint8_t address, uint8_t *query, uint16_t querySize)
{
  if(HAL_I2C_Master_Transmit(&hi2c1, address<<1, query, querySize, TIMEOUT)==HAL_OK)
    return true;v
  else
	return false;
}

/**
  * @brief  Encapsulates the hardware specific call to the I2C Master Read
  * @param  uint8_t address: address of the I2C device.
  * @param  uint8_t *response: pointer to the allocated buffer with the correct size.
  * @param  uint16_t responseSize: size of bytes to read.
  * @retval bool_t: returns true if the query was sent, otherwaise false
  */
bool_t API_PN532_HAL_I2C_Read(uint8_t address, uint8_t *response, uint16_t responseSize)
{
  if(HAL_I2C_Master_Receive(&hi2c1, address<<1, response, responseSize, TIMEOUT)==HAL_OK)
    return true;
  else
	return false;
}


/*----------------------------------------------------------------------------*/
