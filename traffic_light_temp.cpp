void Initialize(void)
        {
            if (_traffic_light_push_counter != TRAFFIC_LIGHTS_COUNT)
                print_error("FATAL ERROR: Cannot intialize the scheduler beacuse the number of traffic lights "
                            " that were pushed doesn't corresponed to number of traffic lights that the scheduler expects.\n");
                            
            if (_traffic_light_transition_delays_push_counter != TRAFFIC_LIGHTS_COUNT)
                print_error("FATAL ERROR: Cannot intialize the scheduler beacuse the number of traffic light transition delays"
                            " that were pushed doesn't corresponed to number of traffic lights that the scheduler expects.\n");
                
            size_t index_of_traffic_light_with_minimal_delay_for_its_current_state = 0;
            for (size_t traffic_light_index = 1; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                if (_array_of_traffic_light_transition_delays[index_of_traffic_light_with_minimal_delay_for_its_current_state].GetDelay(
                        _array_of_traffic_lights[index_of_traffic_light_with_minimal_delay_for_its_current_state].GetState()) >
                    _array_of_traffic_light_transition_delays[traffic_light_index].GetDelay(_array_of_traffic_lights[traffic_light_index].GetState())) 
                {
                    index_of_traffic_light_with_minimal_delay_for_its_current_state = traffic_light_index;
                }
            }
            unsigned minimal_delay = _array_of_traffic_light_transition_delays[index_of_traffic_light_with_minimal_delay_for_its_current_state].GetDelay(
                _array_of_traffic_lights[index_of_traffic_light_with_minimal_delay_for_its_current_state].GetState());
            
            // Find all indices with minimal delay and push them into an indices tracker:
            for (size_t traffic_light_index = 0; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                if (_array_of_traffic_light_transition_delays[traffic_light_index].GetDelay(_array_of_traffic_lights[traffic_light_index].GetState()) == minimal_delay) 
                {
                   _indices_tracker_for_traffic_lights_that_require_a_state_update.PushIndex(traffic_light_index);
                }
            }
            
            _last_minimal_delay = minimal_delay;
        }
    
        void Run(void)
        {
            /*
            _traffic_light_array[0].SetState(TRAFFIC_LIGHT_STATE::STOP);
            delay(5000);
            _traffic_light_array[0].SetState(TRAFFIC_LIGHT_STATE::PREPARE_TO_DRIVE);
            delay(1000);
            _traffic_light_array[0].SetState(TRAFFIC_LIGHT_STATE::DRIVE);
            delay(5000);
            _traffic_light_array[0].SetState(TRAFFIC_LIGHT_STATE::PREPARE_TO_STOP);
            delay(1000);
            */
            
            // Wait for last_minimal_delay:
            delay(_last_minimal_delay);
            
            // Update the states for all traffic lights that required an update that were tracked inside the indices tracker:
            for (size_t traffic_light_index = 0; traffic_light_index < _indices_tracker_for_traffic_lights_that_require_state_update.GetCount(); traffic_light_index++)
                _array_of_traffic_lights[_indices_tracker_for_traffic_lights_that_require_a_state_update.GetAt(index)].SetState(
                    _array_of_traffic_lights[_indices_tracker_for_traffic_lights_that_require_a_state_update.GetAt(index)].GetState().NextState());

            // Checks wether there is an index that is not in the indices tracker:
            bool is_there_a_traffic_light_index_that_is_not_in_the_indices_tracker = false;
            size_t index_of_traffic_light_that_is_not_in_the_indices_tracker_with_minimal_delay_for_its_current_state;
                
            for (size_t traffic_light_index = 0;
                 !is_there_a_traffic_light_index_that_is_not_in_the_indices_tracker && traffic_light_index < TRAFFIC_LIGHTS_COUNT; 
                 traffic_light_index++)
            {
                if (!_indices_tracker_for_traffic_lights_that_require_a_state_update.IsIn(traffic_light_index))
                {
                    is_there_a_traffic_light_index_that_is_not_in_the_indices_tracker = true;
                    index_of_traffic_light_that_is_not_in_the_indices_tracker_with_minimal_delay_for_its_current_state = traffic_light_index;
                }
            }
            
            // Find minimal delay for those indices that are not in the indices tracking array:
            if (is_there_a_traffic_light_index_that_is_not_in_the_indices_tracker)
            {
                for (size_t traffic_light_index = 0; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
                {
                    if (!_indices_tracker_for_traffic_lights_that_require_a_state_update.IsIn(traffic_light_index))
                    {
                        if (_array_of_traffic_light_transition_delays[index_of_traffic_light_that_is_not_in_the_indices_tracker_with_minimal_delay_for_its_current_state].GetDelay(
                            _array_of_traffic_lights[index_of_traffic_light_that_is_not_in_the_indices_tracker_with_minimal_delay_for_its_current_state].GetState()) >
                            _array_of_traffic_light_transition_delays[traffic_light_index].GetDelay(
                                _array_of_traffic_lights[traffic_light_index].GetState())) 
                        {
                            index_of_traffic_light_with_minimal_delay_for_its_current_state = traffic_light_index;
                        }
                    }
                }
                
                // Find minimal delay for those indices that are not in the indices tracking array:
                unsigned minimal_delay_for_traffic_lights_that_their_indices_are_not_in_the_indices_tracking_array = 
                    _array_of_traffic_light_transition_delays[index_of_traffic_light_with_minimal_delay_for_its_current_state].GetDelay(
                        _array_of_traffic_lights[index_of_traffic_light_with_minimal_delay_for_its_current_state].GetState());
                        
                unsigned shifted_minimal_delay_for_traffic_lights_that_their_indices_are_not_in_the_indices_tracking_array =
                        minimal_delay_for_traffic_lights_that_their_indices_are_not_in_the_indices_tracking_array - _last_minimal_delay;
                        
                // ?????????????????????????????
                for (size_t traffic_light_index = 0; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
                {
                    if (_indices_tracker_for_traffic_lights_that_require_a_state_update.IsIn(traffic_light_index))
                    {
                        if (_array_of_traffic_light_transition_delays[traffic_light_index].GetDelay(_array_of_traffic_lights[traffic_light_index].GetState()) == shifted_minimal_delay) 
                        {
                           new_traffic_light_scheduler_minimal_delay_indices_tracker.PushIndex(traffic_light_index);
                        }
                    }
                    else
                    {
                        if (_traffic_light_transition_delays_array[traffic_light_index].GetDelay(_traffic_light_array[traffic_light_index].GetState()) == 
                            shifted_minimal_delay_for_traffic_lights_that_their_indices_are_not_in_the_indices_tracking_array) 
                        {
                           new_traffic_light_scheduler_minimal_delay_indices_tracker.PushIndex(traffic_light_index);
                        }
                    }
                     new_indices_tracker_for_traffic_lights_that_require_a_state_update.PushIndex(traffic_light_index);
                }
            }
            
            //?????????????????????????????/
            
            // Find all indices with the "corresponding" minimal delay:
            INDEX_CONTAINER new_indices_tracker_for_traffic_lights_that_require_a_state_update;
            for (size_t traffic_light_index = 0; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                 new_indices_tracker_for_traffic_lights_that_require_a_state_update.PushIndex(traffic_light_index);
            }
            
            INDEX_CONTAINER new_indices_tracker_for_traffic_lights_that_require_a_state_update;
            for (size_t traffic_light_index = 0; traffic_light_index < TRAFFIC_LIGHTS_COUNT; traffic_light_index++)
            {
                if (_indices_tracker_for_traffic_lights_that_require_a_state_update.IsIn(traffic_light_index))
                {
                    if (_array_of_traffic_light_transition_delays[traffic_light_index].GetDelay(_array_of_traffic_lights[traffic_light_index].GetState()) == shifted_minimal_delay) 
                    {
                       new_traffic_light_scheduler_minimal_delay_indices_tracker.PushIndex(traffic_light_index);
                    }
                }
                else
                {
                    if (_traffic_light_transition_delays_array[traffic_light_index].GetDelay(_traffic_light_array[traffic_light_index].GetState()) == minimal_delay_of_those_that_are_not_in_the_indices_tracking_array) 
                    {
                       new_traffic_light_scheduler_minimal_delay_indices_tracker.PushIndex(traffic_light_index);
                    }
                }
            }
            
            _indices_tracker_for_traffic_lights_that_require_a_state_update = new_indices_tracker_for_traffic_lights_that_require_a_state_update;
            last_minimal_delay = shifted_minimal_delay;
        }
