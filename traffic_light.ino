
class LED
{
   public: 
      typedef enum LED_STATE { OFF = 0, ON = 1} LED_STATE;
  
  private:
    int _led_pin_id;
    LED_STATE _state;
  
  public:
    LED(void) {}
    ~LED(void) {}
    
    static LED Create(int led_pin_id) 
    {
        LED led;
        led._led_pin_id = led_pin_id;
        led._state = OFF;
        pinMode(led_pin_id, OUTPUT);
        return led;
    }
  
    void SetState(LED::LED_STATE state)
    {
        this->_state = state;
        int voltage = state == OFF ? LOW : HIGH;
        digitalWrite(_led_pin_id, voltage);
    }
    
    LED::LED_STATE GetState(void)
    {
      return this->_state;
    }
};


class TRAFFIC_LIGHT
{
    public:
        typedef enum TRAFFIC_LIGHT_STATE 
        { 
            STOP = 0, 
            PREPARE_TO_DRIVE = 1, 
            DRIVE = 2, 
            PREPARE_TO_STOP = 3 
        } TRAFFIC_LIGHT_STATE;
    
    private:
        TRAFFIC_LIGHT::TRAFFIC_LIGHT_STATE _state;
        LED _red_led;
        LED _yellow_led;
        LED _green_led;
        
    public:
        TRAFFIC_LIGHT(void) {}
        ~TRAFFIC_LIGHT(void) {}
        
        static TRAFFIC_LIGHT Create(LED red_led, LED yellow_led, LED green_led) 
        {
            TRAFFIC_LIGHT tl;
            tl._red_led = red_led;
            tl._yellow_led = yellow_led;
            tl._green_led = green_led;
            return tl;
        }
        
        void SetState(TRAFFIC_LIGHT::TRAFFIC_LIGHT_STATE state)
        {
            this->_state = state;
            switch(state)
            {
                case STOP:
                    _red_led.SetState(LED::LED_STATE::ON);
                    _yellow_led.SetState(LED::LED_STATE::OFF);
                    _green_led.SetState(LED::LED_STATE::OFF);
                    break;
                
                case PREPARE_TO_DRIVE:
                    _red_led.SetState(LED::LED_STATE::ON);
                    _yellow_led.SetState(LED::LED_STATE::ON);
                    _green_led.SetState(LED::LED_STATE::OFF);
                    break;
                
                case DRIVE:
                    _red_led.SetState(LED::LED_STATE::OFF);
                    _yellow_led.SetState(LED::LED_STATE::OFF);
                    _green_led.SetState(LED::LED_STATE::ON);
                    break;
                
                case PREPARE_TO_STOP:
                    _red_led.SetState(LED::OFF);
                    _yellow_led.SetState(LED::ON);
                    _green_led.SetState(LED::OFF);
                    break;
            }
        }
        
        TRAFFIC_LIGHT::TRAFFIC_LIGHT_STATE GetState(void)
        {
            return this->_state;
        }
};

class TRAFFIC_LIGHT_DELAY
{
    private:
        enum class DELAY_TYPE {CONSTANT = 0, RANDOM = 1} _delay_type;
        
        // USED FOR CONSTANT DELAY:
        unsigned _delay;

        // USED FOR RANDOM DELAY:
        unsigned _min_delay;
        unsigned _max_delay;
        
    public:
        TRAFFIC_LIGHT_DELAY(void) {}
        ~TRAFFIC_LIGHT_DELAY(void) {}
        
        static TRAFFIC_LIGHT_DELAY CreateConstant(unsigned delay)
        {
            TRAFFIC_LIGHT_DELAY traffic_light_delay;
            traffic_light_delay._delay_type = DELAY_TYPE::CONSTANT;
            traffic_light_delay._delay = delay;
            return traffic_light_delay;
        }
        
        // 'min_delay' must be < 'max_delay'
        static TRAFFIC_LIGHT_DELAY CreateRandom(unsigned min_delay, unsigned max_delay)
        {
            // CHECK FOR ERROR!!!
            TRAFFIC_LIGHT_DELAY traffic_light_delay;
            traffic_light_delay._delay_type = DELAY_TYPE::RANDOM;
            traffic_light_delay._min_delay = min_delay;
            traffic_light_delay._max_delay = max_delay;
            return traffic_light_delay;
        }
        
        unsigned GetDelay(void)
        {
            if (_delay_type == DELAY_TYPE::CONSTANT)
                return _delay;
            else if (_delay_type == DELAY_TYPE::RANDOM)
                return random(_min_delay, _max_delay);
        }
};

class TRAFFIC_LIGHT_TRANSITION_DELAYS
{
    private:
        TRAFFIC_LIGHT_DELAY _stop_delay;
        TRAFFIC_LIGHT_DELAY _prepare_to_drive_delay;
        TRAFFIC_LIGHT_DELAY _drive_delay;
        TRAFFIC_LIGHT_DELAY _prepare_to_stop_delay;
        
    public:
        TRAFFIC_LIGHT_TRANSITION_DELAYS(void) {}
        ~TRAFFIC_LIGHT_TRANSITION_DELAYS(void) {}
        
