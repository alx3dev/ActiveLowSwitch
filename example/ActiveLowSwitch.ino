#include "ActiveLowSwitch.h"

#define IRP 2 // infrared sensor

byte switchPin = 0; // relay pin

ActiveLowSwitch relay(switchPin, true);


IRAM_ATTR void monitor_relay() { relay.trigger(); }


void setup() {
  pinMode(IRP, INPUT);
  pinMode(switchPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IRP), monitor_relay, RISING);
}


void loop() {
  relay.autoOff();
}

