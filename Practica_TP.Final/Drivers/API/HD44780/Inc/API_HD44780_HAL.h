/*
 * API_HD44780_HAL.h
 *
 *  Created on: Jul 5, 2024
 *      Author: raxt
 */

#ifndef API_HD44780_INC_API_HD44780_HAL_H_
#define API_HD44780_INC_API_HD44780_HAL_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "API_HD44780.h"

/*----------------------------------------------------------------------------*/

/* Hardware Specific Includes ------------------------------------------------*/

#include "stm32f4xx_hal.h"

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define DELAY20MS 20
#define DELAY10MS 10
#define DELAY2MS  2
#define DELAY1MS  1

/*----------------------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

void API_HD44780_HAL_Delay(uint32_t delay);
void API_HD44780_HAL_I2C_Write(API_HD44780_t lcdInstance, uint8_t payload);

/*----------------------------------------------------------------------------*/

#endif /* API_HD44780_INC_API_HD44780_HAL_H_ */
