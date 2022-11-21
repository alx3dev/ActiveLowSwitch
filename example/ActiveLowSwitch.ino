#include "ActiveLowSwitch.h"

#define IRP 2 // infrared sensor

byte switchPin = 0; // relay pin

ActiveLowSwitch relay;

IRAM_ATTR void monitor_relay() { relay.trigger(switchPin); }  // attach interrupt to esp8266


void setup() {
  pinMode(IRP, INPUT);
  pinMode(switchPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IRP), monitor_relay, RISING);

  relay.useTimer = true;
  relay.offTimer = 180000;  // turn of after 3 minutes
}


void loop() {
  relay.autoOff(switchPin); // if not turned off manually, do it after 3 minutes
}

