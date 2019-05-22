

void print_error(const char* string)
{
    //Serial.print(string);
}

#define modulo(a,b) ((a) % (b))

typedef enum LED_STATE { OFF = 0, ON = 1} LED_STATE;

class LED
{
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
    
        void SetState(LED_STATE state)
        {
            this->_state = state;
            int voltage = state == OFF ? LOW : HIGH;
            digitalWrite(_led_pin_id, voltage);
        }
    
        LED_STATE GetState(void)
        {
            return this->_state;
        }
};

class TRAFFIC_LIGHT_STATE
{
    public:
        enum STATE : unsigned
        {
            STOP = 0, 
            PREPARE_TO_DRIVE = 1, 
            DRIVE = 2, 
            PREPARE_TO_STOP = 3 
        };
    
        TRAFFIC_LIGHT_STATE() = default;
        constexpr TRAFFIC_LIGHT_STATE(STATE state) : _state(state) { }
        
        bool operator==(TRAFFIC_LIGHT_STATE traffic_light_state) const { return _state == traffic_light_state._state; }
        bool operator!=(TRAFFIC_LIGHT_STATE traffic_light_state) const { return _state != traffic_light_state._state; }
    
        TRAFFIC_LIGHT_STATE NextState(void)
        {
            TRAFFIC_LIGHT_STATE next_traffic_light_state;
            
            next_traffic_light_state = STATE(modulo(unsigned(this->_state) + 1,4));
            
            return next_traffic_light_state;
        }
        
    private:
        STATE _state;
};

class TRAFFIC_LIGHT
{
    private:
        TRAFFIC_LIGHT_STATE _traffic_light_state;
        LED _red_led;
        LED _yellow_led;
        LED _green_led;
        
    public:
        TRAFFIC_LIGHT(void) {}
        ~TRAFFIC_LIGHT(void) {}
        
        static TRAFFIC_LIGHT Create(LED red_led, LED yellow_led, LED green_led, TRAFFIC_LIGHT_STATE traffic_light_state) 
        {
            TRAFFIC_LIGHT traffic_light;
            traffic_light._red_led = red_led;
            traffic_light._yellow_led = yellow_led;
            traffic_light._green_led = green_led;
            traffic_light.SetState(traffic_light_state);
            return traffic_light;
        }
        
        void SetState(TRAFFIC_LIGHT_STATE traffic_light_state)
        {
            this->_traffic_light_state = traffic_light_state;
            if (_traffic_light_state == TRAFFIC_LIGHT_STATE::STOP)
            {
                _red_led.SetState(LED_STATE::ON);
                _yellow_led.SetState(LED_STATE::OFF);
                _green_led.SetState(LED_STATE::OFF);
            }
            else if (_traffic_light_state == TRAFFIC_LIGHT_STATE::PREPARE_TO_DRIVE)
            {
                _red_led.SetState(LED_STATE::ON);
                _yellow_led.SetState(LED_STATE::ON);
                _green_led.SetState(LED_STATE::OFF);
            }
            else if (_traffic_light_state == TRAFFIC_LIGHT_STATE::DRIVE)
            {
                _red_led.SetState(LED_STATE::OFF);
                _yellow_led.SetState(LED_STATE::OFF);
                _green_led.SetState(LED_STATE::ON);
            }
            else if (_traffic_light_state == TRAFFIC_LIGHT_STATE::PREPARE_TO_STOP)
            {
                _red_led.SetState(LED_STATE::OFF);
                _yellow_led.SetState(LED_STATE::ON);
                _green_led.SetState(LED_STATE::OFF);
            }
        }
        
        TRAFFIC_LIGHT_STATE GetState(void)
        {
            return this->_traffic_light_state;
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
            TRAFFIC_LIGHT_TRANSITION_DELAYS traffic_light_transition_delays;
            traffic_light_transition_delays._stop_delay = stop_delay;
            traffic_light_transition_delays._prepare_to_drive_delay = prepare_to_drive_delay;
            traffic_light_transition_delays._drive_delay = drive_delay;
            traffic_light_transition_delays._prepare_to_stop_delay = prepare_to_stop_delay;
            return traffic_light_transition_delays;
        }
        
