#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <termios.h>

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
    
    for(int x = MIN_X; x <= MAX_X; x++)
    {
        for(int y = MIN_Y; y <= MAX_Y; y++)
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

STATE next_state(STATE current_state, INPUT input)
{
    STATE new_state;
    
    new_state.frame = current_state.frame+1;
    new_state.unit_position.x = 1;
    new_state.unit_position.y = 2;
    new_state.shoot_delay = current_state.shoot_delay > 0 ? current_state.shoot_delay - 1 : 0;
    new_state.shot_positions = current_state.shot_positions;
    
    return new_state;
}

void read_input(void (*process_input)(char))
{
    struct termios told,tnew;
    char c;
    tcgetattr(0,&told);
    tnew = told;
    tnew.c_lflag&=~ICANON;
    tcsetattr(0,TCSANOW,&tnew);
    while (read(0,&c,1) && c!='q') process_input(c);
    tcsetattr(0,TCSANOW,&told);
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
    //int input;
    
    
    
    
    init();
    loop(run);
    
    return 0;
}
