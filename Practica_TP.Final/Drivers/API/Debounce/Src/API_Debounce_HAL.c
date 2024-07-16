/*
 * API_Debounce_HAL.c
 *
 *  Created on: Jul 13, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_Debounce_HAL.h"

/*----------------------------------------------------------------------------*/

/* Hardware Specific API code ------------------------------------------------*/

/**
  * @brief  Indicates the state of the gpio
  * @param  GPIO_t pin: gpio structure to inspect
  * @retval bool_t: return the state of the gpio
  */
bool_t API_Debounce_HAL_ReadButtonState(GPIO_t pin)
{
  return HAL_GPIO_ReadPin(pin.GPIOx, pin.GPIOpin) ? true : false;
}

/*----------------------------------------------------------------------------*/
