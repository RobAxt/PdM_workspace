## Driver PN532
 **Type:** Polled Driver
 **Objective:** Read the RFID Tags using the PN532 IC, the hardware use could be found [here](https://www.elechouse.com/elechouse/images/product/PN532_module_V3/PN532_shematic_drowing.pdf). The datasheet could be found [here](https://www.nxp.com/docs/en/nxp/data-sheets/PN532_C1.pdf) and the user manual [here](https://www.nxp.com/docs/en/user-guide/141520.pdf).
 
## **Files:**
**Include files:**
> /Driver/API/PN532/Inc/API_PN532_HAL.h
> /Driver/API/PN532/Inc/API_PN532.h

**Source Files**
> /Driver/API/PN532/Src/API_PN532_HAL.c
> /Driver/API/PN532/Src/API_PN532.c

* The logic of the driver is written in **API_PN532.c**, while the hardware specific code for the STM32F429zi is in the file **API_PN532_HAL.c** using the HAL abstraction layer provided by STM32.
*  The current version of this driver only allow to retrieve the firmware version.revision, the IC version and the supported Tag.
* Also is limited to read only MIFARE Classic Tags, with the UID size of 4 bytes.

## Interface

```c

/**
* @brief function to retrieve the current tad  readed
* @param PN532_t instance: pointer to the hidden structure.
* @param uint8_t *uid: poiter to the allocated array that will contain the tad  uid
* @param  const uint8_t size: the size of the tag uid
* @retval uint8_t: if ok, return the size of the uid tag; otherwise, it indicates that
* the instance was not initialized.
*/
uint8_t  API_PN532_GetTag(PN532_t instance, uint8_t *uid, const  uint8_t size);

/*----------------------------------------------------------------------------*/

/**
* @brief Get the IC version
* @param PN532_t instance: pointer to the hidden structure.
* @retval uint8_t: return IC version if ok; otherwise it will indicate that the instance was
* not initialized..
*/
uint8_t  API_PN532_GetIC(PN532_t instance);

/*----------------------------------------------------------------------------*/

/**
* @brief Get the firmware version
* @param PN532_t instance: pointer to the hidden structure.
* @retval uint8_t: return firmware version if ok; otherwise it will indicate that the instance was
* not initialized..
*/
uint8_t  API_PN532_GetVersion(PN532_t instance);

/*----------------------------------------------------------------------------*/

/**
* @brief Get the IC revision
* @param PN532_t instance: pointer to the hidden structure.
* @retval uint8_t: return IC revision if ok; otherwise it will indicate that the instance was
* not initialized..
*/
uint8_t  API_PN532_GetRevision(PN532_t instance);

/*----------------------------------------------------------------------------*/

/**
* @brief Get the type of tags supported
* @param PN532_t instance: pointer to the hidden structure.
* @retval uint8_t: return the type of tags supported if ok; otherwise it will indicate
* that the instance was not initialized..
*/
uint8_t  API_PN532_GetSupport(PN532_t instance);

/*----------------------------------------------------------------------------*/

/**
* @brief Initialize the elements of the structure and send the SAM Config
* command to the PN532 to enable the reading of the tags.
* @param None
* @retval PN532_t: returns the pointer to the hidden structure
*/
PN532_t  API_PN532_Init(void);

/*----------------------------------------------------------------------------*/

/**
* @brief Read the UID of the Tag if it is present.
* @param PN532_t instance: pointer to the hidden structure.
* @retval PN532_Error_t: enum that indicates the status of the transaction with the PN532.
*/
PN532_Error_t  API_PN532_ReadTag(PN532_t instance)

/*----------------------------------------------------------------------------*/
```