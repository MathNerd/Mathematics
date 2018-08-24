#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>

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
        
	int MinimalDistance(void)
	{
	    if (m < 2)
	    {
	        cout << "FATAL ERROR\n";
		return 0;
	    }
		
	    int minimal_distance = 999999999;
	    for (int i = 0; i <= m-2; i++)
	    {
		for (int j = i+1; j <= m-1; j++)
		{
		    int distance = hamming_distance(codeword[i], codeword[j]);
		    if (distance < minimal_distance)
		         minimal_distance = distance;
		}
	    }
	    return minimal_distance;
	}
	
	CodeWord<Q,N> GetCodeWordAt(size_t idx)
	{
	    if(idx < m)
	        return codeword[idx];
	    else
	    {
	        cout << "FATAL ERROR\n";
		return CodeWord<Q,N>();
	    }
	}
	
        void Print(bool newline)
        {
            cout << "{";
            size_t idx;
            for (idx = 0; idx < m-1; idx++)
            {
                codeword[idx].Print(false);
                cout << ",";
            }
            codeword[idx].Print(false);
            cout << "}";
    
            if (newline)
                cout << endl;
        }
};

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

void RandomInit(void)
{
    srand(time(NULL));
}

double Random(void)
{
    return rand()/double(RAND_MAX);
}

unsigned nCk(unsigned n, unsigned k )
{
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( int i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

double probability(double p, int n, int i)
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
    
    return int(nCk(n,i)) * pow(p,i) * pow(1-p,n-i);
}

template<size_t M, size_t Q, size_t N>
void PrintValidityProbabilities(Code<M,Q,N> code, double p)
{
    double sum = 0.0;
    for (int nValid = N; nValid >= 0; nValid--)
    {
        double prob = probability(p, N, nValid);
        cout << "P(VALID = " << nValid << ") = " << prob << endl;
        sum += prob;
    }
    cout << "P(VALID = 0,...," << N << ") = " << sum << endl;
}

template<size_t M, size_t Q, size_t N>
void simulate_send(Code<M,Q,N> code, int codeword_idx, double p)
{
    // Generate CodeWord with noise:
    int codeword_with_noise_arr[N];
    for(int idx = 0; idx < N; idx++)
    {
        int symbol = code.GetCodeWordAt(codeword_idx).GetSymbolAt(idx);
	
	if (Random() <= p)
	{
		// NEEDS RENOVATION FOR CASE Q>2!!!
	    symbol = 1-symbol;
	}
	    
	codeword_with_noise_arr[idx] = symbol;
    }
    CodeWord<Q,N> codeword_with_noise(codeword_with_noise_arr);
	
	cout << "DIST = " << hamming_distance(code.GetCodeWordAt(codeword_idx), codeword_with_noise) << " MUTATE = ";
    codeword_with_noise.Print(true);
}

int main() {
	
	Code<4,2,2> C1 = createC1();
	Code<4,2,3> C2 = createC2();
	Code<4,2,5> C3 = createC3();

	cout << "d(";
	C1.Print(false);
	cout << ") = " << C1.MinimalDistance() << endl;
	
	cout << "d(";
	C2.Print(false);
	cout << ") = " << C2.MinimalDistance() << endl;
	
	cout << "d(";
	C3.Print(false);
	cout << ") = " << C3.MinimalDistance() << endl;
	
	RandomInit();
	
	double p = 0.4;
	
	PrintValidityProbabilities(C3,p);
	
//	for (int nValid = N; nValid >= 0; nValid—)
//	    cout << "PROBABILITY OF " << nValid << " VALID PLACES = " << probabilty(
	for (int i = 1; i<= 100; i++)
    	simulate_send(C3, 1, p);
	
	return 0;
}
