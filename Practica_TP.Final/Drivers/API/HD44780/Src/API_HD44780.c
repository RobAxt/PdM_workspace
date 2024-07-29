/*
 * API_HD44780.c
 *
 *  Created on: Jul 4, 2024
 *      Author: raxt
 */

/* Includes ------------------------------------------------------------------*/

#include "API_HD44780.h"
#include "API_HD44780_HAL.h"

/*----------------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

struct API_HD44780_s
{
  backlight_t backLight;
  uint8_t     address;
};

/*----------------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define RScMD    0x00
#define RSdATA   0x01
#define RWwRITE  0x00
#define RWrEAD   0x02
#define ENuNSET  0x00
#define ENsET    0x04

#define MSnIBBLE  0xf0
#define LSnIBBLE  0x04
#define EOL       '\0'

#define CLEARdISPLAY    0x01   // Clear Screen and Move Cursor To First Line
#define RETURNhOME      0x02   // Return Home
#define ENTRYmODE       0x04   // Entry Mode | something below
#define EMiNCREMENT     0x02   // ENTRYmODE  | Increment Cursor Position
#define EMnORMAL        0x00   // ENTRYmODE  | Move Cursor instead of Screen
#define DISPLAYmODE     0x08   // Display Mode | something below
#define DMdISPLAYoN     0x04   // DISPLAYmODE  | Display ON
#define DMdISPLAYoFF    0x00   // DISPLAYmODE  | Display OFF
#define DMcURSORoN      0x01   // DISPLAYmODE  | Cursor ON
#define DMcURSORoFF     0x00   // DISPLAYmODE  | Cursor OFF
#define DMcURSORbLINK   0x01   // DISPLAYmODE  | Cursor Blink
#define SHIFTmODE       0x10   // Shift Display or Cursor | something below
#define SMcURSOR        0x00   // SHIFTmODE | Shift Cursor
#define SMdISPLAY       0x08   // SHIFTmODE | Shift Display
#define SMlEFT          0x00   // SHIFTmODE | Shift to Left
#define SMrIGHT         0x04   // SHIFTmODE | Shift to Right
#define BYTEmODE        0x32   // Function set to 8-bit mode
#define NIBBLEmODE      0x28   // Function Set | Nibble Bus | 2 Lines LCD | 5x7 Character Matrix
#define SETDDRAM        0x80   // SETDDRAM | address

#define LINE1aDDRESS 0x00
#define LINE2aDDRESS 0x40

/*----------------------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

static void API_HD44780_Write_DataNibble(API_HD44780_t lcdInstance, uint8_t nibble, uint8_t rs, uint8_t rw);
static void API_HD44780_Write_Data(API_HD44780_t lcdInstance, uint8_t nibble, uint8_t rs, uint8_t rw);
static void API_HD44780_InitLCD(API_HD44780_t lcdInstance);

/*----------------------------------------------------------------------------*/

/* API code ------------------------------------------------------------------*/

/**
  * @brief  get the I2C address of PCF8574.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @retval returns the I2C address of PCF8574.
  */
uint8_t API_HD44780_GetAddress(API_HD44780_t lcdInstance)
{
  if(NULL != lcdInstance)
    return lcdInstance->address;
  return NOaDDRESS;
}

/**
  * @brief  set new I2C address of PCF8574.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  address: the new PCF8574 I2C address
  * @retval None.
  */
void API_HD44780_SetAddress(API_HD44780_t lcdInstance, uint8_t address)
{
  if(NULL != lcdInstance)
  {
    if(PCF8574MAXaDDRESS >= address && PCF8574MINaDDRESS <= address)
      lcdInstance->address = address;
    else
      lcdInstance->address = PCF8574MAXaDDRESS;
  }
}

/**
  * @brief  get the backlight state.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @retval returns the backlight state.
  */
backlight_t API_HD44780_GetBacklight(API_HD44780_t lcdInstance)
{
  if(NULL != lcdInstance)
    return lcdInstance->backLight;
  return BACKLIGHToFF;
}

/**
  * @brief  set new backlight state.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  backLight: the new backlight state.
  * @retval None.
  */
void API_HD44780_SetBacklight(API_HD44780_t lcdInstance, backlight_t backLight)
{
  if(NULL != lcdInstance)
  {
    if(BACKLIGHToN == backLight || BACKLIGHToFF == backLight)
      lcdInstance->backLight = backLight;
    else
      lcdInstance->backLight = BACKLIGHToN;
  }
}

/**
  * @brief  Initialize API_HD44780_s structure and device.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  address:
  * @param  backLight:
  * @retval API_HD44780_t.
  */
API_HD44780_t API_HD44780_Init(uint8_t address, backlight_t backLight)
{
  static struct API_HD44780_s this = {0};

  API_HD44780_SetAddress(&this, address);
  API_HD44780_SetBacklight(&this, backLight);
  API_HD44780_InitLCD(&this);

  return &this;
}

