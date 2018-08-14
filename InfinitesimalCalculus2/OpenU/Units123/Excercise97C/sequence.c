#include <stdio.h>
#include <math.h>

int CHECK_FOR_ERRORS_IN_SEQUENCE_INDEX(int n)
{
     if(n <= 0)
     {
          printf("FATAL ERROR: argument \'n\' must be >= 1\n");
          return 1;
     }
     else // n > 0 —-> n >= 1
          return 0;
}
      
int lower(int n)
{
    if (CHECK_FOR_ERRORS_IN_SEQUENCE_INDEX(n))
        return 0;
    else
        return ceil((-1+sqrt(1+8*n))/2.0);
}

int upper(int n)
{
    if (CHECK_FOR_ERRORS_IN_SEQUENCE_INDEX(n))
        return 0;
    else
        return floor((1+sqrt(1+8*(n-1)))/2.0);
}

int a(int n)
{
    if (CHECK_FOR_ERRORS_IN_SEQUENCE_INDEX(n))
        return 0;
    else
    {
        int i = lower(n)-1;
        return n-i*(i+1)/2;//ceil((-1+sqrt(1+8*n))/2.0)+1;
    }
}

int main() {
    for (int n = 1; n <= 22; n++)
        printf("lower(%d) = %d, upper(%d) = %d, a(%d) = %d\n", n, lower(n), n, upper(n), n, a(n));
    
    return 0;
}
