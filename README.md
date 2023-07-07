# TC74-pico
The TC74 series I2C simple tiny temperature sensor for support Raspberry Pi Pico microcontroller with added feature standby power mode function. 

Advantage of TC74 sensor is low cost (less than two dollars per each sensor), simple usage (very little I2C commands and don't require to additional data processing), low current comsuption (maximum: 10 uA for standby mode and 350 uA for normal mode).

One disadvange of this sensor is not very accuracy temperature measurement (2-3 oC plus voltage dependent 1oC per volt) and big resolution measurement (1 oC)


Features of this software library:
* **Switching power saving mode (setting standby mode of sensor) via our code**
* **Measuring temperature range from -127 to +127 degree Celisus and obtain data only signed 8-bit integer value**
* **Able self calibrating temperature for setting best accuracy via setting temperature offset in C function of own library**

Application of this software library and TC74 sensor (According official datasheet of TC74 sensor):
* **For electronics device** (for example: power supply, computer devices, battery charger)
* **Simple termostat hardware**
* **Heat detector** (In my opinion)

 


