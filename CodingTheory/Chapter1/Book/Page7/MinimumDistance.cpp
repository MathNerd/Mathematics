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

Code<4,2,2> createC1(void)
{
    int cw1_arr[2] = {0,0};
    int cw2_arr[2] = {0,1};
    int cw3_arr[2] = {1,0};
    int cw4_arr[2] = {1,1};
    
    CodeWord<2,2> cw1(cw1_arr);
    CodeWord<2,2> cw2(cw2_arr);
    CodeWord<2,2> cw3(cw3_arr);
    CodeWord<2,2> cw4(cw4_arr);
    
    CodeWord<2,2> cw_arr[4] = { cw1, cw2, cw3, cw4 };
    
    Code<4,2,2> c(cw_arr);
    
    return c;
}

Code<4,2,3> createC2(void)
{
    
}

Code<4,2,5> reateC3(void)
{
    
}

int main() {
	
	Code<4,2,2> C1 = createC1();
	Code<4,2,3> C2 = createC2();
	Code<4,2,5> C3 = createC3();

	C1.Print(true);
	C2.Print(true);
	C3.Print(true);
}
