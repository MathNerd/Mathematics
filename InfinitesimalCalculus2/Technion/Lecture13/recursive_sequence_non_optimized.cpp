#include<iostream>

double a(int n)
{
    if (n==1)
        return 0.25;
    else if (n>1)
    {
        double a_prev = a(n-1);
        return a_prev*a_prev + 0.25;
    }
    else
    {
        printf("FATAL ERROR!\n");
        return 0.0;
    }
}

int main()
{
    std::cout.precision(17);
    
    for (int i = 1; i<=30; i++)
        std::cout << "a(" << i << ") = " << a(i) << std::endl;
       
    return 0; 
}