        unsigned GetDelay(TRAFFIC_LIGHT_STATE traffic_light_state)
        {
            if (traffic_light_state == TRAFFIC_LIGHT_STATE::STOP)
                return _stop_delay.GetDelay();
            else if (traffic_light_state == TRAFFIC_LIGHT_STATE::PREPARE_TO_DRIVE)
                return _prepare_to_drive_delay.GetDelay();
            else if (traffic_light_state == TRAFFIC_LIGHT_STATE::DRIVE)
                return _drive_delay.GetDelay();
            else if (traffic_light_state == TRAFFIC_LIGHT_STATE::PREPARE_TO_STOP)
                return _prepare_to_stop_delay.GetDelay();
        }
};

template<size_t SIZE>
class INDEX_CONTAINER
{
    private:
        size_t _index_array[SIZE];
        size_t _count;
        
    public:
        INDEX_CONTAINER(void) 
        {
            _count = 0U;
        }
        
        ~INDEX_CONTAINER(void) {}
        
        void PushIndex(size_t index)
        {
            _index_array[_count++] = index;
        }
        
        size_t GetCount(void)
        {
            return _count;
        }
        
        size_t GetAt(size_t i)
        {
            return _index_array[i];
        }
        
        void Clear(void)
        {
            _count = 0;
        }
        
        bool IsIn(size_t index)
        {
            for (size_t i = 0; i < _count; i++)
                if (index = GetAt(i))
                    return true;
            return false;
        }
        
        INDEX_CONTAINER& operator=(const INDEX_CONTAINER& other)
        {
            this->_count = other._count;
            for (size_t i = 0; i < _count; i++)
            {
               this-> _index_array[i] = other._index_array[i];
            }
            return *this;
        }
};

template<size_t TRAFFIC_LIGHTS_COUNT>
class TRAFFIC_LIGHT_SCHEDULER
{
    private:
        TRAFFIC_LIGHT _array_of_traffic_lights[TRAFFIC_LIGHTS_COUNT];
        unsigned int _traffic_light_push_counter;
        
        TRAFFIC_LIGHT_TRANSITION_DELAYS _array_of_traffic_light_transition_delays[TRAFFIC_LIGHTS_COUNT];
        unsigned int _traffic_light_transition_delays_push_counter;
        
        unsigned int _array_of_current_traffic_light_delays[TRAFFIC_LIGHTS_COUNT];
        unsigned int _last_minimal_delay;

        INDEX_CONTAINER _indices_tracker_for_traffic_lights_that_require_a_state_update;
        
    public:
        TRAFFIC_LIGHT_SCHEDULER(void) {}
        ~TRAFFIC_LIGHT_SCHEDULER(void) {}
        
        static TRAFFIC_LIGHT_SCHEDULER Create(void)
        {
           TRAFFIC_LIGHT_SCHEDULER traffic_light_scheduler;
           traffic_light_scheduler._traffic_light_push_counter = 0U;
           traffic_light_scheduler._traffic_light_transition_delays_push_counter = 0U;
           return traffic_light_scheduler;
        }
        
        void PushTrafficLight(TRAFFIC_LIGHT traffic_light)
        {
            if (_traffic_light_push_counter >= TRAFFIC_LIGHTS_COUNT)
                print_error("FATAL ERROR: Too much traffic light objects were pushed in to the scheduler.\n");
            else
                _array_of_traffic_lights[_traffic_light_push_counter++] = traffic_light;
        }
        
