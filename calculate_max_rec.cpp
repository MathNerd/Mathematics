// Calculates the maximal value in an array recursively.

#include <iostream>

#define max(a,b) ((a) > (b) ? (a) : (b))
#define index(n) ((n)-1)
#define array_length(A) sizeof((A)) / sizeof((A)[0])

template<typename T>
T array_max(T a[], size_t n)
{
    if (n == 0U)
    {
        fprintf(stderr, "FATAL ERROR: 'n' must be > 0\n");
        exit(EXIT_FAILURE);
    }
    else if (n == 1U)
        return a[0];
    else /* size > 1U */
    {
        return max(array_max(a, n - 1), a[index(n)]);
    }
}

template<typename T>
void array_print(T a[], size_t n)
{
    std::cout << "{";
    if (n > 0)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
            std::cout << a[i] << ",";
        std::cout << a[i];
    }
    std::cout << "}";
}

int main() 
{
    int x[] = {1, 3, 7, 2, 5};
    size_t length_x = array_length(x);
    array_print(x, length_x);
    std::cout << std::endl;
    std::cout << array_max(x, length_x) << std::endl;
    
    double y[] = {3.5, 2.3, 7.8, 9.2, 1.5, 5.3};
    size_t length_y = array_length(y);
    array_print(y, length_y);
    std::cout << std::endl;
    std::cout << array_max(y, length_y) << std::endl;
    
    return 0;
}
