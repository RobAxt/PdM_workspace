/*
 * API_Debounce_HAL.h
 *
 *  Created on: Jul 13, 2024
 *      Author: raxt
 */

#ifndef API_DEBOUNCE_INC_API_DEBOUNCE_HAL_H_
#define API_DEBOUNCE_INC_API_DEBOUNCE_HAL_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"      /* <- HAL include */

/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

#ifndef BOOL_TYPE_DEFINITIOON_
#define BOOL_TYPE_DEFINITIOON_
typedef bool bool_t;
#endif // BOOL_TYPE_DEFINITIOON_

typedef struct
{
  GPIO_TypeDef* GPIOx;
  uint16_t GPIOpin;
} GPIO_t;

typedef enum
{
  DOWN = 0,
  UP
} pushButtonState_t;

/*----------------------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

bool_t API_Debounce_HAL_ReadButtonState(GPIO_t pin);

/*----------------------------------------------------------------------------*/

#endif /* API_DEBOUNCE_INC_API_DEBOUNCE_HAL_H_ */
