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
        natural max_f = 1;
         
        for (natural i = 1; i <= m; i++)
        {
            natural f_i = f(i);
             
            if (max_f < f_i)
                max_f = f_i;
        }
        
        n = max_f - m;        
        
        X = malloc(sizeof(natural)*n);
        
        unsigned i = 0;
        for (natural k = 1; k <= max_f; k++)
        {
            bool is_found = false;
            
            for (natural l = 1; !is_found && l <= m; l++)
            {
                if (k == f(l))
                    is_found = true;
            }
            
            if (!is_found)
                X[i++] = k;         
        }
        
        is_initialized = true;
        
        for (unsigned i = 0; i < m; i++)
        {
            printf("%u  ", X[i]);
        }
        printf("\n");
    }
    
    if (1 <= k && k <= n)
        return X[k-1];
    else if (n + 1 <= k)
        return k + m;
        
    fprintf(stderr, "FATAL ERROR: argument for function 'g' is not in range.\n");
    return 1;
}

int main(void)
{
    printf("hello %u\n", g(6+10));
    
    return 0;
}
