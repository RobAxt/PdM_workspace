/*
 * API_debounce.h
 *
 *  Created on: Jul 11, 2024
 *      Author: raxt
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "API_delay.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* Exported types ------------------------------------------------------------*/
#ifndef BOOL_TYPE_DEFINITIOON_
#define BOOL_TYPE_DEFINITIOON_
typedef bool bool_t;
#endif // BOOL_TYPE_DEFINITIOON_

/* Exported functions ------------------------------------------------------- */
void API_debounceFSM_init(void);
void API_debounceFSM_update(void);
bool_t API_debounceFSM_readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
