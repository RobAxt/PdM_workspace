/*
 * API_delay.c
 *
 *  Created on: Jul 4, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"

/* Public functions ---------------------------------------------------------*/
/**
  * @brief  Initialize the delay structure.
  * @param  delay: pointer to the delay structure.
  * @param  duration: time in milisecond of the delay.
  * @retval None.
  */
void delayInit( delay_t * delay, tick_t duration )
{
  if(NULL != delay && MAXdELAY >= duration)
  {
	delay->startTime = 0;
	delay->duration  = duration;
	delay->running   = false;
  }
}

/**
  * @brief  Check whether the delay has been exceeded or not.
  * @param  delay: pointer to the delay structure.
  * @retval true  -> if duration is no exceeded.
  *         false -> if duration is exceeded.
  */
bool_t delayRead(delay_t * delay)
{
  if(NULL != delay)
  {
    if(true == delay->running)
    {
      if(HAL_GetTick() - delay->startTime >= delay->duration)
      {
    	delay->running = false;
      }
    } else
    {
	  delay->startTime = HAL_GetTick();
	  delay->running = true;
    }
    return delay->running;
  }
  return false;
}

/**
  * @brief  Updates the duration of the delay.
  * @param  delay: pointer to the delay structure.
  * @param  duration: time in milisecond of the delay.
  * @retval None.
  */
void delayWrite(delay_t * delay, tick_t duration)
{
  if(NULL != delay && MAXdELAY >= duration)
  {
    delay->duration  = duration;
  }
}

/**
  * @brief  Indicates whether the timer is running or not.
  * @param  delay: pointer to the delay structure.
  * @param  running: boolean that specifies whether the time has run out or not.
  * @retval None.
  */
bool_t delayIsRunning(delay_t * delay)
{
  return delay->running;
}
