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

int main(void)
{
    // a >= b
    printf("%f\n", partition_point(2.0,1.0,0,4));
    
    // n < 1
    printf("%f\n", partition_point(1.0,2.0,0,4));
    
    // i > n
    printf("%f\n", partition_point(1.0,2.0,3,4));
    
    // good
    printf("%f\n", partition_point(1.0,2.0,3,0));
    printf("%f\n", partition_point(1.0,2.0,3,1));
    printf("%f\n", partition_point(1.0,2.0,3,2)); 
    printf("%f\n", partition_point(1.0,2.0,3,3));
    
    return 0;
}
