#include <stdio.h>
#include <math.h>


int lower(int n)
{
    if (n <= 0)
    {
        printf("FATAL ERROR: argument \'n\' must be >= 1\n");
        return 0;
    }
    else // n > 0 ——> n >= 1
    {
        return ceil((-1+sqrt(1+8*n))/2.0);
    }
}

int upper(int n)
{
    if (n <= 0)
    {
        printf("FATAL ERROR: argument \'n\' must be >= 1\n");
        return 0;
    }
    else // n > 0 ——> n >= 1
    {
        return floor((1+sqrt(1+8*(n-1)))/2.0);
    }
}

double a(int n)
{
    if (n <= 0)
    {
        printf("FATAL ERROR: argument \'n\' must be >= 1\n");
        return 0;
    }
    else // n > 0 --> n >= 1
    {
        return n-ceil((-1+sqrt(1+8*n))/2.0);
    }
}

int main() {
    for (int n = 1; n <= 22; n++)
        printf("lower(%d) = %d, upper(%d) = %d\n", n, lower(n), n, upper(n));
    
    return 0;
}
