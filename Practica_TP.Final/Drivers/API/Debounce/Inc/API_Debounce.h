/*
 * API_Debounce.h
 *
 *  Created on: Jul 13, 2024
 *      Author: raxt
 */

#ifndef API_DEBOUNCE_INC_API_DEBOUNCE_H_
#define API_DEBOUNCE_INC_API_DEBOUNCE_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include "API_Delay.h"
#include "API_Debounce_HAL.h"

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define MAXdEBOUNCEiNTANCES 5

/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct DebounceGPI_s * DebounceGPI_t;

/*----------------------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

DebounceGPI_t API_Debounce_Init(GPIO_t gpio);
void          API_Debounce_Update(DebounceGPI_t pushButton);
bool_t        API_Debounce_ReadKey(DebounceGPI_t pushButton);

/*----------------------------------------------------------------------------*/
#endif /* API_DEBOUNCE_INC_API_DEBOUNCE_H_ */
