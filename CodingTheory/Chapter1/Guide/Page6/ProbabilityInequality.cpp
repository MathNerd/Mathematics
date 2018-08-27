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

// distance between successive elements of 'prob'.
namespace Distance 
{
	
double distance(double p, int n, int i)
{
    if (n<1)
    {
        printf("FATAL ERROR: \'n\' must be >= 1\n");
        return 0.0;
    }
    
    if (i<0 || n-1<i)
    {
        printf("FATAL ERROR: \'i\' must be >= 0 and <= n-1\n");
        return 0;
    }
    
    return pow(p,i)*pow(1-p,n-i-1)*abs(2*p-1);
}

double lower_bound(double p, int n)
{
    if(p<0.5)
        return pow(p,n-1)*abs(2*p-1);
    else if(p>0.5)
        return pow(1-p,n-1)*abs(2*p-1);
    else
        return 0;
}

double upper_bound(double p, int n)
{
    if(p<0.5)
        return pow(1-p,n-1)*abs(2*p-1);
    else if (p>0.5)
        return pow(p,n-1)*abs(2*p-1);
    else
        return 0;
}
	
}

int main() {
	double p = 0.4; //0.5; //0.499999; //0.500001;
	int n = 10;
	
	cout.precision(5);
	
	cout<<"PROBABILITIES:\n";
	for (int i = 0; i <= n; i++)
	{
	    cout<<"prob("<<p<<", "<<n<<", "<<i<<") = " << prob(p,n,i) << endl;
	}
	
	cout<<"DISTANCES:\n";
	for (int i = 0; i <= n-1; i++)
	{
	    cout<<"lower_bound("<<p<<", "<<n<<") = "<<Distance::lower_bound(p,n)
		<<" <= distance("<<p<<", "<<n<<", "<<i<<") = " << Distance::distance(p,n,i)
		<<" <= upper_bound("<<p<<", "<<n<<") = " << Distance::upper_bound(p,n)<< endl;
	}
	
	return 0;
}
