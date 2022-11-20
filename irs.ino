/*
  Switching light ON/OFF with infrared sensor and ESP8266

    For ESP-01 use next setup

      GPIO_0 -> 10К pull-up -> mechanical relay (active low)
      GPIO_2 -> infrared sensor

    To use TX/RX pins of esp-01 for I2C display:
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
             const byte& modeOn = RELAY_ON)
    {
      if (digitalRead(pin) != modeOn);
        return true;
    }
  }

  void turn_switch(const byte& state) {

    if (state == 1) {
      digitalWrite(RLP, RELAY_ON);

      detected = true;
      triggered = millis();
    }
    else {
      digitalWrite(RLP, !RELAY_ON);
      detected = false;  
    }
  }
};  // Sensor


struct Sensor ir;

ICACHE_RAM_ATTR void switch_relay() {
  if (ir.isOff()) {
    ir.turn_switch(ON);
  }
  else {
    ir.turn_switch(OFF);
  }
}


void setup() {
  pinMode(IRP, INPUT);
  pinMode(RLP, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IRP), switch_relay, RISING);
}


void loop() {

  if (ir.autoOff) {

    ir.timer = millis();

    if (ir.timer - ir.triggered > AUTO_OFF) {
      ir.turn_switch(OFF);
    }
  }
}
