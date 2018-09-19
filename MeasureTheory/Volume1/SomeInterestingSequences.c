#include <stdio.h>

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

int main(void)
{
    interval I;
    
    printf("%f\n", partition_point(1.0,2.0,3,0));
    printf("%f\n", partition_point(1.0,2.0,3,1));
    printf("%f\n", partition_point(1.0,2.0,3,2)); 
    printf("%f\n", partition_point(1.0,2.0,3,3));
    
    I = partition_interval(1.0,2.0,3,0);
    printf("[%f,%f]\n", I.a, I.b);
    
    I = partition_interval(1.0,2.0,3,1);
    printf("[%f,%f]\n", I.a, I.b);
    
    I = partition_interval(1.0,2.0,3,2);
    printf("[%f,%f]\n", I.a, I.b);
    
    return 0;
}