        static TRAFFIC_LIGHT_TRANSITION_DELAYS Create(
            TRAFFIC_LIGHT_DELAY stop_delay,
            TRAFFIC_LIGHT_DELAY prepare_to_drive_delay,
            TRAFFIC_LIGHT_DELAY drive_delay,
            TRAFFIC_LIGHT_DELAY prepare_to_stop_delay)
        {
            _stop_delay = stop_delay;
            _prepare_to_drive_delay = prepare_to_drive_delay;
            _drive_delay = drive_delay;
            _prepare_to_stop_delay = prepare_to_stop_delay;
        }
        
        // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
};

template<unsigned int SIZE>
class TRAFFIC_LIGHT_SCHEDULER
{
    private:
        bool is_initialized;
        unsigned int _traffic_light_transition_delays_added;
        TRAFFIC_LIGHT_TRANSITION_DELAYS _traffic_light_transition_delays_array[SIZE];
        
    public:
        TRAFFIC_LIGHT_SCHEDULER(void) {}
        ~TRAFFIC_LIGHT_SCHEDULER(void) {}
        
        static TRAFFIC_LIGHT_SCHEDULER Create()
        {
           TRAFFIC_LIGHT_SCHEDULER traffic_light_scheduler;
           traffic_light_scheduler._traffic_light_transition_delays_added = 0U;
           return traffic_light_scheduler;
        }
        
        void PushTrafficLightTransitionDelays(TRAFFIC_LIGHT_TRANSITION_DELAYS traffic_light_transition_delays)
        {
            // CHECK FOR ERROR!!!
            _traffic_light_transition_delays_array[_traffic_light_transition_delays_added++]
                = traffic_light_transition_delays;
        }
        
        
};

class TRAFFIC_LIGHT_CONTROLLER
{
  private:
    TRAFFIC_LIGHT _traffic_light;
    
  public:
    TRAFFIC_LIGHT_CONTROLLER(void) {}
    ~TRAFFIC_LIGHT_CONTROLLER(void) {}

    static TRAFFIC_LIGHT_CONTROLLER Create(TRAFFIC_LIGHT traffic_light)
    {
        TRAFFIC_LIGHT_CONTROLLER traffic_light_controller;
        traffic_light_controller._traffic_light = traffic_light;
        return traffic_light_controller;
    }

    void Run(void)
    {
      _traffic_light.SetTrafficState(TRAFFIC_LIGHT::TRAFFIC_LIGHT_STATE::STOP);
      delay(5000);
      _traffic_light.SetTrafficState(TRAFFIC_LIGHT::TRAFFIC_LIGHT_STATE::PREPARE_TO_DRIVE);
      delay(1000);
      _traffic_light.SetTrafficState(TRAFFIC_LIGHT::TRAFFIC_LIGHT_STATE::DRIVE);
      delay(5000);
      _traffic_light.SetTrafficState(TRAFFIC_LIGHT::TRAFFIC_LIGHT_STATE::PREPARE_TO_STOP);
      delay(1000);
    }
};

struct TRAFFIC_LIGHT_PIN_IDS
{
  int red;
  int yellow;
  int green;
};

TRAFFIC_LIGHT_PIN_IDS traffic_light_pin_ids1 = {
  .red = 13, 
  .yellow = 12, 
  .green = 11
 };
TRAFFIC_LIGHT_TRANSITION_DELAYS traffic_light_transition_delays1 = {
  .stop_delay = 5000,
  .prepare_to_drive_delay = 1000,
  .drive_delay = 5000,
  .prepare_to_stop_delay = 1000
};
TRAFFIC_LIGHT traffic_light1;
TRAFFIC_LIGHT_CONTROLLER traffic_light_controller1;

TRAFFIC_LIGHT_PIN_IDS traffic_light_pin_ids2 = {
  .red = 10, 
  .yellow = 9, 
  .green = 8
};
TRAFFIC_LIGHT_TRANSITION_DELAYS traffic_light_transition_delays2 = {
  .stop_delay = 5000,
  .prepare_to_drive_delay = 1000,
  .drive_delay = 5000,
  .prepare_to_stop_delay = 1000
};
TRAFFIC_LIGHT traffic_light2;
TRAFFIC_LIGHT_CONTROLLER traffic_light_controller2;

void setup()
{
  traffic_light1 = TRAFFIC_LIGHT::Create(
    LED::Create(traffic_light_pin_ids1.red),
    LED::Create(traffic_light_pin_ids1.yellow),
    LED::Create(traffic_light_pin_ids1.green)
  );

  traffic_light_controller1 = TRAFFIC_LIGHT_CONTROLLER::Create(traffic_light1);

  traffic_light2 = TRAFFIC_LIGHT::Create(
    LED::Create(traffic_light_pin_ids2.red),
    LED::Create(traffic_light_pin_ids2.yellow),
    LED::Create(traffic_light_pin_ids2.green)
  );

  traffic_light_controller2 = TRAFFIC_LIGHT_CONTROLLER::Create(traffic_light2);
}

void loop()
{
  traffic_light_controller1.Run();
  traffic_light_controller2.Run();
}
