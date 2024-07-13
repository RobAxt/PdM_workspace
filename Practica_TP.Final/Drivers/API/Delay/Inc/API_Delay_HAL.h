/*
 * API_Delay_HAL.h
 *
 *  Created on: Jul 13, 2024
 *      Author: raxt
 */

#ifndef API_DELAY_INC_API_DELAY_HAL_H_
#define API_DELAY_INC_API_DELAY_HAL_H_

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "API_Delay.h"

/*----------------------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

tick_t API_Delay_HAL_GetTick(void);

/*----------------------------------------------------------------------------*/
#endif /* API_DELAY_INC_API_DELAY_HAL_H_ */
