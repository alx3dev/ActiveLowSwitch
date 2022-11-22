#define ON 1
#define OFF 0

class ActiveLowSwitch {

  public:

    byte pin;

    bool detected = false;

    bool useTimer;
    unsigned int offTimer;

    unsigned long timer = 0UL;
    unsigned long triggered = 0UL;


    ActiveLowSwitch(byte switch_pin, bool use_timer = false,
                    unsigned int pause_time = 180000)
    {
      pin = switch_pin;
      useTimer = use_timer;
      offTimer = pause_time;
    }


    bool isOff() {

      if (digitalRead(pin) == 1) { return true; }   // relay is active-low
      return false;
    }


    void turn(const byte state) {

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


    void trigger() {

      if (isOff()) { turn(ON); }
      else { turn(OFF); }
    }


    void autoOff() {

      if (useTimer && detected) {

        timer = millis();
        if (timer - triggered > offTimer) { turn(OFF); }
      }
    }
  };  // Sensor
