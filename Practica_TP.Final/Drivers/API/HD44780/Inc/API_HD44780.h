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
 */

#ifndef API_HD44780_INC_API_HD44780_H_
#define API_HD44780_INC_API_HD44780_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define BLoFF      0x00
#define BLoN       0x08

#define PCF8574MINaDDRESS 0x20
#define PCF8574MAXaDDRESS 0x27

/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct API_HD44780_s * API_HD44780_t;

typedef enum { BACKLIGHToN = BLoN, BACKLIGHToFF = BLoFF } backlight_t;

/*----------------------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

void API_HD44780_Init(API_HD44780_t lcdInstance, uint8_t address, backlight_t backLight);
void API_HD44780_ClearDisplay(API_HD44780_t lcdInstance);

uint8_t     API_HD44780_GetAddress(API_HD44780_t lcdInstance);
void        API_HD44780_SetAddress(API_HD44780_t lcdInstance, uint8_t address);
backlight_t API_HD44780_GetBacklight(API_HD44780_t lcdInstance);
void        API_HD44780_SetBacklight(API_HD44780_t lcdInstance, backlight_t backLight);

/*----------------------------------------------------------------------------*/

#endif /* API_HD44780_INC_API_HD44780_H_ */
