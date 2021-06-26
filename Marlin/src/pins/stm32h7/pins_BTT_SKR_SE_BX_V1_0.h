/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#ifndef STM32H7
  #error "Oops! Select an STM32H7 board in 'Tools > Board.'"
#endif

#define BOARD_INFO_NAME      "BTT SKR SE-BX V1.0"
#define DEFAULT_MACHINE_NAME "BIQU-BX"

// QSPI Flash
#define HAS_QSPI_FLASH                   1
// #define HAS_SPI_FLASH                    1

// Onboard I2C EEPROM
#define I2C_EEPROM
#define MARLIN_EEPROM_SIZE                0x1000  // 4KB (24C32 ... 32Kb = 4KB)

//
// Limit Switches
//
#define X_MIN_PIN                           PB11
//#define X_MAX_PIN                           PD13
#define Y_MIN_PIN                           PB12
#define Y_MAX_PIN                           PB13
#ifdef Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN
  #define Z_MIN_PIN                         PH2
#else
  #define Z_MIN_PIN                         PD12
#endif
//#define Z_MAX_PIN                           PD11

#define FIL_RUNOUT_PIN                      PD13
#define FIL_RUNOUT2_PIN                     PB13

#ifdef BTT_SKR_SE_BX_WITHBOOT
  //#define LED_PIN                             PA13
  #define POWER_LOSS_BUFFER_PIN             PA13      // Used to buffer the power loss signal to the pi.
  #define BEEPER_PIN                          PA14
#endif

#define POWER_MONITOR_PIN                   PB0
#define SAFE_POWER_PIN                      PI11
#define RPI_POWER_PIN                       PE5

#define SERVO0_PIN                          PA2

//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN                   PH2  // Probe
#endif

//
// Steppers
//
#define X_STEP_PIN                          PG13
#define X_DIR_PIN                           PG12
#define X_ENABLE_PIN                        PG14
#define X_CS_PIN                            PG10

#define Y_STEP_PIN                          PB3
#define Y_DIR_PIN                           PD3
#define Y_ENABLE_PIN                        PB4
#define Y_CS_PIN                            PD4


#define Z2_STEP_PIN                          PA8
#define Z2_DIR_PIN                           PC9
#define Z2_ENABLE_PIN                        PD2
#define Z2_CS_PIN                            PC8

#define Z_STEP_PIN                         PD7
#define Z_DIR_PIN                          PD6
#define Z_ENABLE_PIN                       PG9
#define Z_CS_PIN                           PD5

#define E0_STEP_PIN                         PC14
#define E0_DIR_PIN                          PC13
#define E0_ENABLE_PIN                       PC15
#define E0_CS_PIN                           PI8

//
// Software SPI pins for TMC2130 stepper drivers
//
#if ENABLED(TMC_USE_SW_SPI)
  #ifndef TMC_SW_MOSI
    #define TMC_SW_MOSI                     PC6
  #endif
  #ifndef TMC_SW_MISO
    #define TMC_SW_MISO                     PG3
  #endif
  #ifndef TMC_SW_SCK
    #define TMC_SW_SCK                      PC7
  #endif
#endif

#if HAS_TMC_UART
  /**
   * TMC2208/TMC2209 stepper drivers
   *
   * Hardware serial communication ports.
   * If undefined software serial is used according to the pins below
   */
  //#define X_HARDWARE_SERIAL  Serial
  //#define X2_HARDWARE_SERIAL Serial1
  //#define Y_HARDWARE_SERIAL  Serial1
  //#define Y2_HARDWARE_SERIAL Serial1
  //#define Z_HARDWARE_SERIAL  Serial1
  //#define Z2_HARDWARE_SERIAL Serial1
  //#define E0_HARDWARE_SERIAL Serial1
  //#define E1_HARDWARE_SERIAL Serial1
  //#define E2_HARDWARE_SERIAL Serial1
  //#define E3_HARDWARE_SERIAL Serial1
  //#define E4_HARDWARE_SERIAL Serial1
  //#define E5_HARDWARE_SERIAL Serial1
  //#define E6_HARDWARE_SERIAL Serial1
  //#define E7_HARDWARE_SERIAL Serial1

  //
  // Software serial
  //
  #define X_SERIAL_TX_PIN                   PG10
  #define X_SERIAL_RX_PIN                   PG10

  #define Y_SERIAL_TX_PIN                   PD4
  #define Y_SERIAL_RX_PIN                   PD4

  #define Z2_SERIAL_TX_PIN                   PC8
  #define Z2_SERIAL_RX_PIN                   PC8

  #define Z_SERIAL_TX_PIN                  PD5
  #define Z_SERIAL_RX_PIN                  PD5

  #define E0_SERIAL_TX_PIN                  PI8
  #define E0_SERIAL_RX_PIN                  PI8

  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE                     19200
#endif

//
// Temperature Sensors
//
#define TEMP_0_PIN                          PH4  // TH0
#define TEMP_1_PIN                          PA3  // TH1
#define TEMP_BED_PIN                        PH5  // TB

//
// Heaters / Fans
//
#define HEATER_0_PIN                        PC4
#define HEATER_1_PIN                        PC5
#define HEATER_BED_PIN                      PA4

#define FAN_PIN                             PA5  // "FAN0"
#define FAN1_PIN                            PA6  // "FAN1"
//#define CONTROLLER_FAN_PIN                PA7
//#define FAN2_PIN                            PA7  // "FAN2"

#define NEOPIXEL_PIN                        PH3
#define NEOPIXEL2_PIN                       PB1

#ifndef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN                   PA7
#endif

#if HAS_LTDC_TFT

  #define TFT_WIDTH                         1024
  #define TFT_HEIGHT                        600
  #define GRAPHICAL_TFT_UPSCALE             4
  #define TFT_PIXEL_OFFSET_X                ((TFT_WIDTH - GRAPHICAL_TFT_UPSCALE * 128) / 2)
  #define TFT_PIXEL_OFFSET_Y                ((TFT_HEIGHT - GRAPHICAL_TFT_UPSCALE * 64) / 2)

#endif

#define BTN_EN1                             PH6
#define BTN_EN2                             PH7
#define BTN_ENC                             PH8

#ifndef SDCARD_CONNECTION
  #define SDCARD_CONNECTION ONBOARD
#endif

//
// By default the LCD SD (SPI2) is enabled
// Onboard SD is on a completely separate SPI bus, and requires
// overriding pins to access.
//

#define BSD_DETECT_PIN                      PB10
#define BSDSS                               PA15

#define SOFTWARE_SPI
#define SDSS                                PC1
#define SS_PIN                              SDSS
#define SCK_PIN                             PC10
#define MISO_PIN                            PC11
#define MOSI_PIN                            PC12
#define SD_DETECT_PIN                       PI3
