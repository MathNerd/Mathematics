#include <iostream>
using namespace std;

template<class T>
T Max(T x, T y)
{
    return (x < y ? y : x);
}

template<class T>
T Max(T a[], size_t n)
{
    if (n == 1)
        return a[0];
    else /* n > 1 */
        return Max(Max(a, n - 1), a[n - 1]);
}

int main() {
	double a[] = {1,4,2,6,3,9,6,2,5,7,1,3};
	const size_t n = sizeof(a)/sizeof(a[0]);
	cout << "Max(a," << n << ") = " << Max(a,n) << endl;
	
	return 0;
}
