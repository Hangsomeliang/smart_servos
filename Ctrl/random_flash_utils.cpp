//
// Created by 104 on 2024/12/2.
//

#include <string.h>
#include "random_flash_utils.h"

#include <sys/_stdint.h>

#ifdef __cplusplus
extern "C" {

#endif
/* Be able to change FLASH_BANK_NUMBER to use if relevant */
#if !defined(FLASH_BANK_NUMBER) && \
    (defined(STM32F0xx) || defined(STM32F1xx) || defined(STM32G4xx) || \
    defined(STM32H7xx) || defined(STM32L4xx) || defined(STM32L5xx))
/* For STM32F0xx, FLASH_BANK_1 is not defined only FLASH_BANK1_END is defined */
#if defined(STM32F0xx)
#define FLASH_BANK_1 1U
#endif
#if defined(FLASH_BANK_2)
#define FLASH_BANK_NUMBER FLASH_BANK_2
#else
#define FLASH_BANK_NUMBER FLASH_BANK_1
#endif
#ifndef FLASH_BANK_NUMBER
#error "FLASH_BANK_NUMBER could not be defined"
#endif
#endif

/* Be able to change FLASH_DATA_SECTOR to use if relevant */
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx) || \
    defined(STM32H7xx)
#if !defined(FLASH_DATA_SECTOR)
#define FLASH_DATA_SECTOR ((uint32_t)(FLASH_SECTOR_TOTAL - 1))
#else
#ifndef FLASH_BASE_ADDRESS
#error "FLASH_BASE_ADDRESS have to be defined when FLASH_DATA_SECTOR is defined"
#endif
#endif
#endif
/* Be able to change FLASH_PAGE_NUMBER to use if relevant */
#if !defined(FLASH_PAGE_NUMBER) && \
    (defined (STM32G0xx) || defined(STM32G4xx) || defined (STM32L4xx) || \
    defined (STM32L5xx) || defined(STM32WBxx))
#define FLASH_PAGE_NUMBER ((uint32_t)((FLASH_SIZE / FLASH_PAGE_SIZE) - 1))
#endif

/* Be able to change FLASH_END to use */
#define FLASH_END FLASH_BANK1_END

#if !defined(FLASH_END)
#if defined(STM32F0xx) || defined(STM32F1xx)
#if defined(FLASH_BANK2_END) && (FLASH_BANK_NUMBER == FLASH_BANK_2)
#define FLASH_END FLASH_BANK2_END
#elif defined(FLASH_BANK1_END) && (FLASH_BANK_NUMBER == FLASH_BANK_1)
#define FLASH_END FLASH_BANK1_END
#endif

#elif defined (STM32F3xx)
static inline uint32_t get_flash_end(void)
{
    uint32_t size;
    switch ((*((uint16_t *)FLASH_SIZE_DATA_REGISTER))) {
        case 0x200U:
            size = 0x0807FFFFU;
            break;
        case 0x100U:
            size = 0x0803FFFFU;
            break;
        case 0x80U:
            size = 0x0801FFFFU;
            break;
        case 0x40U:
            size = 0x0800FFFFU;
            break;
        case 0x20U:
            size = 0x08007FFFU;
            break;
        default:
            size = 0x8003FFFU;
            break;
    }
    return size;
}
#define FLASH_END get_flash_en()
#elif defined(STM32G0xx) || defined(STM32G4xx) || defined (STM32L4xx) || \
defined (STM32L5xx) || defined(STM32WBxx)
/* If FLASH_PAGE_NUMBER is defined by user, this is not really end of the flash */
#define FLASH_END ((uint32_t)(FLASH_BASE + (((FLASH_PAGE_NUMBER + 1) * FLASH_PAGE_SIZE))-1))
#elif defined(EEPROM_RETRAM_MODE)
#define FLASH_END ((uint32_t)(EEPROM_RETRAM_START_ADDRESS + EEPROM_RETRAM_MODE_SIZE -1))
#elif defined(DATA_EEPROM_END)
#define FLASH_END DATA_EEPROM_END
#endif
#ifndef FLASH_END
#error "FLASH_END could not be defined"
#endif
#endif

/* Be able to change FLASH_BASE_ADDRESS to use */
#ifndef FLASH_BASE_ADDRESS
/*
 * By default, Use the last page of the flash to store data
 * in order to prevent overwritting
 * program data
 */
#if defined(EEPROM_RETRAM_MODE)
#define FLASH_BASE_ADDRESS EEPROM_RETRAM_START_ADDRESS
#else
#define FLASH_BASE_ADDRESS ((uint32_t)((FLASH_END + 1) - FLASH_PAGE_SIZE))
#endif
#ifndef FLASH_BASE_ADDRESS
#error "FLASH_BASE_ADDRESS could not be defined"
#endif
#endif

#if !defined(DATA_EEPROM_BASE)
static uint8_t eeprom_buffer[E2END + 1] __attribute__((aligned(8))) = {0};
#endif

/**
* @brief  Function reads a byte from emulated eeprom (flash)
* @param  pos : address to read
* @retval byte : data read from eeprom
*/
uint8_t eeprom_read_byte(const uint32_t pos)
{
#if defined(DATA_EEPROM_BASE)
    __IO uint8_t data = 0;
    if
}
