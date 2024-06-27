 /**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup UART_Printf
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

typedef enum
{
  UPsEQUENCE = 0,
  DOWNsEQUENCE
} LED_sequence_t;

/* Private define ------------------------------------------------------------*/

#define TIMEoN  200
#define TIMEoFF 200

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

Led_TypeDef LED_sequence[2][3] = {{LED1, LED2, LED3},{LED3, LED2, LED1}};

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

void LED_blink(Led_TypeDef led, uint32_t timeOn, uint32_t timeOff);
LED_sequence_t PB_USER_sequence(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Initialize BSP Led for LEDs */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);

  /* Initialize BSP PB for BUTTON_USER */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  const uint8_t MAXlED = sizeof(LED_sequence[0]) / sizeof(Led_TypeDef);
  LED_sequence_t PB_sequence = UPsEQUENCE;

  /* Infinite loop */
  while (1)
  {
	PB_sequence = PB_USER_sequence();

	for(uint8_t i=0; i < MAXlED; i++)
	{
	  LED_blink(LED_sequence[PB_sequence][i], TIMEoN, TIMEoFF);
	}
  }
}

/**
  * @brief  Blink led one time.
  * @param  led: Specifies the Led to be blinked.
   *   This parameter can be one of following parameters:
   *	  @arg  LED1
   *	  @arg  LED2
   *	  @arg  LED3
  * @param	timeOn: Specifies the time the led will remain on.
  * @param	timeOff: Specifies the time the led will remain off.
  * @retval None
  */
void LED_blink(Led_TypeDef led, uint32_t timeOn, uint32_t timeOff)
{
	BSP_LED_On(led);
	HAL_Delay(timeOn);
	BSP_LED_Off(led);
	HAL_Delay(timeOff);
}

/**
  * @brief  Read user pushbutton and returns the selected led sequence.
  *         Se asume que el cambio de sentido de la secuencia es por
  *         nivel del PB y no por flanco.
  * @param  None
  * @retval LED_sequence_t: Return one of the two the sequence.
  */
LED_sequence_t PB_USER_sequence(void)
{
	return BSP_PB_GetState(BUTTON_USER)? DOWNsEQUENCE : UPsEQUENCE;
}

/* Respuestas a preguntas para pensar:
 *
 * * Al usar un array queda en un unico lugar del código la especificacion
 *   de la secuencia a utilizar.
 *
 * * En el esquematico de la placa hay un circuito RC que se encarga de
 *   minimizar el efecto de los rebotes del pulsador.
 *
 * * La diferencia entre implementar la lectura del PB entre cada secuencia
 *   o entre cada parpadeo es que el usuario observará una demora en el tiempo
 *   de respuesta entre que se presiona el boton y se observa el cambio de secuencia.
 *   En esta implementación el usuario debe esperar que termine la secuencia actual
 *   para que observe el cambio de secuencia.
 *
 * * La forma mas eficiente seria implementar una interrupción por flanco
 *   ascendente y descendente para modificar el tipo de sucuencia a ejecutar.
 *   De esta manera solo debe esperar a que una funcion LED_blink termine para
 *   observar el cambio de secuencia (esto se debe a que se usa HAL_Delay
 *   que es bloqueante)
 *
 * * Al ser bloquante la funcion de demora no importa si se usa una interrupcion
 *   o se lee el PB dentro del ciclo for, siempre hay que esperar a que termine
 *   uno de los llamados a LED_blink.
 */

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
