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

struct ActiveLowSwitch {

  bool useTimer = false;
  bool detected = false;

  unsigned long offTimer = 180000;

  unsigned long timer = 0UL;
  unsigned long triggered = 0UL;


  bool isOff(byte& pin) {

    if (digitalRead(pin) == 1) { return true; }   // relay is active-low
    return false;
  }


  void turn(const byte& state, byte& pin) {

    if (state == 1) {
      digitalWrite(pin, 0);

      detected = true;
      triggered = millis();
    }
    else {
      digitalWrite(pin, 1);
      detected = false;  
    }
  }


  void trigger(byte& pin) {

    if (isOff(pin)) { turn(ON, pin); }
    else { turn(OFF, pin); }
  }


  void autoOff(byte& pin) {

    if (useTimer && detected) {

      timer = millis();
      if (timer - triggered > offTimer) { turn(OFF, pin); }
    }
  }

};  // Sensor
