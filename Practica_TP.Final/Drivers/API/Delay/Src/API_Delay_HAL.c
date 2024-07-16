/*
 * API_Delay_HAL.c
 *
 *  Created on: Jul 13, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_Delay_HAL.h"

/*----------------------------------------------------------------------------*/

/* Hardware Specific API code ------------------------------------------------*/

/**
  * @brief  Encapsulates the hardware specific call to a blocking delay
  * @param  uint32_t delay: delay in miliseconds.
  * @retval None.
  */
tick_t API_Delay_HAL_GetTick(void)
{
  return HAL_GetTick();
}

/*----------------------------------------------------------------------------*/
