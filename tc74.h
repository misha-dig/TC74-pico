/**
 * Copyright (C) 2023 by Misha Zaslavskis   
 * License is BSD 3-Clause
*/

/**
 * @file tc74.h
 * @author Misha Zaslavskis
 * @date 19th July 2024
 * @brief A header file of TC74 sensor measuring temperature functionality 
 * @see See in tc74.c code
 * 
 * */

#ifndef __TC74_H__
#define __TC74_H__

/**
 * @brief I2C sensor address diffrent depending TC74 series sensor part model. You can look a datasheet of TC74. This I2C address for TC74A0-xxVAT or TC74A0-xxVCTTR: 
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
 * Note: I convert into hex from binary address via calculalor which I took official TC74 datasheet that people able read I2C address of TC74 sensor
*/
#define I2C_ADDRESS_A0 0x48
/**
 * @brief I2C sensor address diffrent depending TC74 series sensor part model. You can look a datasheet of TC74. This I2C address for TC74A1-xxVAT or TC74A1-xxVCTTR: 
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
 * Note: I convert into hex from binary address via calculalor which I took official TC74 datasheet that people able read I2C address of TC74 sensor
*/
#define I2C_ADDRESS_A1 0x49
/**
 * @brief I2C sensor address diffrent depending TC74 series sensor part model. You can look a datasheet of TC74. This I2C address for TC74A2-xxVAT or TC74A2-xxVCTTR: 
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
 * Note: I convert into hex from binary address via calculalor which I took official TC74 datasheet that people able read I2C address of TC74 sensor
*/
#define I2C_ADDRESS_A2 0x4A
/**
 * @brief I2C sensor address diffrent depending TC74 series sensor part model. You can look a datasheet of TC74. This I2C address for TC74A3-xxVAT or TC74A3-xxVCTTR: 
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
 * Note: I convert into hex from binary address via calculalor which I took official TC74 datasheet that people able read I2C address of TC74 sensor
*/
#define I2C_ADDRESS_A3 0x4B
/**
 * @brief I2C sensor address diffrent depending TC74 series sensor part model. You can look a datasheet of TC74. This I2C address for TC74A4-xxVAT or TC74A4-xxVCTTR: 
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
 * Note: I convert into hex from binary address via calculalor which I took official TC74 datasheet that people able read I2C address of TC74 sensor
*/
#define I2C_ADDRESS_A4 0x4C
/**
 * @brief I2C sensor address diffrent depending TC74 series sensor part model. You can look a datasheet of TC74. This I2C address for TC74A5-xxVAT or TC74A5-xxVCTTR: 
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
 * Note: I convert into hex from binary address via calculalor which I took official TC74 datasheet that people able read I2C address of TC74 sensor
*/
#define I2C_ADDRESS_A5 0x4D
/**
 * @brief I2C sensor address diffrent depending TC74 series sensor part model. You can look a datasheet of TC74. This I2C address for TC74A6-xxVAT or TC74A6-xxVCTTR: 
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
 * Note: I convert into hex from binary address via calculalor which I took official TC74 datasheet that people able read I2C address of TC74 sensor
*/
#define I2C_ADDRESS_A6 0x4E
/**
 * @brief I2C sensor address diffrent depending TC74 series sensor part model. You can look a datasheet of TC74. This I2C address for TC74A7-xxVAT or TC74A7-xxVCTTR: 
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
 * Note: I convert into hex from binary address via calculalor which I took official TC74 datasheet that people able read I2C address of TC74 sensor
*/
#define I2C_ADDRESS_A7 0x4F

/**
 * @brief A definition of maximum I2C baudrate for TC74 sensor device. Maximum I2C baudrate is 100 kHz. Please see offical datasheet in section "1.0 ELECTRICAL CHARACTERISTICS" page
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
*/
#define I2C_SPEED_FOR_TC74 1000 * 100

/**
 * @brief A definition of I2C command that able read current temperature for TC74 sensor. Please see offical datasheet in section "4.0 REGISTER SET AND PROGRAMMER’S MODEL" page
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf 
*/
#define RTR  0x00
/**
 * @brief A definition of I2C command that read and write sensor configration. Please see offical datasheet in section "4.0 REGISTER SET AND PROGRAMMER’S MODEL" page.
 * @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf 
*/
#define RWCR 0x01

