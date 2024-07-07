/*
 * API_PN532.h
 *
 *  Created on: Jul 6, 2024
 *      Author: raxt
 */

#ifndef API_PN532_INC_API_PN532_H_
#define API_PN532_INC_API_PN532_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <string.h>

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define APIpN532eRROR 0x80
#define MAXUIDsIZE 		10 	// More Info @ --> https://www.nfc-tag-shop.de/info/en/knowledge/uid-uniquely-identify-and-clone-nfc-tags/

/*----------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

typedef struct tag_s * tag_t;

/*----------------------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

void   API_PN532_Init(tag_t tag);
int8_t API_PN532_ReadTag(tag_t tag);
int8_t API_PN532_GetTag(tag_t tag, uint8_t *UID, const uint8_t size);
void   API_PN532_SetTag(tag_t tag, const uint8_t * const UID, const uint8_t size);

/*----------------------------------------------------------------------------*/

#endif /* API_PN532_INC_API_PN532_H_ */
