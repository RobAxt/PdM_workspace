/*
 * API_Logger.c
 *
 *  Created on: Jul 25, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_Logger.h"
#include "API_Logger_HAL.h"

/*----------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define LINEsIZE    64
#define DEBUGlEVEL    "DBG"
#define WARNINGlEVEL  "WAR"
#define ERRORlEVEL    "ERR"

/*----------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void API_Logger_Log(uint8_t *level, uint8_t *string, uint8_t size);

/*----------------------------------------------------------------------------*/

/* API code ------------------------------------------------------------------*/

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
void API_Logger_LogDebug(uint8_t *string)
{
  if(NULL != string)
    API_Logger_Log((uint8_t*) DEBUGlEVEL, string, strlen((char*)string));
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
void API_Logger_LogWarning(uint8_t *string)
{
  if(NULL != string)
    API_Logger_Log((uint8_t*) WARNINGlEVEL, string, strlen((char*)string));
}

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
void API_Logger_LogError(uint8_t *string)
{
  if(NULL != string)
    API_Logger_Log((uint8_t*) ERRORlEVEL, string, strlen((char*)string));
}

/*----------------------------------------------------------------------------*/

/* Private API code ----------------------------------------------------------*/

/**
  * @brief  ...
  * @param  ...
  * @retval ...
  */
void API_Logger_Log(uint8_t *level, uint8_t *string, uint8_t size)
{
  uint8_t logString[LINEsIZE] = {0};
  if(NULL != level && NULL != string && LINEsIZE > size)
  {
    sprintf((char*)logString, "%08ld - %s - %s\r\n", API_Logger_HAL_Time(), (char *)level, (char *)string);
    API_Logger_HAL_UARTTx(logString, strlen((char*)logString));
  }
}


/*----------------------------------------------------------------------------*/
