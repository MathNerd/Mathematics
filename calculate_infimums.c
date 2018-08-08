

    #include<stdio.h>
    #include<math.h>
    
    #define PI 3.14159265358979323846
    #define INFINITY 999999999
    #define max(X, Y) (((X) < (Y)) ? (Y) : (X))
    
    // The sequence $\{a_n\}_{n=1}^\infty$:
    double a(int n)
    {
        return n*sin(PI * n / 4);
    }
    
    // Checks wether the argument equals an element in the sequence,
    // If it is, The function will return the index in which it was found,
    // And if it was not, It will return -1.

    int search_for(double L)
    {
        // The maximal index that must be examined:
        int max_index = ceil(sqrt(2) * L);
        
        // The index at which it was found (if was found):
        int index = 1;
        
        // Indicates wether the value was found at the current interation:
        bool is_found = false;
        
        do
        {
            if(a(index) == L)
                is_found = true;
            else
                index++;
        }
        while (!is_found  && index <= max_index);
        
        if (!is_found)
            index = -1;
        
        return index;
    }

    double infimum(double L)
    {
       double minimal_distance; // Will hold in the end the value of the appropriate infimum.
       int m; // Holds the first index for which $L=a_m$ if any.
       int k0; // Holds the index that its existence was guaranteed in cases (1) and (2).
       int nk0; // Holds the element of the sequence $\{n_k\}$ at the index $k_0$. 
       int M; // Holds the value of $M$ as defined in case (2) [Used only if we are dealing with case (2)].
       int N; // Holds the greatest index that must be considered inorder to evaluate the minimums.
    
       // We have to choose an index $k_0$ that will ensure that $L<a_{n_{k_0}}$, 
       // And the $k_0$ defined this way will satisfy it.
       k0 = ceil((sqrt(2)*L-1)/8)+1;
    
       // The $k_0$’s element of the sequence $\{n_k\}$.
       nk0 = 8*k0+1;
    
       // Searches for the first index for which $L=a_m$ if any.
       m = search_for(L);
       
       // L equals some element in the sequence and thus $m>0$:
       if (m > 0)
       {
           // Since we are dealing here with case (2), 
           // We will define $M$ and $N$ as they were defined in case (2).
           M = m + 9 - m%8;
           N = max(M,nk0)+8;
       }

       // L does not equal any element in the sequence and thus $m=-1$.
       else
       {
           // Since we are dealing here with case (1),
           // We will define $N$ as it was defined in case (1).
           N = nk0 + 8;
       }
       
       // The following chunk of code will calculate the appropriate minimum based   
       // on wether we are dealing with case (1) or case (2).
       // Note:
       // If we are dealing with case (1), Then we know that $m=-1$, 
       // And thus the condition $i\neq m$ in the for loop header will never be satisfied,
       // And in the end $minimal_distance$ will hold the value $\min\limits_{n\in\{1,...,N\}}|a_n-L|$
       // And if we are dealing with case (2), Then we know that $m\in\{1,...,N\}$,
       // And thus the condition $i\neq m$ in the for loop header will skip over the
       // index $m$, And in the end $minimal_distance$ will hold the value  $\min\limits_{n\in\{1,...,N\}\backslash\{m\}}|a_n-L|$ 
       minimal_distance = INFINITY;
       for (int i = 1; i != m && i <= N; i++)
       {
           double current_distance = abs(a(i) - L);
           if (current_distance < minimal_distance)
               minimal_distance = current_distance;
       }
       
       return minimal_distance;
    }

    void test(double L)
    {
       printf("infimum(%f) = %f\n", L, infimum(L));
    }
    
    int main(void)
    {
        test(1);
        test(2);
        test(sqrt(2));
        test(sqrt(5));
        test(10);
        test(100);
    
        return 0;
    }
