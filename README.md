# ActiveLowSwitch

Library to control active-low switches with ESP8266 / ESP32 and ArduinoIDE / PlatformIO.

---

# Example

Infrared sensor is configured as input and attached as interrupt (when rising). It control another output pin with AC mechanical relay that is _"active-low",_ (in case of ESP-01 it goes on GPIO_0 with 10K pull-up resistor).  

Relay goes OFF with another interrupt, or after some time if no signal received by IR sensor. Everything is structed, making it easy to add more switches and to reuse same code.


## Writing sketch to ESP-01 with ESP32

To write a sketch on ESP-01 from ESP32 over USB cable, you need to take care about a few things:  

 - GPIO_0 on ESP-01 must be LOW before powering to enter boot mode
 - RST and CH on ESP-01 must be HIGH for chip to work
 - EN pin of ESP32 must be grounded to let us flash ESP-01
 - Use different power supply for ESP-01 (+3.3V)
 - Connect ESP32 to PC over USB
 - Open ArduinoIDE and select generic ESP8826 board
 - Compile and upload[*]  
   
 [*] if you are having troubles, reset ESP-01 when upload start by pulling RST to the ground  
   
   
    
 _Wiring diagram table to flash ESP-01 from ESP32:_

|  POWER     |  ESP-01   |     ESP32      |                 NOTE                     |
| :---       |  :---:    |     :---:      |                 ----:                    |
|     x      | TX        |   TX           |                                          |
|     x      | RX        |   RX           |                                          |
|    GND     |  x        |   EN           | disable ESP32 so we can work             |
|    GND     | GPIO_0    |   x            | ground gpio_0 to enter boot mode         |
|   +3.3V    | Vin       |   x            |                                          |
|   +3.3V    | CH        |   x            | add pull-up or connect to 3.3V           |
|   +3.3V    | RST       |   x            | add pull-up or connect to 3.3V -> ground it to reset ESP-01 |
