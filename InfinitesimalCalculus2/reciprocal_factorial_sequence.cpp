#include <iostream>

using namespace std;

int fact(int n)
{
    if (n < 0)
    {
        printf("FATAL ERROR!\n");
        return 0;
    }
    else // n >= 0
    {
        if (n <= 1)
            return 1;
        else // n > 1
            return n*fact(n-1);
    }
}

double s(int n)
{
    if(n < 0)
    {
        printf("FATAL ERROR!\n");
        return 0.0;
    }
    else // n >= 0
    {
        double sum = 0.0;
        
        for (int k = 0; k <= n; k++)
            sum += 1.0/fact(k);
            
        return sum;
    }
}

int main() {
	const int MAX_INDEX = 12;
	cout.precision(17);
	for (int n = 0; n <= MAX_INDEX; n++)
	    cout << "s(" << n << ") = " << s(n) << endl;
}
