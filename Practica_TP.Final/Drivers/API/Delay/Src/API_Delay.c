/*
 * API_Delay.c
 *
 *  Created on: Jul 13, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_Delay.h"
#include "API_Delay_HAL.h"

/*----------------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

struct Delay_s
{
  tick_t startTime;
  tick_t duration;
  bool_t running;
  bool_t used;
};

/*----------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

static Delay_t API_Delay_AllocateInstance(void);

/*----------------------------------------------------------------------------*/

/* API code ------------------------------------------------------------------*/

/**
  * @brief  Obtain an instance and initialize the structure
  * @param  tick_t duration: specifies the time of the delay
  * @retval Delay_t: return an instance of the delay object
  */
Delay_t API_Delay_Init(tick_t duration)
{
  Delay_t this = API_Delay_AllocateInstance();

  if(NULL != this && MAXdELAY >= duration)
  {
    this->startTime = 0;
    this->duration  = duration;
    this->running   = false;
  }

  return this;
}

/**
  * @brief  Check whether the delay has been exceeded or not.
  * @param  delay: pointer to the delay structure.
  * @retval true  -> if duration is exceeded.
  *         false -> if duration is no exceeded.
  */
bool_t API_Delay_DelayTimeOut(Delay_t delay)
{
  if(NULL != delay)
  {
    if(true == delay->running)
    {
      if(API_Delay_HAL_GetTick() - delay->startTime >= delay->duration)
      {
    	delay->running = false;
      }
    } else
    {
	  delay->startTime = API_Delay_HAL_GetTick();
	  delay->running = true;
    }
    return !delay->running;
  }
  return false;
}

/**
  * @brief  Updates the duration of the delay.
  * @param  delay: pointer to the delay structure.
  * @param  duration: time in milisecond of the delay.
  * @retval None.
  */
void API_Delay_DelayDuration(Delay_t  delay, tick_t duration)
{
  if(NULL != delay && MAXdELAY >= duration)
  {
    delay->duration  = duration;
  }
}

/*----------------------------------------------------------------------------*/

/* Private API code ----------------------------------------------------------*/

/**
  * @brief  Allocates memory for the Delay_s structure
  * @param  None.
  * @retval Delay_t if the MAXdELAYiNTANCES is not exceded, will return the pointer of the Delay_s
  */
static Delay_t API_Delay_AllocateInstance(void)
{
  static struct Delay_s instances[MAXdELAYiNTANCES] = {0};

  Delay_t newInstance = NULL;
  for(uint8_t index = 0; MAXdELAYiNTANCES > index; index++)
  {
    if(!instances[index].used)
    {
      newInstance = &instances[index];
      newInstance->used = true;
      break;
    }
  }

  return newInstance;
}
/*----------------------------------------------------------------------------*/
