/*
 * API_PN532.h
 *
 *  Created on: Jul 6, 2024
 *      Author: raxt
 *       TODO:  Optimize interrogation sequence in a generic private function.
 */

#ifndef API_PN532_INC_API_PN532_H_
#define API_PN532_INC_API_PN532_H_

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define MAXUIDsIZE 		10 	// More Info @ --> https://www.nfc-tag-shop.de/info/en/knowledge/uid-uniquely-identify-and-clone-nfc-tags/
#define PN532aDDRESS  0x24
#define NOTiNITIALIZED   0
/*----------------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct PN532_s * PN532_t;

typedef enum {
  PN532oK = 0,
  PN532bADaCK,
  PN532nOaCK,
  PN532bADcOMMAND,
  PN532bADrESPONSE,
  PN532nOtAG,
  PN532nOTiNITIALIZED
} PN532_Error_t;

/*----------------------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

PN532_t       API_PN532_Init();
PN532_Error_t API_PN532_ReadTag(PN532_t instance);

uint8_t API_PN532_GetTag(PN532_t instance, uint8_t *uid, const uint8_t size);
uint8_t API_PN532_GetIC(PN532_t instance);
uint8_t API_PN532_GetVersion(PN532_t instance);
uint8_t API_PN532_GetRevision(PN532_t instance);
uint8_t API_PN532_GetSupport(PN532_t instance);

/*----------------------------------------------------------------------------*/

#endif /* API_PN532_INC_API_PN532_H_ */
