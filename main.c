/**
 * Copyright (C) 2023 by Misha Zaslavskis   
 * License is BSD 3-Clause
*/

/**
 * @file main.c
 * @author Misha Zaslavskis
 * @date 19th July 2023
 * @brief A main code of how work with TC74 sensor for Raspberry Pi Pico board. Find of all available different bus address of TC74 sensors. 
 * */

#include <stdio.h> /* Standard libary for printing the UART console */
#include "pico/stdlib.h" /* Libary of PICO SDK C/C++ for support function for RPI PICO */
#include "tc74.h" /* Own header of TC74 Sensor driver */

/**
 * @brief A main function that able measure temperature and print the results of simple measurment in UART interface
 * Scanning and test TC74 sensor in this main code. 
 * All c/c++ code must include int main() or int main(int argc, char **argv) function. 
*/
int main() {

    stdio_init_all(); /* Initialize that supporting printf standard function via UART interface */

    i2c_init_tc74(); /* Initialize I2C interface for TC74 sensor */

    sleep_ms(1000); /* Pause 1 second for startup sensor to avoid error/fauly working this software */

    while(1) /* Infinite loop */
    {
        for(uint8_t num_diff_addr_tc74 = I2C_ADDRESS_A0; num_diff_addr_tc74 < I2C_ADDRESS_A7 + 1; num_diff_addr_tc74++) /* Loop of address range of TC74 sensor which TC74 sensor model has eight different addresses */
        {
            if (is_present_address_tc74(num_diff_addr_tc74)) /* Check that I2C bus address is present in I2C inteface */
            {
                int16_t temp = get_temperature_tc74(num_diff_addr_tc74, -4); /* Measure current temperature with current bus address */
        
                printf("Current temperature: %d oC (from 0x%.2x) \r\n", temp, num_diff_addr_tc74); /* Print current temperature with current address of TC74 sensor */

                if(!set_standby_mode_tc74(num_diff_addr_tc74, 1)) 
                    printf("The TC74 sensor with 0x%.2X address is switched to standby mode \r\n", num_diff_addr_tc74); /* Switch to standby mode from normal mode to saving energy with current bus address */
        
                sleep_ms(9700); /* Delay 9.7 second*/

                if(!set_standby_mode_tc74(num_diff_addr_tc74, 0)) 
                    printf("The TC74 sensor with 0x%.2X address is switched to normal mode \r\n", num_diff_addr_tc74); /* Switch to normal mode from standby mode to able measure current temperature with current bus address */

                sleep_ms(300); /* Delay 0.3 second */
            }
            else printf("Not available sensor in %.2X address \r\n", num_diff_addr_tc74);// continue; /* Not available TC74 I2C address. Skip this task and go into next address of TC74 sensor. */ 
        }
    }
}
