#define ON 1
#define OFF 0

class ActiveLowSwitch {

  private:

    byte pin;
    bool detected = false;

  public:

    bool useTimer;
    uint32_t offTime;
    uint32_t triggered = 0UL;

    ActiveLowSwitch(const byte switch_pin,
                    const bool use_timer = false,
                    const uint32_t off_time = 300000)
    {
      pin = switch_pin;
      useTimer = use_timer;
      offTime = off_time;

      pinMode(pin, OUTPUT);
    }

    bool isOFF() {
      return digitalRead(pin) == 1;   // active-low switch
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
      isOFF() ? turn(ON) : turn(OFF);
    }

    void autoOFF() {
      if (useTimer && detected) {
        uint32_t atm = millis();

        if (atm - triggered >= offTime)  {
          turn(OFF);
        }
      }
    }
  };  // ActiveLowSwitch
