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
    
        CodeWord(void)
        {
            // Never use it
            // Just make the compiler SHUT THE FUCK UP!
        }
        
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
        
        ~CodeWord(void){}
        
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
};

template<size_t M, size_t Q, size_t N>
class Code
{
    public:
    
      //  const static size_t n = N;
    //    const static size_t q = Q;
        const static size_t m = M;
        
    private:
    
        CodeWord<Q,N> codeword[m];
        
    public:
    
        Code(CodeWord<Q,N> codewords[])
        {
            for (size_t idx = 0; idx < m; idx++)
            {
		// ADD COPY/DUPLICATE CHECK !!!
                codeword[idx] = codewords[idx];
            }
        }
        
        ~Code(void){}
        
        void Print(bool newline)
        {
            cout << "{";
            size_t idx;
            for (idx = 0; idx < m-1; idx++)
            {
                codeword[idx].Print(false);
                cout << ", ";
            }
            codeword[idx].Print(false);
            cout << "}";
    
            if (newline)
                cout << endl;
        }
};

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
    int cw1_arr[3] = {0,0,0};
    int cw2_arr[3] = {0,1,1};
    int cw3_arr[3] = {1,0,1};
    int cw4_arr[3] = {1,1,0};
    
    CodeWord<2,3> cw1(cw1_arr);
    CodeWord<2,3> cw2(cw2_arr);
    CodeWord<2,3> cw3(cw3_arr);
    CodeWord<2,3> cw4(cw4_arr);
    
    CodeWord<2,3> cw_arr[4] = { cw1, cw2, cw3, cw4 };
    
    Code<4,2,3> c(cw_arr);
    
    return c;
}

Code<4,2,5> createC3(void)
{
    int cw1_arr[5] = {0,0,0,0,0};
    int cw2_arr[5] = {0,1,1,0,1};
    int cw3_arr[5] = {1,0,1,1,0};
    int cw4_arr[5] = {1,1,0,1,1};
    
    CodeWord<2,5> cw1(cw1_arr);
    CodeWord<2,5> cw2(cw2_arr);
    CodeWord<2,5> cw3(cw3_arr);
    CodeWord<2,5> cw4(cw4_arr);
    
    CodeWord<2,5> cw_arr[4] = { cw1, cw2, cw3, cw4 };
    
    Code<4,2,5> c(cw_arr);
    
    return c;
}


int main() {
	
	Code<4,2,2> C1 = createC1();
	Code<4,2,3> C2 = createC2();
	Code<4,2,5> C3 = createC3();

	C1.Print(true);
	C2.Print(true);
	C3.Print(true);
	
	return 0;
}
