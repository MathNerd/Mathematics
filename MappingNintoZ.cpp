// program to map N (the set of natural numbers) into Z (the set of whole numbers):

#include <cstdio>
#define modulo(N,P) ((N)%(P))

int h(int n)
{
    int r;
    if (modulo(n,2)==1)
        r = (1-n)/2;
    else
        r = n/2;
    return r;
}

int main(void)
{
    for(int n=1; n<=30; n++)
        printf("\t%d\n",h(n));
}
