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

int compar(const void* a, const void* b)
{
    return a <= b;
}

natural g(natural k)
{
    static natural n;
    static natural Y[m];
    static natural* X;
    static is _initialized = false;
    
    if(!is_initialized)
    {
        for (unsigned i = 0; i < m; i++)
        {
            Y[i] = f(i);
        }
        
        qsort(Y, m, sizeof(natural), compar);
        
        for (unsigned i = 0; i < m; i++)
        {
            printf("%u  ", Y[i]);
        }
        printf("\n");
        
        natural max_f = Y[m-1];
        
        n = max_f - m;
        
        X = malloc(sizeof(natural)*n);
        
        for (natural i = 1; i <= max_f; i++)
        {
            if ()
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
