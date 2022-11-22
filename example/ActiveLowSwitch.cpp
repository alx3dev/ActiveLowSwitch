//MIT License
//Copyright (c) 2022 Alx3Dev

//#include <Arduino.h>
#include "ActiveLowSwitch.h"


byte irPin = 2; // infrared sensor

byte switchPin = 0; // relay pin

bool auto_off = true;

unsigned long auto_off_time = 180000; // 3 min.


ActiveLowSwitch relay(switchPin, auto_off, auto_off_time);  // configure


IRAM_ATTR void monitorIR() { relay.trigger(); }   // attach interrupt


void setup() {
  pinMode(irPin, INPUT);
  pinMode(switchPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(irPin), monitorIR, RISING);
}


void loop() {
  relay.autoOFF();
}
