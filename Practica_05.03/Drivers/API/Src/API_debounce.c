/*
 * API_debounce.c
 *
 *  Created on: Jul 11, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/
#include "API_debounce.h"

/* Private define ------------------------------------------------------------*/
#define DEBOUNCEdELAY 40

/* Private types -------------------------------------------------------------*/
typedef enum
{
  BUTTON_UP,
  BUTTON_FALLING,
  BUTTON_DOWN,
  BUTTON_RAISING,
} debounceState_t;

typedef enum
{
  DOWN = 0,
  UP
} pushButtonState_t;

/* Private function prototypes -----------------------------------------------*/
static pushButtonState_t API_debounceFSM_buttonState(void);

/* Private variable ----------------------------------------------------------*/
static bool_t pushButtonPressed;
static delay_t debounceDelay = {0, 0, false};
static debounceState_t currentState = BUTTON_UP;

/* API code ------------------------------------------------------------------*/

/**
  * @brief  Initialize FSM
  * @param  None
  * @retval None
  */
void API_debounceFSM_init(void)
{
  uartInit();
  delayInit(&debounceDelay, DEBOUNCEdELAY);
  currentState = BUTTON_UP;
}

/**
  * @brief  Updates FSM
  * @param  None
  * @retval None
  */
void API_debounceFSM_update(void)
{
  switch(currentState)
  {
    case BUTTON_UP:
      if(DOWN == API_debounceFSM_buttonState())
      {
        delayRead(&debounceDelay);
        currentState = BUTTON_FALLING;
      }
      break;
	case BUTTON_FALLING:
	    uartSendString((uint8_t*)"Flanco descendente detectado\r\n");
      if(false == delayRead(&debounceDelay))
      {
        if(DOWN == API_debounceFSM_buttonState())
        {
          currentState = BUTTON_DOWN;
          pushButtonPressed = true;
        }
        else
          currentState = BUTTON_UP;
      }
      break;
    case BUTTON_DOWN:
      if(UP == API_debounceFSM_buttonState())
      {
        delayRead(&debounceDelay);
        currentState = BUTTON_RAISING;
      }
      break;
    case BUTTON_RAISING:
      uartSendString((uint8_t*)"Flanco ascendente detectado\r\n");
      if(false == delayRead(&debounceDelay))
      {
        if(UP == API_debounceFSM_buttonState())
          currentState = BUTTON_UP;
        else
          currentState = BUTTON_DOWN;
      }
      break;
    default:
    	API_debounceFSM_init();
  }
}

/**
  * @brief  Return if the button where pressed
  * @param  None
  * @retval return true only if the button was pressed
  */
bool_t API_debounceFSM_readKey(void)
{
  bool_t returnPushButtonState = pushButtonPressed;
  pushButtonPressed = false;
  return returnPushButtonState;
}

/* Private API code ----------------------------------------------------------*/

/**
  * @brief  Reads the current state of the User Push Button
  * @param  None
  * @retval return the pushButtonState_t of the Push Button
  */
static pushButtonState_t API_debounceFSM_buttonState(void)
{
  return BSP_PB_GetState(BUTTON_USER)? UP : DOWN;
}
