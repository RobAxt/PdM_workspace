/*
 * API_PN532_HAL.h
 *
 *  Created on: Jul 6, 2024
 *      Author: raxt
 */

#ifndef API_PN532_INC_API_PN532_HAL_H_
#define API_PN532_INC_API_PN532_HAL_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/*----------------------------------------------------------------------------*/

/* Hardware Specific Includes ------------------------------------------------*/

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

/* Exported functions prototypes ---------------------------------------------*/

void   API_PN532_HAL_Delay(uint32_t delay);
bool_t API_PN532_HAL_I2C_Write(uint8_t address, uint8_t *query, uint16_t querySize);
bool_t API_PN532_HAL_I2C_Read(uint8_t address, uint8_t *response, uint16_t responseSize);
void   API_PN532_HAL_I2C_QueryResponse(uint8_t address, uint8_t *query, uint16_t querySize, uint8_t *response, uint16_t responseSize);

/*----------------------------------------------------------------------------*/

#endif /* API_PN532_INC_API_PN532_HAL_H_ */
