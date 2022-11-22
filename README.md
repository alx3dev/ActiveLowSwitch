# ActiveLowSwitch

Dead-simple arduino library for "active-low" switches.

---

# Example

Infrared sensor is configured as input and attached as interrupt (when rising). It control another output pin with AC mechanical relay that is _"active-low"_, meaning that relay switch light ON when input is LOW. I wrote it for esp-01, in that case relay go on GPIO_0 with 10K pull-up resistor.  

Relay goes OFF with another interrupt, or after defined time if no signal received by IR sensor.


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
