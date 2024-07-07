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

extern I2C_HandleTypeDef hi2c2;

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
  * @param  address: ...
  * @param  payload: ...
  * @retval None.
  */
void API_PN532_HAL_I2C_QueryResponse(uint8_t address, uint8_t *query,uint8_t querySize, uint8_t *response, uint8_t responseSize)
{
  if(HAL_I2C_Master_Transmit(&hi2c2, address<<1, query, querySize, TIMEOUT) == HAL_OK ){
    HAL_I2C_Master_Receive(&hi2c2, address<<1, response, responseSize, TIMEOUT);
  }
}

/*----------------------------------------------------------------------------*/
