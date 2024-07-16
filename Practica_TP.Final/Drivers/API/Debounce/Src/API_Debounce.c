/*
 * API_Debounce.c
 *
 *  Created on: Jul 13, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_Delay.h"
#include "API_Debounce.h"

/*----------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define DEBOUNCEdELAY 40

/*----------------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

typedef enum
{
  BUTTON_UP,
  BUTTON_FALLING,
  BUTTON_DOWN,
  BUTTON_RAISING,
} debounceState_t;

struct DebounceGPI_s
{
  bool_t pushButtonPressed;
  GPIO_t gpio;
  Delay_t debounceDelay;
  debounceState_t currentState;
  bool_t used;
};

/*----------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

DebounceGPI_t API_Debounce_AllocateInstance(void);

/*----------------------------------------------------------------------------*/

/* API code ------------------------------------------------------------------*/

/**
  * @brief  Initialize FSM structure for the specified GPIO
  * @param  GPIO_t gpio: public structure that encapsulates the gpio format
  * @retval DebounceGPI_t: return a pointer to the allocated memory structure
  */
DebounceGPI_t API_Debounce_Init(GPIO_t gpio)
{
  DebounceGPI_t this = API_Debounce_AllocateInstance();

  if(NULL != this)
  {
    this->gpio.GPIOpin = gpio.GPIOpin;
    this->gpio.GPIOx   = gpio.GPIOx;
    this->pushButtonPressed = false;
    this->debounceDelay = API_Delay_Init(DEBOUNCEdELAY);
    this->currentState = BUTTON_UP;
  }
  return this;
}

/**
  * @brief  Refresh the state of the current FSM instance
  * @param  DebounceGPI_t pushButton: instance of the FSM to update
  * @retval None
  */
void API_Debounce_Update(DebounceGPI_t pushButton)
{
  if(NULL != pushButton)
  {
    switch(pushButton->currentState)
    {
      case BUTTON_UP:
        if(DOWN == API_Debounce_HAL_ReadButtonState(pushButton->gpio))
          pushButton->currentState = BUTTON_FALLING;
        break;
      case BUTTON_FALLING:
        if(API_Delay_DelayTimeOut(pushButton->debounceDelay))
        {
          if(DOWN == API_Debounce_HAL_ReadButtonState(pushButton->gpio))
          {
            pushButton->currentState = BUTTON_DOWN;
            pushButton->pushButtonPressed = true;
          }
          else
            pushButton->currentState = BUTTON_UP;
        }
        break;
      case BUTTON_DOWN:
        if(UP == API_Debounce_HAL_ReadButtonState(pushButton->gpio))
          pushButton->currentState = BUTTON_RAISING;
        break;
      case BUTTON_RAISING:
        if(API_Delay_DelayTimeOut(pushButton->debounceDelay))
        {
          if(UP == API_Debounce_HAL_ReadButtonState(pushButton->gpio))
            pushButton->currentState = BUTTON_UP;
          else
            pushButton->currentState = BUTTON_DOWN;
        }
        break;
      default:
    }
  }
}

/**
  * @brief  Indicates if the pushbutton was pressed or not
  * @param  DebounceGPI_t pushButton: instance of the FSM
  * @retval bool_t: return true if the pushbutton was pressed
  */
bool_t API_Debounce_ReadKey(DebounceGPI_t pushButton)
{
  if(NULL != pushButton)
  {
    bool_t returnPushButtonState = pushButton->pushButtonPressed;
    pushButton->pushButtonPressed = false;
    return returnPushButtonState;
  }
  return false;
}

/*----------------------------------------------------------------------------*/

/* Private API code ----------------------------------------------------------*/

/**
  * @brief  Allocates memory for the DebounceGPI_s structure
  * @param  None
  * @retval DebounceGPI_t if the MAXdEBOUNCEiNTANCES is not exceded,
  *         will return the pointer of the DebounceGPI_s
  */
DebounceGPI_t API_Debounce_AllocateInstance(void)
{
  static struct DebounceGPI_s instances[MAXdEBOUNCEiNTANCES] = {0};

  DebounceGPI_t newInstance = NULL;
  for(uint8_t index = 0; MAXdEBOUNCEiNTANCES > index; index++)
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

