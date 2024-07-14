/*
 * FSM.c
 *
 *  Created on: Jul 14, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "FSM.h"

/*----------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define STATEDELAY 3000
#define ZERO          0

/*----------------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

typedef enum
{
  WAITING,
  VERIFY,
  ADD,
  DELETE,
  INVALID
} FSMstates_t;

struct FSM_s
{
  DebounceGPI_t addPB;
  DebounceGPI_t delPB;
  PN532_t tagReader;
  PN532_Tag_t currentTag;
  API_HD44780_t diplayLCD;

  Delay_t stateDelay;
  FSMstates_t currentState;
};

/*----------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

static FSMstates_t APP_FSM_WaitingState(FSM_t fsm);
static FSMstates_t APP_FSM_VerifyState(FSM_t fsm);
static FSMstates_t APP_FSM_AddState(FSM_t fsm);
static FSMstates_t APP_FSM_DeleteState(FSM_t fsm);
static FSMstates_t APP_FSM_InvalidState(FSM_t fsm);

/*----------------------------------------------------------------------------*/

/* APP code ------------------------------------------------------------------*/

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
FSM_t APP_FSM_Init(GPIO_t signInButton, GPIO_t eraseButton)
{
  static struct FSM_s this;

  this.addPB = API_Debounce_Init(signInButton);
  this.delPB = API_Debounce_Init(eraseButton);
  this.diplayLCD = API_HD44780_Init(PCF8574MAXaDDRESS, BACKLIGHToN);
  this.tagReader = API_PN532_Init();
  memset(this.currentTag.uid, ZERO, MAXUIDsIZE);
  this.currentTag.size = 0;
  this.stateDelay = API_Delay_Init(STATEDELAY);

  this.currentState = WAITING;

  if(NULL != this.addPB && NULL != this.delPB && NULL != this.diplayLCD && NULL != this.tagReader && NULL != this.stateDelay)
    return &this;
  else
    return NULL;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
void APP_FSM_Update(FSM_t fsm)
{

  if(NULL != fsm)
  {
    API_Debounce_Update(fsm->addPB);
    API_Debounce_Update(fsm->delPB);

    switch(fsm->currentState)
    {
      case WAITING:
        fsm->currentState = APP_FSM_WaitingState(fsm);
        break;
      case VERIFY:
        fsm->currentState = APP_FSM_VerifyState(fsm);
        break;
      case ADD:
        fsm->currentState = APP_FSM_AddState(fsm);
        break;
      case DELETE:
        fsm->currentState = APP_FSM_DeleteState(fsm);
        break;
      case INVALID:
        fsm->currentState = APP_FSM_InvalidState(fsm);
        break;
      default:
    }
  }
}

/*----------------------------------------------------------------------------*/

/* Private APP code ----------------------------------------------------------*/

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
static FSMstates_t APP_FSM_WaitingState(FSM_t fsm)
{
  PN532_Error_t tagStatus = API_PN532_ReadTag(fsm->tagReader);
  FSMstates_t nextState = WAITING;

  if(PN532oK != tagStatus) // If No Tag pressent or something wrong stay here
  {
    API_HD44780_SetCursor(fsm->diplayLCD, LINE1, 0);
    API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)" Waiting Tag... ");
    API_HD44780_SetCursor(fsm->diplayLCD, LINE2, 0);
    API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)"                ");
    nextState = WAITING;
  }
  else
  {
    if(PN532oK == tagStatus)  // If Tag present go to VERIFY
      nextState = VERIFY;
    else                      // Oops stay here
      nextState = WAITING;
  }
  return nextState;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
