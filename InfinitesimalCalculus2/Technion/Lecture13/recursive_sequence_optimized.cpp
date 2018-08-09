#include<iostream>
#include<vector>

double a(int n)
{
    #define SAVED_VALUE(n) saved_values[(n)-1]
    #define SAVED_VALUES_COUNT int(saved_values.size())
    #define SAVE_VALUE(val) saved_values.push_back((val))
    static std::vector<double> saved_values{0.25};
    
    if (n <= SAVED_VALUES_COUNT)
        return SAVED_VALUE(n);
    else if (n > SAVED_VALUES_COUNT)
    {
        double a_prev = a(n-1);
        double a_current = a_prev*a_prev + 0.25;
        
        SAVE_VALUE(a_current);
        
        return a_current;
    }
    else
    {
        printf("FATAL ERROR!\n");
        return 0.0;
    }
    
    #undef SAVED_VALUE
    #undef SAVED_VALUES_COUNT
    #undef SAVE_VALUE
}

int main()
{
    std::cout.precision(17);
    
    for (int i = 1; i<=50; i++)
        std::cout << "a(" << i << ") = " << a(i) << std::endl;
       
    return 0; 
}
