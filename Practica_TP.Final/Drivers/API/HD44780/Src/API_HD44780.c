/*
 * API_HD44780.c
 *
 *  Created on: Jul 4, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_HD44780.h"

/*----------------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

struct API_HD44780_s
{
  backlight_t backLight;
  uint8_t     address;
};

/*----------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void API_HD44780_Write_Nibble(API_HD44780_t lcdInstance, uint8_t nibble, uint8_t rs);

/*----------------------------------------------------------------------------*/

/* API code ------------------------------------------------------------------*/

/**
  * @brief  Initialize API_HD44780_s structure.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  address:
  * @param  backLight:
  * @retval None.
  */
void API_HD44780_Init(API_HD44780_t lcdInstance, uint8_t address = PCF8574MAXaDDRESS, backlight_t backLight = BACKLIGHToN)
{
  if(PCF8574MAXaDDRESS >= address && PCF8574MINaDDRESS <= address)
    lcdInstance->address = address;
  else
    lcdInstance->address = PCF8574MAXaDDRESS;

  lcdInstance->backLight = backlight;
}

/*----------------------------------------------------------------------------*/

/* Private API code ----------------------------------------------------------*/

/**
  * @brief  Write nibble
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  nibble:
  * @param  rs:
  * @retval None.
  */
void API_HD44780_Write_Nibble(API_HD44780_t lcdInstance, uint8_t nibble, uint8_t rs)
{

}
