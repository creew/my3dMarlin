/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
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
  * 2017 Victor Perez Marlin for stm32f1 test
  * 2018 Modified by Pablo Crespo for Morpheus Board (https://github.com/pscrespo/Morpheus-STM32)
  * 11.2018 Modified by 3dmaniack for fork of Morpheus Board
  */

//
// MORPHEUS Board pin assignments
//

#ifndef __STM32F1__
  #error "Oops!  Make sure you have an STM32F1 board selected from the 'Tools -> Boards' menu."
#endif

#define BOARD_NAME "Bluepill based board"

//
// Limit Switches
//
#define X_MIN_PIN          PB9
//#define Y_MIN_PIN          PB3
//#define Z_MIN_PIN          PA9
//#define X_MAX_PIN          PB9
#define Y_MAX_PIN          PB3
#define Z_MAX_PIN          PA9



//
// Steppers
//
// X & Y enable are the same
#define X_STEP_PIN         PB7
#define X_DIR_PIN          PB6
#define X_ENABLE_PIN       PB8

#define Y_STEP_PIN         PB5
#define Y_DIR_PIN          PB4
#define Y_ENABLE_PIN       PB8

#define Z_STEP_PIN         PA15
#define Z_DIR_PIN          PA10
#define Z_ENABLE_PIN       PB8

#define E0_STEP_PIN        PA8
#define E0_DIR_PIN         PB15
#define E0_ENABLE_PIN      PB8

//
// Temperature Sensors
//
#define TEMP_0_PIN         PB1   // Analog Input (HOTEND thermistor)
#define TEMP_BED_PIN       PB0   // Analog Input (BED thermistor)

//
// Heaters / Fans
//
#define HEATER_0_PIN       PA2   // HOTEND MOSFET
#define HEATER_BED_PIN     PA0   // BED MOSFET

#define FAN_PIN            PA1   // FAN1 header on board - PRINT FAN


//Encoder
#define BTN_EN1           PC15
#define BTN_EN2           PC14
#define BTN_ENC           PC13

// SDCard
#define SDSS               PA4
#define SD_DETECT_PIN     -1
#define KILL_PIN          -1

//LCD REPRAP_DISCOUNT_SMART_CONTROLLER
//
 //#define LCD_PINS_RS         PB12
 //#define LCD_PINS_ENABLE     PB13
 //#define LCD_PINS_D4         PB14
 //#define LCD_PINS_D5         PA3
 //#define LCD_PINS_D6         PB10
 //#define LCD_PINS_D7         PB11

//LCD MKS_MINI_12864
//
 //#define DOGLCD_CS         PA3
 //#define DOGLCD_A0         PB10

 // GLCD features
 //
 //#define LCD_CONTRAST   190

 // Uncomment screen orientation
 //
 //#define LCD_SCREEN_ROT_90
 //#define LCD_SCREEN_ROT_180
 //#define LCD_SCREEN_ROT_270