/**
  * @brief  Initialize the HD44780 LCD.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @retval None.
  */
static void API_HD44780_InitLCD(API_HD44780_t lcdInstance)
{
  const uint8_t initCommands[] = {
                                   BYTEmODE+1, BYTEmODE, NIBBLEmODE,
                                   DISPLAYmODE|DMdISPLAYoFF|DMcURSORoFF,
		                               RETURNhOME, ENTRYmODE|EMnORMAL|EMiNCREMENT,
                                   DISPLAYmODE|DMdISPLAYoN|DMcURSORoFF, CLEARdISPLAY
                                 };
  const uint8_t MAXcOMMANDS = sizeof(initCommands)/sizeof(initCommands[0]);

  if(NULL != lcdInstance)
  {
    for(uint8_t i=0; i<MAXcOMMANDS; i++)
      API_HD44780_Write_Data(lcdInstance, initCommands[i], RScMD, RWwRITE);
  }
}

/**
  * @brief  Clear Display and set cursor to start of first line.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @retval None.
  */
void API_HD44780_ClearDisplay(API_HD44780_t lcdInstance)
{
  if(NULL != lcdInstance)
  {
    API_HD44780_Write_Data(lcdInstance, CLEARdISPLAY, RScMD, RWwRITE);
    API_HD44780_HAL_Delay(DELAY1MS);
  }
}

/**
  * @brief  Write a character to LCD
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  ascii: valid ASCII character to write to LCD
  * @retval None.
  */
void API_HD44780_SendChar(API_HD44780_t lcdInstance, uint8_t ascii)
{
  if(NULL != lcdInstance && (VALIDmINaSCII <= ascii || VALIDmAXaSCII >= ascii))
    API_HD44780_Write_Data(lcdInstance, ascii, RSdATA, RWwRITE);
}

/**
  * @brief  Wire a string to the LCD
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  string: string of valid ASCII character to write to LCD
  * @retval None.
  */
void API_HD44780_SendString(API_HD44780_t lcdInstance, uint8_t *string)
{
  if(NULL != lcdInstance)
    while(NULL != string && EOL != *string)
      API_HD44780_SendChar(lcdInstance, *(string++));
}

/**
  * @brief  Set cursor to a specific position on the LCD
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  line: the specific line to set the cursor
  * @param  offset: the specific offset to set the cursor
  * @retval None.
  */
void API_HD44780_SetCursor(API_HD44780_t lcdInstance, uint8_t line, uint8_t offset)
{
  if(NULL != lcdInstance && (LINE1 == line || LINE2 == line) && DISPLAYlINEsIZE > offset)
    API_HD44780_Write_Data(lcdInstance, SETDDRAM | ((LINE2 == line?LINE2aDDRESS:LINE1aDDRESS) + offset), RScMD, RWwRITE);
}

/*----------------------------------------------------------------------------*/

/* Private API code ----------------------------------------------------------*/

/**
  * @brief  Write a byte of payload to I2C port hardware specific.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  payload: byte of payload to write to the I2C byte.
  * @param  rs: select the instruction register or the data register.
  * @param  rw: perform read or write operation.
  * @retval None.
  */
static void API_HD44780_Write_Data(API_HD44780_t lcdInstance, uint8_t payload, uint8_t rs, uint8_t rw)
{
  if(NULL != lcdInstance && (RScMD == rs || RSdATA == rs) && (RWwRITE == rw || RWrEAD == rw))
  {
    API_HD44780_Write_DataNibble(lcdInstance, payload &  MSnIBBLE, rs, rw); // write Most Significant Nibble first
    API_HD44780_Write_DataNibble(lcdInstance, (payload << LSnIBBLE) & MSnIBBLE, rs, rw); // write Less Significant Nibble next
  }
}

/**
  * @brief  Write high nibble of data --> [D7 D6 D5 D4] and low nibble of settings -->[ BL E RW RS] to I2C port hardware specific.
  * @param  lcdInstance: pointer to the LCD instance structure.
  * @param  nibble: nibble of data to write to the I2C byte.
  * @param  rs: select the instruction register or the data register.
  * @param  rw: perform read or write operation.
  * @retval None.
  */
static void API_HD44780_Write_DataNibble(API_HD44780_t lcdInstance, uint8_t nibble, uint8_t rs, uint8_t rw)
{
  if(NULL != lcdInstance && (RScMD == rs || RSdATA == rs) && (RWwRITE == rw || RWrEAD == rw))
  {
    API_HD44780_HAL_I2C_Write(lcdInstance, nibble | lcdInstance->backLight |  ENsET  | rw | rs);
    API_HD44780_HAL_Delay(DELAY1MS);
    API_HD44780_HAL_I2C_Write(lcdInstance, nibble | lcdInstance->backLight | ENuNSET | rw | rs);
    API_HD44780_HAL_Delay(DELAY1MS);
  }
}
