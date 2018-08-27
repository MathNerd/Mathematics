#include <iostream>

// THE SEQUENCE:
double a(int n)
{
    return 1.0/n;
}

// THE INDICES SEQUENCE:
int n(int k)
{
    return k*k;
}

// THE SUBSEQUENCE OF THE SEQUENCE 'a’ THAT CORRESPONDS TO THE INDICES SEQUENCE:
double s(int k)
{
    return a(n(k));
}

int main() 
{
    for(int k = 1; k <= 10; k++)
       std::cout << "n(" << k << ") = " << n(k) << ", s(" << k << ") = " << s(k) << std::endl;
}
