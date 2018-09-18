#include <stdio.h>
#include <vector>
#include <math.h>

#define PI 3.14159265358979323846

struct position
{
    double x;
    double y;
};

struct STATE
{
    unsigned frame;
    position unit_position;
    unsigned shoot_delay;
    std::vector<position> shot_positions;
};

const STATE start_state = {0,{0,0},0,{}};

void print_state(STATE state)
{
    const int MIN_X = -3;
    const int MAX_X = 3;
    const int MIN_Y = -3;
    const int MAX_Y = 3;
    
    for(int y = MAX_Y; y >= MIN_Y; y--)
    {
        for(int x = MIN_X; x <= MAX_X; x++)
        {
            if (state.unit_position.x == x && state.unit_position.y == y)
                printf("*");
            else
                printf("+");
        }
        printf("\n");
    }
}

enum class INPUT{none, shoot};

position position_function(unsigned n)
{
    position new_position;
    
    const unsigned R = 3U; // radiusa
    
    if (n <= R)
    {
        new_position.x = n;
        new_position.y = 0;
    }
    else // n > 3U
    {
        double alpha = PI*0.1*(n-3);
        double x = R*cos(alpha);
        double y = R*sin(alpha);
    
        new_position.x = floor(x);
        new_position.y = floor(y);
    }
    
    return new_position;
}

STATE next_state(STATE current_state, INPUT input)
{
    STATE new_state;
    
    new_state.frame = current_state.frame+1;
    new_state.unit_position = position_function(new_state.frame);
    new_state.shoot_delay = current_state.shoot_delay > 0 ? current_state.shoot_delay - 1 : 0;
    new_state.shot_positions = current_state.shot_positions;
    
    return new_state;
}

static STATE state;

void init(void)
{
    state = start_state;
    printf("\n");
    print_state(state);
    printf("\n");
}

void run(char c)
{
    INPUT input;
    if (c == 's')
        input = INPUT::shoot;
    else
        input = INPUT::none;
    
    state = next_state(state, input);
    
    printf("\n");
    
    print_state(state);
    
    printf("\n");
}

void loop(void (*process_input)(char))
{
    int c;
    
    while((c = getchar()) != EOF && c != 'q')
    {
        process_input(c);
    }
}

int main(void)
{
    init();
    loop(run);
    
    return 0;
}
