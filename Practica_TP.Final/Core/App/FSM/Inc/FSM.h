/*
 * FSM.h
 *
 *  Created on: Jul 14, 2024
 *      Author: raxt
 */

#ifndef APP_FSM_INC_FSM_H_
#define APP_FSM_INC_FSM_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "UserADM.h"
#include "API_Delay.h"
#include "API_Debounce.h"
#include "API_HD44780.h"
#include "API_PN532.h"

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct FSM_s * FSM_t;

/*----------------------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

FSM_t  APP_FSM_Init(GPIO_t signInButton, GPIO_t eraseButton);
void   APP_FSM_Update(FSM_t fsm);

/*----------------------------------------------------------------------------*/

#endif /* APP_FSM_INC_FSM_H_ */
