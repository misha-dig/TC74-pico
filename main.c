/**
 * Copyright (C) 2023 by Misha Zaslavskis   
 * License is BSD 3-Clause
*/

/**
 * @file main.c
 * @author Misha Zaslavskis
 * @date 7 July 2023
 * @brief A main code of how work with TC74 sensor for Raspberry Pi Pico board.  
 * */

#include <stdio.h> /* Standard libary for printing the UART console */
#include "pico/stdlib.h" /* Libary of PICO SDK C/C++ for support function for RPI PICO */
#include "tc74.h" /* Own header of TC74 Sensor driver */

/**
 * @brief A main function that able measure temperature and print the results of simple measurment in UART interface 
 * All c/c++ code must include int main() or int main(int argc, char **argv) function. 
*/
int main() {

    stdio_init_all(); /* Initialize that supporting printf standard function via UART interface */

    i2c_init_tc74(); /* Initialize I2C interface for TC74 sensor */

    sleep_ms(1000); /* Pause 1 second for startup sensor to avoid error/fauly working this software */

    for (;;) /* Infinite loops */ 
    {
        int16_t temp = get_temperature_tc74(I2C_ADDRESS_A4, -4); /* Measure current temperature */
        
        printf("Current temperature: %d oC \r\n", temp); /* Print current temperature */

        if(!set_standby_mode_tc74(I2C_ADDRESS_A4, 1)) printf("The TC74 sensor is switched to standby mode \r\n"); /* Switch to standby mode from normal mode to saving energy */
        
        sleep_ms(9700); /* Delay 9.7 second*/

        if(!set_standby_mode_tc74(I2C_ADDRESS_A4, 0)) printf("The TC74 sensor is switched to normal mode \r\n"); /* Switch to normal mode from standby mode to able measure current temperature */

        sleep_ms(300); /* Delay 0.3 second */
    }
}
