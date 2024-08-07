/*
 * API_delay.h
 *
 *  Created on: Jul 4, 2024
 *      Author: raxt
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef uint32_t tick_t;
typedef bool bool_t;
typedef struct
{
  tick_t startTime;
  tick_t duration;
  bool_t running;
} delay_t;

/* Exported constants --------------------------------------------------------*/
#define MAXdELAY 60000

/* Exported functions ------------------------------------------------------- */
void delayInit(delay_t * delay, tick_t duration);
bool_t delayRead(delay_t * delay);
void delayWrite(delay_t * delay, tick_t duration);
bool_t delayIsRunning(delay_t * delay);

#endif /* API_INC_API_DELAY_H_ */
