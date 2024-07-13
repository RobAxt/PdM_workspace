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
  * @brief  ...
  * @param  ...
  * @retval ...
  */
tick_t API_Delay_HAL_GetTick(void)
{
  return HAL_GetTick();
}
