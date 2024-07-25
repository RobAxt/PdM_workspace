/*
 * API_Logger_HAL.h
 *
 *  Created on: Jul 25, 2024
 *      Author: raxt
 */

#ifndef API_LOGGER_INC_API_LOGGER_HAL_H_
#define API_LOGGER_INC_API_LOGGER_HAL_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

#ifndef BOOL_TYPE_DEFINITIOON_
#define BOOL_TYPE_DEFINITIOON_
typedef bool bool_t;
#endif // BOOL_TYPE_DEFINITIOON_

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

uint32_t API_Logger_HAL_Time(void);
bool_t API_Logger_HAL_UARTTx(uint8_t *data, uint8_t dataSize);

/*----------------------------------------------------------------------------*/

#endif /* API_LOGGER_INC_API_LOGGER_HAL_H_ */
