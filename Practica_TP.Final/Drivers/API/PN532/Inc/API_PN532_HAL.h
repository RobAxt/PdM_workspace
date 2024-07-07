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
#include "stm32f4xx_hal.h"
#include "API_PN532.h"

/*----------------------------------------------------------------------------*/

/* Hardware Specific Includes ------------------------------------------------*/

#include "stm32f4xx_hal.h"

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

void API_PN532_HAL_Delay(uint32_t delay);
void API_PN532_HAL_I2C_QueryResponse(uint8_t address, uint8_t *query,uint8_t querySize, uint8_t *response, uint8_t responseSize);
/*----------------------------------------------------------------------------*/

#endif /* API_PN532_INC_API_PN532_HAL_H_ */
