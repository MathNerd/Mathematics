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
        
        for (unsigned k = 0; k <= 2; k++)
        {
            interval J = partition_interval(I.a, I.b, 3, k);
            printf("f(%u)=%f %s [%f,%f] = PI(%u)\n", n, fn, (is_in_interval(fn, J) ? "in" : "not in"), J.a, J.b, k);
        }
        printf("\n");
        
        //printf("f(%d) = %f, a(%d) = %f, b(%d) = %f\n", n, fn, n, I.a, n, I.b);
    }
    
    return 0;
}
