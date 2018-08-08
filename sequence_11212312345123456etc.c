
#include <iostream>

using namespace std;

int a(int n)
{
    int reduce = 1; // Holds the value which will be subtracted from the variable 'n' on every iteration of the following loop.

    // In each iteration of the loop we subtract the current value of 'reduce' from the current value of 'n',
    // Until 'n' becomes negative, After which the loop ends, 
    // And we then, "undo" the last subtraction 'n = n - reduce' that was carried out in the last iteration
    // inorder to get the correct value of 'n' by adding 'reduce-1' to the value of 'n' 
    // that we got just after getting out of the loop.
    // Note: 
    // We add 'reduce-1' because the value of 'reduce' was incremented by 1 on the last iteration of the loop,
    // And thus, Inorder to get the actual value of 'reduce' which was subtracted from 'n' in the last iteration, 
    // We need to use 'reduce-1', And NOT 'reduce'.
    // 'n', 
    while(n>0)
    {
        n = n - reduce;
        reduce = reduce + 1;
    }
    n = n + reduce - 1;

    return n;
}

int main() {
    int max = 22;
	for(int n=1; n<= max; n++)
        cout<<"a("<<n<<") = " << a(n)<<endl;
    return 0;
}
