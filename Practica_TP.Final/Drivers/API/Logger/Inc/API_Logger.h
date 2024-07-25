/*
 * API_Logger.h
 *
 *  Created on: Jul 25, 2024
 *      Author: raxt
 */

#ifndef API_LOGGER_INC_API_LOGGER_H_
#define API_LOGGER_INC_API_LOGGER_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */

void API_Logger_LogDebug(uint8_t *string);
void API_Logger_LogWarning(uint8_t *string);
void API_Logger_LogError(uint8_t *string);

/*----------------------------------------------------------------------------*/

#endif /* API_LOGGER_INC_API_LOGGER_H_ */
