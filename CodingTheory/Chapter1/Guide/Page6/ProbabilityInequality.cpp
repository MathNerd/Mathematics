#include <iostream>
#include <cmath>

using namespace std;

double prob(double p, int n, int i)
{
    if (n<1)
    {
        printf("FATAL ERROR: \'n\' must be >= 1\n");
        return 0.0;
    }
    
    if (i<0 || n<i)
    {
        printf("FATAL ERROR: \'i\' must be >= 0 and <= n\n");
        return 0;
    }
    
    return pow(p,i)*pow(1-p,n-i);
}

int main() {
	double p = 0.1;
	int n = 10;
	
	cout.precision(17);
	for (int i = 0; i <= n; i++)
	    cout<<"prob("<<p<<", "<<n<<", "<<i<<") = " << prob(p,n,i) << endl;
	
	return 0;
}
