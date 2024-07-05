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
 *    │ P0 P1 P2 P3 P4 P5 P6 P7  │
 *    └──┬──┬──┬──┬──┬──┬──┬──┬──┘
 *       │  │  │  *  │  │  │  │
 *    ┌──┴──┴──┴─────┴──┴──┴──┴──┐
 *    │ RS RW  E    D4 D5 D6 D7  │
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

#define RScMD      0x00
#define RSdATA     0x01
#define RWwRITE    0x00
#define RWrEAD     0x02
#define ENuNSET    0x00
#define ENsET      0x04
#define BLoFF      0x00
#define BLoN       0x08

#define PCF8574MINaDDRESS 0x20
#define PCF8574MAXaDDRESS 0x27

/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct API_HD44780_s *API_HD44780_t;

typedef enum { BACKLIGHToN = BLoN, BACKLIGHToFF = BLoFF } backlight_t;

/*----------------------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

void API_HD44780_Init(API_HD44780_t lcdInstance, uint8_t address, backlight_t backLight);

/*----------------------------------------------------------------------------*/

#endif /* API_HD44780_INC_API_HD44780_H_ */
