/**
 * Copyright (C) 2023 by Misha Zaslavskis   
 * License is BSD 3-Clause
*/

/**
 * @file tc74.c
 * @author Misha Zaslavskis
 * @date 19th July 2024
 * @brief A source of code that support tc74 temperature sensor in I2C/SMBus inferface for Raspberry Pi Pico / RP2040 MCU
 * TC74 series sensors are tiny simple sensor that able measure temperature anymore for electronics application. (Total three I2C commands in this slave hardware)
 * You can see a datasheet of sensor. @see https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf
 * You can get result temperature with 8 bit signed integer value (-128 to 127) and it has unit degree Celisus.
 * Note: This sensor has accuracy 2-3 degree celisus, plus voltage dependent 1 degree celisus per each volt, so not situable for weather station.
 * Include file: @see tc74.h 
 * We used I2C hardware interface via pico SDK for I2C communication. @see https://www.raspberrypi.com/documentation/pico-sdk/hardware.html
 * Based by code of Arduino library that working with TC74 sensor: @see https://github.com/FaultyTwo/TC74-arduino-lib/tree/master. You can look a license @see https://github.com/FaultyTwo/TC74-arduino-lib/blob/master/LICENSE
 * Thanks you for usage code: @see https://github.com/FaultyTwo
 * */

#include "tc74.h"

void i2c_init_tc74()
{
    i2c_init(i2c_default, I2C_SPEED_FOR_TC74); /* Initialize I2C interface with default port */
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C); /* Set GPIO function as I2C with default RPI Pico Pin for SDA I2C pin */
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C); /* Set GPIO function as I2C with default RPI Pico Pin for SCL I2C pin */
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN); /* Set pull-up internal resistor of MCU for SDA pin */
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN); /* Set pull-up internal resistor of MCU for SCL pin */
}

int16_t get_temperature_tc74(uint8_t sensor_address, int8_t temp_offset)
{
    uint16_t final_data = 0; /* Data return value declaration */

    uint8_t rtr_reg[1] = {RTR}; /* I2C regsiter command value declaration as array method for usage pointer value in I2C function */
    uint8_t rtr_data[1] = {0}; /* I2C result data declaration as array method for usage pointer value in I2C function for retrieve current temperature */
    uint16_t error_value = 404; /* Declaration error value for unsuccesfully I2C data transfering for this sensor */

    /* Check current sensor status that data ready to read current temperature. We used I2C register according TC74 sensor offical datasheet. 
       Should be DATA_RDY equal one to order able read current temperator from this device. 
       [D6] - Data ready, so we used (1 << 6) bitwise shift to determine this state. 
    */
    if (get_rwcr_state_of_tc74(sensor_address) & (1 << 6))
    {
        /* Send I2C command request to sensor address to read current data */
        if (i2c_write_blocking(i2c0, sensor_address, rtr_reg, 1, false) == PICO_ERROR_GENERIC) final_data = error_value;
        /* Read I2C data to retrieve current temperature */
        if (i2c_read_blocking(i2c0, sensor_address, rtr_data, 1, true) == PICO_ERROR_GENERIC) final_data = error_value;
        else final_data = rtr_data[0] + temp_offset; /* Assign return value current received temperature with settings offset */
    }
    else final_data = error_value; /* Assign return error value if I2C data transfred unluckily */

    sleep_us(5); /* I2C Bus delay to avoid I2C transfer error for sensor for next start I2C transfer (Mimimum value is 4.7 microseconds) */

    return final_data; /* Return final data (current temperature + offset or error value) */
}

int8_t set_standby_mode_tc74(uint8_t sensor_address, uint8_t enable_standby)
{
    uint8_t rwcr_status_ackw = 0x00 | (enable_standby << 7); /* Declaration register value of config TC74 sensor for setting power mode, see in official datasheet of TC74 sensor */
    uint8_t write_config_protocol[] = {RWCR, rwcr_status_ackw}; /* I2C regsiter command value declaration as array for sending multiple values in I2C interface */

    /* Write I2C data for sensor setting power mode (Data: Command + power mode (sensor configuration)) */
    if (i2c_write_blocking(i2c0, sensor_address, write_config_protocol, 2, true) == PICO_ERROR_GENERIC) return -1; /* Return non-zero value if I2C writing data error for this sensor */

    sleep_us(5); /* I2C Bus delay to avoid I2C transfer error for sensor for next start I2C transfer (Mimimum value is 4.7 microseconds) */

    return 0; /* Return that correct set power mode of TC74 sensor */
}

uint8_t get_rwcr_state_of_tc74(uint8_t sensor_address)
{
    uint8_t rwcr_status[1] = {0}; /* I2C data of sensor status declaration as array method for usage pointer value in I2C function */
    uint8_t read_config_address_ackw[1] = {RWCR}; /* I2C regsiter command value declaration as array method for usage pointer value in I2C function */
    uint8_t error_value = 255; /* Declaration error value if unsuccessfully obtain sensor status due I2C transfering data failed */

    if (i2c_write_blocking(i2c0, sensor_address, read_config_address_ackw, 1, false) == PICO_ERROR_GENERIC) return error_value;  /* Send I2C command request to sensor address to read sensor configuration data */
    if (i2c_read_blocking(i2c0, sensor_address, rwcr_status, 1, true) == PICO_ERROR_GENERIC) return error_value; /* Receive current sensor configuration data */

    sleep_us(5); /* I2C Bus delay to avoid I2C transfer error for sensor for next start I2C transfer (Minimum value is 4.7 microseconds) */
    
    return rwcr_status[0]; /* Return sensor status value after obtaining this data */
}

uint8_t is_present_address_tc74(uint8_t sensor_address)
{
    int ret = i2c_read_blocking(i2c0, sensor_address, NULL, 1, false);  /* Read data from I2C interface with connected TC74 sensor. Determine size bytes of data during I2C reading mode */ 

    return ret < 0 ? false : true; /* Return variable of state of present I2C address of TC74 sensor */
}