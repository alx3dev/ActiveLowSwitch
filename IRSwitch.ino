#include "irsensor.h"

Sensor ir;

IRAM_ATTR void switch_relay() {

  if (ir.isOff()) { ir.turn_switch(ON); }

  else { ir.turn_switch(OFF); }
}


void setup() {
  pinMode(IRP, INPUT);
  pinMode(RLP, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IRP), switch_relay, RISING);
}


void loop() {

  if (ir.autoOff && ir.detected) {

    ir.timer = millis();
    if (ir.timer - ir.triggered > AUTO_OFF) { ir.turn_switch(OFF); }
  }
}
