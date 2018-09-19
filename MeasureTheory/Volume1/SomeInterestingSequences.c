#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

double partition_point(double a, double b, unsigned n, unsigned i)
{
    if (a >= b)
    {
        fprintf(stderr, "FATAL ERROR: 'a' must be < 'b'.\n");
        return 0.0;
    }
    
    if (n < 1)
    {
        fprintf(stderr, "FATAL ERROR: 'n' must be >= 1.\n");
        return 0.0;
    }
    
    if (i > n)
    {
        fprintf(stderr, "FATAL ERROR: 'i' must be <= 'n'.\n");
        return 0.0;
    }
    
    return ((n - i)*a + i*b)/n;
}

typedef struct interval
{
    double a;
    double b;
} interval;

interval partition_interval(double a, double b, unsigned n, unsigned i)
{
    interval I;
    
    if (i >= n)
    {
        fprintf(stderr, "FATAL ERROR: 'i' must be <= 'n-1'.\n");
        
        I.a = 0;
        I.b = 0;
        
        return I;
    }

    I.a = partition_point(a ,b, n, i);
    I.b = partition_point(a, b, n, i+1);
    
    return I;
}

bool is_in_interval(double x, interval I)
{
    return (I.a <= x && x <= I.b);
}

// f:N—->[0,1]
double f(unsigned n)
{
    if (n < 1)
    { 
        fprintf(stderr, "FATAL ERROR: 'n' must be >= 1.\n");
        return 0.0;
    }
    
    return ((double)rand())/RAND_MAX;
}

int main(void)
{
    const unsigned count = 10;
    interval I;
    I.a = 0.0;
    I.b = 1.0;
    
    srand(time(0));
    for(unsigned n = 1; n <= count; n++)
    {
        double fn = f(n);
        
        const unsigned number_of_partition_intervals = 3;
        unsigned number_of_partition_intervals_to_which_fn_does_not_belong = 0;
        interval partition_intervals_to_which_fn_does_not_belong[number_of_partition_intervals];
        for (unsigned k = 0; k < number_of_partition_intervals; k++)
        {
            interval PI = partition_interval(I.a, I.b, number_of_partition_intervals, k);
            
            if (!is_in_interval(fn, PI))
            {
                 partition_intervals_to_which_fn_does_not_belong
                     [number_of_partition_intervals_to_which_fn_does_not_belong++] = PI;
            }
            
            printf("f(%u)=%g %s [%g,%g] = PI(%u)\n", n, fn, (is_in_interval(fn, PI) ? "in" : "not in"), PI.a, PI.b, k);
        }
        printf("\n");
        
        printf("{ ");
        for (unsigned i = 0; i <  number_of_partition_intervals_to_which_fn_does_not_belong; i++)
        {
            interval PI =  partition_intervals_to_which_fn_does_not_belong[i];
            printf("[%g,%g] ", PI.a, PI.b);
        }
        printf("}\n");
        
        if (number_of_partition_intervals_to_which_fn_does_not_belong > 0)
        {
            interval randomly_choosen_interval = partition_intervals_to_which_fn_does_not_belong
                [rand() % number_of_partition_intervals_to_which_fn_does_not_belong];
         
            printf("[%g,%g]\n\n", randomly_choosen_interval.a, randomly_choosen_interval.b);
        }
        
        //printf("f(%d) = %f, a(%d) = %f, b(%d) = %f\n", n, fn, n, I.a, n, I.b);
    }
    
    return 0;
}