static FSMstates_t APP_FSM_VerifyState(FSM_t fsm)
{
  FSMstates_t nextState = WAITING;
  int8_t line[DISPLAYlINEsIZE] = {0};

  fsm->currentTag.size = API_PN532_GetTag(fsm->tagReader, fsm->currentTag.uid, MAXUIDsIZE);

  if(NOTiNITIALIZED == fsm->currentTag.size)  // No tag present or something wrong go to WAITING
  {
    nextState = WAITING;
  }
  else  // The Tag was readed then ....
  {
    if(APP_UserADM_ValidUser(fsm->currentTag.uid, fsm->currentTag.size))  // If Valid Tag then Show It...
    {
      API_HD44780_SetCursor(fsm->diplayLCD, LINE1, 0);
      API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)"Valid Tag       ");
      API_HD44780_SetCursor(fsm->diplayLCD, LINE2, 0);
      sprintf((char*)line, "%02X %02X %02X %02X    ", fsm->currentTag.uid[0], fsm->currentTag.uid[1], fsm->currentTag.uid[2], fsm->currentTag.uid[3]);
      API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)line);

      if(API_Debounce_ReadKey(fsm->delPB))  // If delete Tag Button was pressed then Go to Delete...
      {
        nextState = DELETE;
      }
      else // stay in this state
      {
        nextState = VERIFY;
      }
    }
    else  // The Tag is Invalid
    {
      if(API_Debounce_ReadKey(fsm->addPB)) // If add Tag Button was pressed then Go to Add...
      {
        nextState = ADD;
      }
      else
      {
        nextState = INVALID;
      }
    }

    if(PN532nOtAG == API_PN532_ReadTag(fsm->tagReader))
    {
      nextState = WAITING;
    }
  }
  return nextState;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
static FSMstates_t APP_FSM_AddState(FSM_t fsm)
{
  FSMstates_t nextState = ADD;
  int8_t line[DISPLAYlINEsIZE] = {0};

  APP_UserADM_AddUser(fsm->currentTag.uid, fsm->currentTag.size);
  fsm->currentTag.size = 0;

  API_HD44780_SetCursor(fsm->diplayLCD, LINE1, 0);
  API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)"Added Tag       ");
  API_HD44780_SetCursor(fsm->diplayLCD, LINE2, 0);
  sprintf((char*)line, "%02X %02X %02X %02X    ", fsm->currentTag.uid[0], fsm->currentTag.uid[1], fsm->currentTag.uid[2], fsm->currentTag.uid[3]);
  API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)line);

  if(API_Delay_DelayTimeOut(fsm->stateDelay))
  {
    nextState = WAITING;
  }

  return nextState;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
static FSMstates_t APP_FSM_DeleteState(FSM_t fsm)
{
  FSMstates_t nextState = DELETE;
  int8_t line[DISPLAYlINEsIZE] = {0};

  APP_UserADM_AddDelete(fsm->currentTag.uid, fsm->currentTag.size);
  fsm->currentTag.size = 0;

  API_HD44780_SetCursor(fsm->diplayLCD, LINE1, 0);
  API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)"Deleted Tag     ");
  API_HD44780_SetCursor(fsm->diplayLCD, LINE2, 0);
  sprintf((char*)line, "%02X %02X %02X %02X    ", fsm->currentTag.uid[0], fsm->currentTag.uid[1], fsm->currentTag.uid[2], fsm->currentTag.uid[3]);
  API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)line);

  if(API_Delay_DelayTimeOut(fsm->stateDelay))
  {
    nextState = WAITING;
  }

  return nextState;
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
static FSMstates_t APP_FSM_InvalidState(FSM_t fsm)
{
  FSMstates_t nextState = INVALID;
  int8_t line[DISPLAYlINEsIZE] = {0};

  API_HD44780_SetCursor(fsm->diplayLCD, LINE1, 0);
  API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)"Invalid Tag     ");
  API_HD44780_SetCursor(fsm->diplayLCD, LINE2, 0);
  sprintf((char*)line, "%02X %02X %02X %02X    ", fsm->currentTag.uid[0], fsm->currentTag.uid[1], fsm->currentTag.uid[2], fsm->currentTag.uid[3]);
  API_HD44780_SendString(fsm->diplayLCD, (uint8_t*)line);

  if(PN532oK != API_PN532_ReadTag(fsm->tagReader))
  {
    nextState = WAITING;
  }

  return nextState;
}

/*----------------------------------------------------------------------------*/
