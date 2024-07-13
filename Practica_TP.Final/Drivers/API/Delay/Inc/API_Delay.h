/*
 * API_Delay.h
 *
 *  Created on: Jul 13, 2024
 *      Author: raxt
 */

#ifndef API_DELAY_INC_API_DELAY_H_
#define API_DELAY_INC_API_DELAY_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

#ifndef BOOL_TYPE_DEFINITIOON_
#define BOOL_TYPE_DEFINITIOON_
typedef bool bool_t;
#endif // BOOL_TYPE_DEFINITIOON_

#ifndef TICK_TYPE_DEFINITIOON_
#define TICK_TYPE_DEFINITIOON_
typedef uint32_t tick_t;
#endif // TICK_TYPE_DEFINITIOON_

typedef struct Delay_s * Delay_t;

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define MAXdELAY          60000
#define MAXdELAYiNTANCES     10

/* Exported functions ------------------------------------------------------- */

Delay_t API_Delay_Init(tick_t duration);
bool_t  API_Delay_DelayTimeOut(Delay_t delay);
void    API_Delay_DelayDuration(Delay_t delay, tick_t duration);

#endif /* API_DELAY_INC_API_DELAY_H_ */
