# TC74-pico
The TC74 series I2C simple tiny temperature sensor for support Raspberry Pi Pico and RP2040 microcontroller with added feature standby power mode function. 

Advantage of TC74 sensor is low cost (less than two dollars per each sensor), simple usage (very little I2C commands and don't require to additional data processing and just took integer value), low current comsuption (maximum: 10 uA for standby mode and 350 uA for normal mode), wide voltage range (2.7 - 5.5 volts).

One disadvange of this sensor is not very accuracy temperature measurement (2-3 oC plus voltage dependent 1 oC per volt) and big resolution measurement (1 oC), according offcial datasheet. 

Note: When use TC74 model sensor use outside voltage recommendation will temperature additional offset dependent what voltage diffrence. (For example TC74A45.0VAT - optimise for 5 volts application), please look an offcial datasheet of TC74.

The code is based: TC74-arduino-lib (You can look and compare in github repository).

Features of this software library:
* **Switching power saving mode (setting standby mode of sensor) via our code**
* **Measuring temperature range from -128 to +127 degree Celisus and obtain data only signed 8-bit integer value**
* **Able self calibrating temperature for setting best accuracy via setting temperature offset in C function of own library**

Application of this software library and TC74 sensor (According official datasheet of TC74 sensor):
* **For electronics device** (for example: power supply, computer devices, battery charger)
* **Simple termostat hardware**
* **Heat detector** (In my opinion)

# Prerequisite

* **TC74 with optimised for 3.3 V power for best accuracy of measurement or any TC74 sensor**
* **Raspberry Pi Pico OR Raspberry Pi Pico W**
* **4 pcs Male-Male breadboard jumper**
* **Micro USB cable (which we can connect into laptop)**
* **GtkTerm software or any serial port terminal software** 
* **Breadboard**
* **Installed PICO C SDK, cmake and visual studio code** (In PICO SDK will install automatically visual studio code IDE, cmake and other essential softwares)

# Screenshot result of air temperature and pressure 

![image](https://github.com/misha-dig/TC74-pico/assets/55639759/878abb97-d7c8-4c4f-bc21-6a98e50dada6)

# Sechmatics and pinouts

## Circuit diagramm

![image](https://github.com/misha-dig/TC74-pico/assets/55639759/3b011edd-cfe3-47c1-9d9c-6a1bffc44b70)

Minimal schematic diagramm for ablity to work TC74 sensor in any projects 

## Pinout 

Assume: Use minimal circuit diagramm to able work with TC74 sensor

Sensor:               Raspberry Pi Pico:

NC   (no. 1) -------> Don't connect any pins
 
SDA  (no. 2) -------> GP4

GND  (no. 3) -------> GND

SCLK (no. 4) -------> GP5

VDD  (no. 5) -------> 3V3(OUT)

# Basic code

A minimal simple code that ablity work TC74 temperature sensor. (Measurement temperature plus setting standby power a long time (about 9.7 seconds per loop) + measuring temperature (about 0.3 seconds per loop)

Main code usage TC74 temperature sensor with Raspberry Pi Pico microcontroller with detailed comments

```
#include <stdio.h> /* Standard libary for printing the UART console */
#include "pico/stdlib.h" /* Libary of PICO SDK C/C++ for support function for RPI PICO */
#include "tc74.h" /* Own header of TC74 Sensor driver */

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
```

# Building code (We used Debian GNU/Linux 11 (bullseye) OS)

## How get binary file for uploading your Raspberry Pi Pico

1. Download own repository by using command ```git clone https://github.com/misha-dig/TC74-pico.git```

2. Go to direcitory ```TC74-pico``` by command ```cd TC74-pico```

3. Set enviroment path of PICO_SDK_PATH with your pico-sdk directory path by command ```export PICO_SDK_PATH=/your_sdk_path/pico-sdk``` unless set enviroment path in .bashrc file 

4. Create directory ```build``` by command ```mkdir build```

5. Go to ```build``` directory by command ```cd build```

6. Hit command ```cmake ..```

7. Hit command ```make``` and wait until building code finished  

8. Flash into your Raspberry Pi Pico file ```pico_tc74.uf2``` from ```build``` directory (You need first hold a button BOOTSEL until file manager appeared for Raspberry Pi Pico drive)

9. Enjoy your project !!! :) :) :)

## How generate doxygen HTML documentation

If you don't have doxygen package in your Linux PC

Please run two simple command (for debian based Linux OS users)

```sudo apt-get update```

```sudo apt-get install doxygen```

And genrate doxygen HTML documentation by invoking command in this directory

```doxygen``` 

Open your documentation by path ```docs/html/index.html```

## Setting UART via USB (after flashing your Raspberry Pi Pico)

We use Pico's setting default speed of UART

The default parameter for Raspberry Pico is

* Baudrate: ```115200``` bit/s
* Data bit: ```8``` bit
* Stopbit: ```1``` bit 
* Parity: ```NONE```
* Flow control: ```XON/XOFF```

So we enter 115200 and select serial port in main page of Putty or GtkTerm software

# How to create own projects with own libary TC74-pico

## Creating empty project with TC74 sensor library (As similary building instruction above)

We used with instruction how create any project with using Pico C SDK. 

1. Clone by hitting command ```git clone https://github.com/misha-dig/TC74-pico.git```

2. Go to direcitory ```TC74-pico``` by command ```cd TC74-pico```

3. Set enviroment path of ```PICO_SDK_PATH``` with your pico-sdk directory path by command ```export PICO_SDK_PATH=/your_sdk_path/pico-sdk``` unless set enviroment path in .bashrc file  

4. Modify project name in ```CMakeLists.txt``` file by using text editor (seach and replace all text from ```TC74-pico``` into your name of project (for example ```heat-detector```) and save this text file) 

5. Create directory ```build``` by command ```mkdir build```

6. Go to ```build``` directory by entering command ```cd build``` 

7. Hit command ```cmake ..```

8. Build your source of code for your project by hitting command ```make``` in ```build``` directory path 

## Your existing project

Just you need to follow few step ... 

1. Download and unzip own this repository from github OR using ```git clone  https://github.com/misha-dig/TC74-pico.git```

2. Go to directory ```TC74-pico```

3. Copy ```tc74.c``` and ```tc74.h``` into your existing project directory

4. You may be need to modify your ```CMakeLists.txt``` (Such adding file tc74.c code in section ```add_executable``` and add dependencies ```hardware_i2c``` in section ```target_link_libraries``` )  

5. Enjoy your coding!!! :) Good Luck!!!

# Credits and resources

Microchip Technology Inc. Tiny Serial Digital Thermal Sensor. https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21462D.pdf (The official datasheet of TC74 sensor)

Chawin. TC74-arduino-lib. GitHub. https://github.com/FaultyTwo/TC74-arduino-lib/tree/master (For understanding code I2C protocol that can interfacing TC74 sensor via I2C interface (breif explaintion plus code showing) + code license)

Raspberry Pi Ltd. hardware_i2c. https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#hardware_i2c (API Documentation of Raspberry PI Pico C SDK)

Raspberry Pi Ltd. The C/C++ SDK. https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#say-hello-world (How create new project with Raspberry Pico)
