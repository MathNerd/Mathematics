#include<iostream>

using namespace std;

template<size_t Q, size_t N>
class CodeWord
{
    public:
    
        static const size_t n = N;
        static const size_t q = Q;
    
    private:
    
        int code[n];
    
    public:
    
        CodeWord(int arr[])
        {
            for (size_t idx = 0; idx < n; idx++)
            {
                if (0 <= arr[idx] && arr[idx] <= q-1)
                {
                    code[idx] = arr[idx];
                }
                else
                {
                    cout << "FATAL ERROR\n";
                }
            }
        }
        
        ~CodeWord(void){};
        
        int GetSymbolAt(size_t idx)
        {
            if (idx < n)
                return code[idx];
            else
            {
                cout << "FATAL ERROR\n";
                return 0;
            }
        }
        
        void Print(bool newline)
        {
            for (size_t idx = 0; idx < n; idx++)
                cout << code[idx];
            
            if(newline)
                cout << endl;
        }
}

template<size_t M, size_t Q, size_t N>
class Code
{
    public:
    
        const static size_t n = N;
        const static size_t q = Q;
        const static size_t m = M;
        
    private:
    
        CodeWord<Q,N> codeword[m];
        
    public:
    
        Code(CodeWord codewords[]]
        {
            for (size_t idx = 0; idx < m; i++)
            {
                codeword[idx] = codewords[idx];
            }
        }
        
        ~Code(void):
        
        void Print(bool newline)
        {
            cout << "{";
            for (size_t idx = 0; idx < m-1; idx++)
            {
                codeword[idx].Print(false);
                cout << ", ";
            }
            codeword[idx].Print(false);
            cout << "}";
    
            if (newline)
                cout << endl;
        }
}


template <size_t Q, size_t N>
int hamming_distance(CodeWord<Q,N> x, CodeWord<Q,N> y)
{
    int count = 0;
    
    for (size_t idx = 0; idx < N; idx++)
    {
        if (x.GetSymbolAt(idx) != y.GetSymbolAt(idx))
            count++;
    }
    
    return count;
}

int main() {
	
	
	Code<4,2,2> 
	CodeWord<2,

	cout<<"Sum of x+y = " << z;
}
