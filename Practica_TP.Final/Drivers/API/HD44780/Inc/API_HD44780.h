/*
 * API_HD44780.h
 *
 *  Created on: Jul 4, 2024
 *      Author: raxt
 *
 *  Hardware Connection according Schematics
 *
 *    ┌──────────────────────────┐
 *    │         PCF8574          │
 *    │                          │
 *    │ P7 P6 P5 P4 P3 P2 P1 P0  │
 *    └──┬──┬──┬──┬──┬──┬──┬──┬──┘
 *       │  │  │  |  *  │  │  │
 *    ┌──┴──┴──┴──┴─────┴──┴──┴──┐
 *    │ D7 D6 D5 D4    EN RW RS  │
 *    │                          │
 *    │         HD44780          │
 *    └──────────────────────────┘
 *  * P3 is connected to a transistor that turns on/off the backlight
 *  Reference: https://msoe.us/taylor/tutorial/ce2800/lcddisplay.htm
 */

#ifndef API_HD44780_INC_API_HD44780_H_
#define API_HD44780_INC_API_HD44780_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define PCF8574MINaDDRESS 0x20
#define PCF8574MAXaDDRESS 0x27
#define VALIDmINaSCII     0x20  // space
#define VALIDmAXaSCII     0x7F  // HD44780 datasheet table 4 "Correspondence between Character Codes and Character Patterns"
#define DISPLAYlINES      2
#define DISPLAYlINEsIZE   16
#define LINE1		      0x01
#define LINE2		      0x02
#define NOaDDRESS         0

/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct API_HD44780_s * API_HD44780_t;

typedef enum { BACKLIGHToN = 0x08, BACKLIGHToFF = 0x00 } backlight_t;

/*----------------------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

API_HD44780_t API_HD44780_Init(uint8_t address, backlight_t backLight);
void API_HD44780_ClearDisplay(API_HD44780_t lcdInstance);
void API_HD44780_SendChar(API_HD44780_t lcdInstance, uint8_t ascii);
void API_HD44780_SendString(API_HD44780_t lcdInstance, uint8_t *string);
void API_HD44780_SetCursor(API_HD44780_t lcdInstance, uint8_t line, uint8_t offset);

uint8_t     API_HD44780_GetAddress(API_HD44780_t lcdInstance);
void        API_HD44780_SetAddress(API_HD44780_t lcdInstance, uint8_t address);
backlight_t API_HD44780_GetBacklight(API_HD44780_t lcdInstance);
void        API_HD44780_SetBacklight(API_HD44780_t lcdInstance, backlight_t backLight);

/*----------------------------------------------------------------------------*/

#endif /* API_HD44780_INC_API_HD44780_H_ */
