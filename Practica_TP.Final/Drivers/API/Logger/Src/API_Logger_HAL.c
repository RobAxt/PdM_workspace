/*
 * API_Logger_HAL.c
 *
 *  Created on: Jul 25, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_Logger_HAL.h"

/*----------------------------------------------------------------------------*/

/* Extern public variables----------------------------------------------------*/

extern UART_HandleTypeDef huart3;

/*----------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define TIMEOUT 5000

/*----------------------------------------------------------------------------*/

/* Hardware Specific API code ------------------------------------------------*/

/**
  * @brief  Retrieve the system time.
  * @param  None
  * @retval uint32_t the system time in second.
  */
uint32_t API_Logger_HAL_Time(void)
{
  return HAL_GetTick()/1000;
}


/**
  * @brief  Send log data to UART
  * @param  uint8_t *data:    data to transmit
  * @param  uint8_t dataSize: size of data to transmit
  * @retval bool_t: returns true if the data was sent, otherwise false
  */
bool_t API_Logger_HAL_UARTTx(uint8_t *data, uint8_t dataSize)
{
  if(HAL_UART_Transmit(&huart3, data, dataSize, TIMEOUT) == HAL_OK)
    return true;
  else
    return false;
}

/*----------------------------------------------------------------------------*/
