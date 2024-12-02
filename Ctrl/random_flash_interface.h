//
// Created by chl on 2024/12/2.
//

#ifndef RANDOM_FLASH_INTERFACE_H
#define RANDOM_FLASH_INTERFACE_H

#if !(defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3) || defined(STM32F4) || defined(STM32F7) || \
defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7) || defined(STM32G0) || defined(STM32G4) || \
defined(STM32WB) || defined(STM32MP1) || defined(STM32L5))
#error This code is intended to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

// Only use this with emulated EEPROM, without integrated EEPROM
#if !defined(DATA_EEPROM_BASE)

#include "random_flash_utils.h"

#endif //RANDOM_FLASH_INTERFACE_H
