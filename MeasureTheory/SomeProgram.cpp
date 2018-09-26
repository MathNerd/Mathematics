#include <iostream>
#include <cstdlib>

typedef unsigned natural;
const natural m = 10;

natural f(natural k)
{
    if (1 <= k && k <= m)
        return k*k;
        
    fprintf(stderr, "FATAL ERROR: argument for function 'f' is not in range.\n");
    return 1;
}

natural g(natural k)
{
    static natural n;
    static natural* X;
    static is _initialized = false;
    
    if(!is_initialized)
    {
        natural max_f = 1;
        
        for (natural i = 1; i <= m; i++)
        {
            natural f_i = f(i);
            
            if (max_f < f_i)
                max_f = f_i;
        }
        
        n = max_f - m;
        
        X = malloc(sizeof(natural)*n);
        
        for (natural i = 1; i <= n; i++)
        {
            X[i] = 1; // min([max_f]\{g(1),...,g(k-1))
            
        }
        
        is_initialized = true;
    }
    
    if (1 <= k)
        return 10;
        
    fprintf(stderr, "FATAL ERROR: argument for function 'g' is not in range.\n");
    return 1;
}

int main(void)
{
    printf("hello %u\n", g(6+10));
    
    return 0;
}
