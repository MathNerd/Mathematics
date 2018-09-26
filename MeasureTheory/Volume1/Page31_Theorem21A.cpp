#include <stdio.h>
#include <math.h>

typedef unsigned natural;
typedef struct {
    natural n;
    natural m;
} natural_pair;

natural f(natural_pair x)
{
    return (x.n + x.m - 2)*(x.n + x.m - 1)/2 + x.m;
}

natural_pair g(natural k)
{
    natural_pair x;
    natural upper_bound_for_m = (sqrt(8*k+1)-1)/2;
    bool is_found = false;
    
    for (x.m = 1; !is_found && x.m <= upper_bound_for_m; x.m = x.m + 1)
    {
        x.n = (3 + sqrt(8*(k-x.m)+1))/2-x.m;
        
        if (f(x) == k)
            is_found = true;
    }
    x.m = x.m - 1;
    
    return x;
}

int main(void)
{
    // Prinf 'f':
    for (natural n = 1; n <= 4; n++)
    {
        for (natural m = 1; m <= 4; m++)
        {
            natural_pair x = {n, m};
            natural k = f(x);
            printf("f(%u,%u) = %u\n", x.n, x.m, k);
        }
    }
    
    // Prinf 'g':
    for (natural k = 1; k <= 10; k++)
    {
        natural_pair x = g(k);
        printf("g(%u) = (%u,%u)\n", k, x.n, x.m);
    }
        
    return 0;
}
