/**
 * Marlin 3D Printer Firmware
 *
 * Copyright (C) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 * Copyright (c) 2016 Bob Cousins bobcousins42@googlemail.com
 * Copyright (c) 2015-2016 Nico Tonnhofer wurstnase.reprap@gmail.com
 * Copyright (c) 2016 Victor Perez victor_pv@hotmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * persistent_store_flash.cpp
 * HAL for stm32duino and compatible (STM32F1)
 * Implementation of EEPROM settings in SDCard
 */

#ifdef __STM32F1__

#include "../../inc/MarlinConfig.h"

// This is for EEPROM emulation in flash
#if BOTH(EEPROM_SETTINGS, FLASH_EEPROM_EMULATION)

#include "../shared/persistent_store_api.h"

#include <flash_stm32.h>
#include <EEPROM.h>

// Store settings in the last two pages
// Flash pages must be erased before writing, so keep track.
uint32_t pageBase = EEPROM_START_ADDRESS;
uint32_t maxSize = 0;
#define EEPROM_SIZE (EEPROM_PAGE_SIZE*2)
static uint8_t ram_eeprom[EEPROM_SIZE] __attribute__((aligned(4))) = {0};

bool PersistentStore::access_start() {
  uint8_t *eeprom_data = (uint8_t *)pageBase;
  // load current settings
  for (int i = 0; i < EEPROM_SIZE; i++) ram_eeprom[i] = eeprom_data[i];
  maxSize = 0;
  return true;
}

bool PersistentStore::access_finish() {
  FLASH_Status status;
  if (maxSize && memcmp((void *)ram_eeprom, (void *)EEPROM_START_ADDRESS, maxSize) != 0) {
    FLASH_Unlock();
    status = FLASH_ErasePage(EEPROM_PAGE0_BASE);
    if (status == FLASH_COMPLETE)
    {
      status = FLASH_ErasePage(EEPROM_PAGE1_BASE);
      if (status == FLASH_COMPLETE){
        uint32_t size = (maxSize + 1) & ~1;
        uint16_t *eeprom_data = (uint16_t *)ram_eeprom;
        for (uint32_t i=0; i<size/2; i++){
          status = FLASH_ProgramHalfWord(pageBase + i*2, eeprom_data[i]);
          if (status != FLASH_COMPLETE) break;
        }
      }
    }
    FLASH_Lock();
  }
  return true;
}

bool PersistentStore::write_data(int &pos, const uint8_t *value, size_t size, uint16_t *crc) {
  for (size_t i = 0; i < size; i++) ram_eeprom[pos + i] = value[i];
  crc16(crc, value, size);
  pos += size;
  maxSize = MAX(maxSize, pos);
  return false;  // return true for any error
}

bool PersistentStore::read_data(int &pos, uint8_t* value, size_t size, uint16_t *crc, const bool writing/*=true*/) {
  const uint8_t * const buff = writing ? &value[0] : &ram_eeprom[pos];
  if (writing) for (size_t i = 0; i < size; i++) value[i] = ram_eeprom[pos + i];
  crc16(crc, buff, size);
  pos += size;
  return false;  // return true for any error
}

size_t PersistentStore::capacity() { return EEPROM_SIZE; }

#endif // EEPROM_SETTINGS && EEPROM FLASH
#endif // __STM32F1__
