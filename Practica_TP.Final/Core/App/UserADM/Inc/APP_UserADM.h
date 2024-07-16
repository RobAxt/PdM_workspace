/*
 * UserADM.h
 *
 *  Created on: Jul 14, 2024
 *      Author: raxt
 */

#ifndef APP_USERADM_INC_APP_USERADM_H_
#define APP_USERADM_INC_APP_USERADM_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define MAXuSERSIZE 10
#define MAXuSER     10

/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

#ifndef BOOL_TYPE_DEFINITIOON_
#define BOOL_TYPE_DEFINITIOON_
typedef bool bool_t;
#endif // BOOL_TYPE_DEFINITIOON_

/*----------------------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

bool_t APP_UserADM_AddUser(uint8_t * user, uint8_t size);
bool_t APP_UserADM_DeleteUser(uint8_t * user, uint8_t size);
bool_t APP_UserADM_ValidUser(uint8_t * user, uint8_t size);

/*----------------------------------------------------------------------------*/
#endif /* APP_USERADM_INC_APP_USERADM_H_ */
