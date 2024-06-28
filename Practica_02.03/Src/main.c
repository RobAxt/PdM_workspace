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
typedef struct
{
  uint32_t times;
  uint32_t period;
  float duty;
} LED_pattern_t;

typedef enum
{
  OFF = false,
  ON  = true
} LED_state_t;

/* Private define ------------------------------------------------------------*/

#define MAXpATTERN 3

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */

UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

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

  /* Initialize BSP Led for LED1 */
  BSP_LED_Init(LED1);
  BSP_LED_Off(LED1);

  /* Declare and Initialize working local variables */
  LED_state_t LEDState = OFF;
  uint32_t patternCount = 0;
  uint32_t timesCount = 0;
  delay_t onDelayLED1  = {0, 0, false};
  delay_t offDelayLED1 = {0, 0, false};
  LED_pattern_t LEDPattern[] = {
  		                         { 5, 1000, 0.5 },
                                 { 5,  200, 0.5 },
                                 { 5,  100, 0.5 },
                               };
  while(1)
  {
	delayInit(&onDelayLED1,  LEDPattern[patternCount].period * LEDPattern[patternCount].duty);
	delayInit(&offDelayLED1, LEDPattern[patternCount].period * (1 - LEDPattern[patternCount].duty));

	while(timesCount < LEDPattern[patternCount].times)
	{
	  if(OFF == LEDState)
	  {
	    if(false == delayRead(&offDelayLED1))
	    {
	      BSP_LED_On(LED1);
	      LEDState = ON;
	      delayRead(&onDelayLED1);
	    }
	  }
	  else
	  {
	    if(false == delayRead(&onDelayLED1))
		{
		  BSP_LED_Off(LED1);
		  LEDState = OFF;
		  delayRead(&offDelayLED1);
		  timesCount++;
		}
	  }
	}
    timesCount = 0;
	patternCount = (patternCount + 1) % MAXpATTERN;
  }
}

/* Delay Implementation ------------------------------------------------------*/

/**
  * @brief  Initialize the delay structure.
  * @param  delay: pointer to the delay structure.
  * @param  duration: time in milisecond of the delay.
  * @retval None.
  */
void delayInit( delay_t * delay, tick_t duration )
{
  if(NULL != delay)
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
  if(NULL != delay)
  {
    delay->duration  = duration;
  }
}

/*----------------------------------------------------------------------------*/

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
