/*
 * API_HD44780_HAL.c
 *
 *  Created on: Jul 5, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_HD44780_HAL.h"

/*----------------------------------------------------------------------------*/

/* Extern public variables----------------------------------------------------*/

extern I2C_HandleTypeDef hi2c2;

/*----------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define TIMEOUT 100

/*----------------------------------------------------------------------------*/

/* Hardware Specific API code ------------------------------------------------*/

/**
  * @brief  ...
  * @param  delay: ...
  * @retval None.
  */
void API_HD44780_HAL_Delay(uint32_t delay)
{
  HAL_Delay(delay);
}

/**
  * @brief  ...
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  payload: ...
  * @retval None.
  */
void API_HD44780_HAL_I2C_Write(API_HD44780_t lcdInstance, uint8_t payload)
{
  HAL_I2C_Master_Transmit(&hi2c2, API_HD44780_GetAddress(lcdInstance)<<1, &payload, sizeof(payload), TIMEOUT);
}

/*----------------------------------------------------------------------------*/
