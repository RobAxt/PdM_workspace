/*
 * FSM.h
 *
 *  Created on: Jul 14, 2024
 *      Author: raxt
 */

#ifndef APP_FSM_INC_APP_FSM_H_
#define APP_FSM_INC_APP_FSM_H_

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "API_PN532.h"
#include "API_Delay.h"
#include "API_Logger.h"
#include "APP_UserADM.h"
#include "API_HD44780.h"
#include "API_Debounce.h"

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

#ifndef BOOL_TYPE_DEFINITIOON_
#define BOOL_TYPE_DEFINITIOON_
typedef bool bool_t;
#endif // BOOL_TYPE_DEFINITIOON_

typedef struct FSM_s * FSM_t;

/*----------------------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

FSM_t  APP_FSM_Init(GPIO_t signInButton, GPIO_t eraseButton);
void   APP_FSM_Update(FSM_t fsm);

/*----------------------------------------------------------------------------*/

#endif /* APP_FSM_INC_APP_FSM_H_ */
