
#include <vector>

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
  
      void SetTrafficState(TRAFFIC_LIGHT::TRAFFIC_LIGHT_STATE state)
      {
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
};

struct TRAFFIC_LIGHT_TRANSITION_DELAYS
{
  int stop_delay;
  int prepare_to_drive_delay;
  int drive_delay;
  int prepare_to_stop_delay;
};

class TRAFFIC_LIGHT_SCHEDULER
{
  private:
    std::vector<TRAFFIC_LIGHT_TRANSITION_DELAYS> _traffic_light_transition_delays_list;
    
  public:
    TRAFFIC_LIGHT_SCHEDULER(void) {}
    ~TRAFFIC_LIGHT_SCHEDULER(void) {}

    static TRAFFIC_LIGHT_SCHEDULER Create(std::vector<TRAFFIC_LIGHT_TRANSITION_DELAYS> traffic_light_transition_delays_list)
    {
      
       TRAFFIC_LIGHT_SCHEDULER traffic_light_scheduler;
       _traffic_light_transition_delays_list = traffic_light_transition_delays_list;
       return traffic_light_scheduler;
    }
}

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
