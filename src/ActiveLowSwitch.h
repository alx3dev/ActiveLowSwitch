#define ON 1
#define OFF 0

class ActiveLowSwitch {

  private:

    byte pin;

    bool detected = false;

    unsigned long triggered = 0UL;


  public:

    bool timer;

    unsigned long pause;


    ActiveLowSwitch(const byte switch_pin, bool use_timer = false,
                    unsigned long pause_time = 180000)
    {
      pin = switch_pin;
      timer = use_timer;
      pause = pause_time;
    }


    bool isOFF() {

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

      if (isOFF()) { turn(ON); }
      else { turn(OFF); }
    }


    void autoOFF() {

      if (timer && detected) {
        unsigned long atm = millis();

        if (atm - triggered > pause) { turn(OFF); }
      }
    }
  };  // Sensor