#include "pico/stdlib.h" /* A standard header file for usage RPI PICO board */
#include <stdlib.h>
#include <stdint.h> /* For using integer values with diffirent bit size */
#include "hardware/i2c.h"/* Header file from RPI Pico SDK C/C++ for usage I2C interface */

/**
 * @brief I2C inferface initialization function for TC74 sensor (default I2C port - i2c0)
 * 
 * If you already initialized default port I2C interface for another application, so you don't need to add function i2c_init_tc74 and just decrase i2c baudrate to 100 KHz (Maximum baudrate for TC74 sensor) if you used higher baudrate I2C for pervious application
 * Use defined values I2C_SPEED_FOR_TC74 to set maximum I2C baudrate for TC74 
 * I2C default port is i2c0
*/
void i2c_init_tc74();

/**
 * @brief A function that retrieve result current temperature from TC74 sensor with specitify I2C address of TC74 sensor
 * 
 * Note: Return value only integer with range (-128 to 127) for temperature and 404 for error status.
 * 
 * @param sensor_address An I2C address of TC74 series sensor, dependent which model of TC74 sensor. Please look a datasheet of TC74. 
 * @param temp_offset A temperature offset that can support more accuracy and real measurement temperature (You can setting increase and decrease by minus sign)
 * @return @c int16_t Current temperature data if TC74 sensor is worked correctly, otherwise will get 404 value if error found with working I2C interface and sensor. 
*/
int16_t get_temperature_tc74(uint8_t sensor_address, int8_t temp_offset);

/**
 * @brief A function that TC74 sensor setting power saving (standby) mode to avoid unwanted energy/power cosumption. Ideally for devices with powered by small baterry.
 * 
 * @param sensor_address An I2C address of TC74 series sensor, dependent which model of TC74 sensor. Please look a datasheet of TC74. 
 * @param enable_standby Enable standby mode (power down TC74 sensor and unable to measurement temperature unless turn off standby mode). 
 * true / 1 value is means that standby mode activated and false / 0 value is means normal mode of device.
 * @return @c int8_t A value of status after I2C data writting. 
 * Zero return value is succesfully activation power mode of this sensor and non-zero value or -1 return value is failed activstion power mode.
*/
int8_t set_standby_mode_tc74(uint8_t sensor_address, uint8_t enable_standby);

/**
 * @brief A function that TC74 sensor retrieve current status (Power mode and Data ready state)
 * 
 * You can check power mode via shift bitwise operation: (for example: uint8_t current_power_mode = get_rwcr_state_of_tc74(I2C_ADDRESS_A4) & (1 << 7); ) 
 * You can check data ready sensor via shift bitwise operation: (for example: uint8_t is_data_ready = get_rwcr_state_of_tc74(I2C_ADDRESS_A4) & (1 << 6); )
 * 
 * @return @c uint8_t A 8-bit register value of TC74 sensor state value. You can look a official TC74 datasheet about sensor status in section "4.0 REGISTER SET AND PROGRAMMER’S MODEL" page
*/
uint8_t get_rwcr_state_of_tc74(uint8_t sensor_address);

/**
 * @brief A function that check TC74 sensor in selected I2C bus address is present in your code. 
 * Depsite that I used some parts of source code in pico-example/i2c/bus_scan/bus_scan.c, may be use for any I2C device due works like I2C scanner by changing not TC74 sensor.
 * NB: never connect sensor with same exact model/address which may be create confict or non-workable your circuit and code.
 * For example, two TC74A4 in the same I2C bus - never to do! Instead this stupid mistake, use TC74A4 and TC74A0 sensor in the same bus which will works without any consequences.
 * @param sensor_address An I2C address of TC74 series sensor, dependent which model of TC74 sensor. Please look a datasheet of TC74.
 * @return @c bool Statement of return value of two-state. True (or '1' state) state is mean present sensor in I2C address. False (or '0' state) is absence or broken TC74 sensor in selected I2C bus address.  
*/
uint8_t is_present_address_tc74(uint8_t sensor_address);

#endif // __TC74_H_