        void PushTrafficLightTransitionDelays(TRAFFIC_LIGHT_TRANSITION_DELAYS traffic_light_transition_delays)
        {
            if (_traffic_light_push_counter >= TRAFFIC_LIGHTS_COUNT)
                print_error("FATAL ERROR: Too much traffic light transition delays objects were pushed in to the scheduler.\n");
            else
                _array_of_traffic_light_transition_delays[_traffic_light_transition_delays_push_counter++] = traffic_light_transition_delays;
        }
        
    public:
        void Initialize(void)
        {
            if (_traffic_light_push_counter != TRAFFIC_LIGHTS_COUNT)
                print_error("FATAL ERROR: Cannot intialize the scheduler beacuse the number of traffic lights "
                            " that were pushed doesn't corresponed to number of traffic lights that the scheduler expects.\n");
                            
            if (_traffic_light_transition_delays_push_counter != TRAFFIC_LIGHTS_COUNT)
                print_error("FATAL ERROR: Cannot intialize the scheduler beacuse the number of traffic light transition delays"
                            " that were pushed doesn't corresponed to number of traffic lights that the scheduler expects.\n");
                
            for (size_t traffic_light_index = 0; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                _array_of_current_traffic_light_delays[traffic_light_index] =  
                    _array_of_traffic_light_transition_delays[traffic_light_index].GetDelay(
                        _array_of_traffic_lights[traffic_light_index].GetState());
            }
            
            size_t index_of_traffic_light_with_minimal_delay_for_its_current_state = 0;
            for (size_t traffic_light_index = 1; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                if (_array_of_current_traffic_light_delays[index_of_traffic_light_with_minimal_delay_for_its_current_state] >
                    _array_of_current_traffic_light_delays[traffic_light_index])
                {
                    index_of_traffic_light_with_minimal_delay_for_its_current_state = traffic_light_index;
                }
            }
            unsigned minimal_delay = _array_of_current_traffic_light_delays[index_of_traffic_light_with_minimal_delay_for_its_current_state];
            
            // Find all indices with minimal delay and push them into the indices tracker:
            for (size_t traffic_light_index = 0; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                if (_array_of_current_traffic_light_delays[traffic_light_index] == minimal_delay) 
                {
                   _indices_tracker_for_traffic_lights_that_require_a_state_update.PushIndex(traffic_light_index);
                }
            }
            
            _last_minimal_delay = minimal_delay;
        }
    
        void Run(void)
        {
            // Wait for last_minimal_delay:
            delay(_last_minimal_delay);
            
            // Update the states of all traffic lights that require an update who were tracked inside the indices tracker:
            for (size_t index_inside_the_indices_tracker = 0; 
                 index_inside_the_indices_tracker < _indices_tracker_for_traffic_lights_that_require_state_update.GetCount(); 
                 index_inside_the_indices_tracker++)
            {
                _array_of_traffic_lights[_indices_tracker_for_traffic_lights_that_require_a_state_update.GetAt(index_inside_the_indices_tracker)].SetState(
                    _array_of_traffic_lights[_indices_tracker_for_traffic_lights_that_require_a_state_update.GetAt(index_inside_the_indices_tracker)].GetState().NextState());
            }

            for (size_t traffic_light_index = 0; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                if (_indices_tracker_for_traffic_lights_that_require_a_state_update.IsIn(traffic_light_index))
                {
                    _array_of_current_traffic_light_delays[traffic_light_index] =  
                        _array_of_traffic_light_transition_delays[traffic_light_index].GetDelay(
                            _array_of_traffic_lights[traffic_light_index].GetState());
                }
                else
                {
                    _array_of_current_traffic_light_delays[traffic_light_index] = _array_of_current_traffic_light_delays[traffic_light_index] - _last_minimal_delay;
                }
            }
        
            size_t index_of_traffic_light_with_minimal_delay_for_its_current_state = 0;
            for (size_t traffic_light_index = 1; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                if (_array_of_current_traffic_light_delays[index_of_traffic_light_with_minimal_delay_for_its_current_state] >
                    _array_of_current_traffic_light_delays[traffic_light_index])
                {
                    index_of_traffic_light_with_minimal_delay_for_its_current_state = traffic_light_index;
                }
            }
            unsigned minimal_delay = _array_of_current_traffic_light_delays[index_of_traffic_light_with_minimal_delay_for_its_current_state];
            
            // Find all indices with minimal delay and push them into the indices tracker:
            INDEX_CONTAINER new_indices_tracker_for_traffic_lights_that_require_a_state_update;
            for (size_t traffic_light_index = 0; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                if (_array_of_current_traffic_light_delays[traffic_light_index] == minimal_delay) 
                {
                   new_indices_tracker_for_traffic_lights_that_require_a_state_update.PushIndex(traffic_light_index);
                }
            }
            
            _indices_tracker_for_traffic_lights_that_require_a_state_update = new_indices_tracker_for_traffic_lights_that_require_a_state_update;
            _last_minimal_delay = minimal_delay;
        }
};

