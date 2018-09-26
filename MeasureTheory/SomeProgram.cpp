
#include <iostream>
#include <cstdlib>

#define DBG_PRINT 0

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
    static bool is_initialized = false;
    
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
        
        #if DBG_PRINT == 1
        printf("max_f = %u, n = %u, m = %u\n", max_f, n, m);
        #endif
        
        X = (natural*)(malloc(sizeof(natural)*n));
        
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
        
        #if DBG_PRINT
        for (unsigned i = 0; i < n; i++)
        {
            printf("%u  ", X[i]);
        }
        printf("\n");
        #endif
    }
    
    if (1 <= k && k <= n)
        return X[k-1];
    else if (n + 1 <= k)
        return k + m;
        
    fprintf(stderr, "FATAL ERROR: argument for function 'g' is not in range.\n");
    return 1;
}

natural h(natural k)
{
    if (1 <= k && k <= m)
        return f(k);
    else if (m+1 <= k)
        return g(k - m);
        
    fprintf(stderr, "FATAL ERROR: argument for function 'h' is not in range.\n");
    return 1;
}

int main(void)
{
    for (natural k = 1; k <= 101; k++)
         printf("h(%u) = %u\n", k, h(k));
    
    return 0;
}
