/*
  Switching light ON/OFF with infrared sensor and ESP8266 (esp-01)

    GPIO_0 -> external_pull-up -> mechanical relay
    GPIO_2 -> infrared sensor

  To use TX/RX pins of esp-01:
    pinMode(1, FUNCTION_3);
    pinMode(3, FUNCTION_3);
*/

#define ON  1
#define OFF 0

#define AUTO_OFF 180000 // 3 minutes

#define RELAY_ON LOW  // relay is active-low


const byte RLP = 0; // relay pin
const byte IRP = 2; // ir pin


struct Sensor {

  bool autoOff = true;
  bool detected = false;

  unsigned long timer = 0UL;
  unsigned long triggered = 0UL;


  bool isOff(const byte& pin = RLP,
             const byte& mode = RELAY_ON) {

    if (digitalRead(pin) != mode) { return true; }
    return false;
  }


  void turn_switch(const byte& state = ON,
                   const byte& myPin = RLP,
                   const byte& myModeOn = RELAY_ON) {

    if (state == 1) {
      digitalWrite(myPin, myModeOn);

      detected = true;
      triggered = millis();
    }
    else {
      digitalWrite(myPin, !myModeOn);
      detected = false;  
    }
  }
};  // Sensor