struct TRAFFIC_LIGHT_PIN_IDS
{
    int red;
    int yellow;
    int green;
};

TRAFFIC_LIGHT_PIN_IDS traffic_light_pin_ids1 = { .red = 13, .yellow = 12, .green = 11 };
TRAFFIC_LIGHT traffic_light1;
TRAFFIC_LIGHT_TRANSITION_DELAYS traffic_light_transition_delays1;

TRAFFIC_LIGHT_PIN_IDS traffic_light_pin_ids2 = { .red = 10, .yellow = 9, .green = 8 };
TRAFFIC_LIGHT traffic_light2;
TRAFFIC_LIGHT_TRANSITION_DELAYS traffic_light_transition_delays2;

TRAFFIC_LIGHT_SCHEDULER<2U> traffic_light_scheduler;

void setup()
{
    traffic_light1 = TRAFFIC_LIGHT::Create(
        LED::Create(traffic_light_pin_ids1.red),
        LED::Create(traffic_light_pin_ids1.yellow),
        LED::Create(traffic_light_pin_ids1.green),
        TRAFFIC_LIGHT_STATE::DRIVE
    );
    
    traffic_light_transition_delays1 = TRAFFIC_LIGHT_TRANSITION_DELAYS::Create(
        TRAFFIC_LIGHT_DELAY::CreateConstant(5000),
        TRAFFIC_LIGHT_DELAY::CreateConstant(1000),
        TRAFFIC_LIGHT_DELAY::CreateConstant(5000),
        TRAFFIC_LIGHT_DELAY::CreateConstant(1000)
    );
    
    traffic_light2 = TRAFFIC_LIGHT::Create(
        LED::Create(traffic_light_pin_ids2.red),
        LED::Create(traffic_light_pin_ids2.yellow),
        LED::Create(traffic_light_pin_ids2.green),
        TRAFFIC_LIGHT_STATE::STOP
    );
    
    traffic_light_transition_delays2 = TRAFFIC_LIGHT_TRANSITION_DELAYS::Create(
        TRAFFIC_LIGHT_DELAY::CreateConstant(5000),
        TRAFFIC_LIGHT_DELAY::CreateConstant(1000),
        TRAFFIC_LIGHT_DELAY::CreateConstant(5000),
        TRAFFIC_LIGHT_DELAY::CreateConstant(1000)
    );
    
    traffic_light_scheduler = TRAFFIC_LIGHT_SCHEDULER<2U>::Create();
    
    traffic_light_scheduler.PushTrafficLight(traffic_light1);
    traffic_light_scheduler.PushTrafficLight(traffic_light2);
    
    traffic_light_scheduler.PushTrafficLightTransitionDelays(traffic_light_transition_delays1);
    traffic_light_scheduler.PushTrafficLightTransitionDelays(traffic_light_transition_delays2);
    
    traffic_light_scheduler.Initialize();
}

void loop()
{
    traffic_light_scheduler.Run();
}
