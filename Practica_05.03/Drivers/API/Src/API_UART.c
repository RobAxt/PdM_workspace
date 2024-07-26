/*
 * API_UART.c
 *
 *  Created on: Jul 25, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/
#include "API_UART.h"

/* Private variable ----------------------------------------------------------*/
/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  ...
  * @param  None.
  * @retval bool_t.
  */
bool_t uartInit(void)
{
  UartHandle.Instance        = USARTx;

  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_ODD;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
   return false;
  }

  uartSendString((uint8_t*)"Welcome: 9600;7O1\r\n");
  return true;
}

/**
  * @brief  ...
  * @param  None.
  * @retval bool_t.
  */
void uartSendString(uint8_t * pstring)
{
  if(NULL != pstring && MAXbUFFER > strlen((char*)pstring))
  {
    if(HAL_OK != HAL_UART_Transmit(&UartHandle, pstring, strlen((char*)pstring), TxTIMEOUT))
      Error_Handler();
  }
  else
    Error_Handler();

}

/**
  * @brief  ...
  * @param  None.
  * @retval bool_t.
  */
void uartSendStringSize(uint8_t * pstring, uint16_t size)
{
  if(NULL != pstring && MAXbUFFER > size && 0 < size)
  {
    if(HAL_OK != HAL_UART_Transmit(&UartHandle, pstring, size, TxTIMEOUT))
      Error_Handler();
  }
  else
    Error_Handler();
}

/**
  * @brief  ...
  * @param  None.
  * @retval bool_t.
  */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size)
{
  if(NULL != pstring && MAXbUFFER > size && 0 < size)
  {
    if(HAL_ERROR == HAL_UART_Receive(&UartHandle, pstring, size, RxTIMEOUT))
      Error_Handler();
  }
  else
    Error_Handler();
}

/* Private API code ----------------------------------------------------------*/
static void Error_Handler(void)
{
  while (1)
  {
  }
}
