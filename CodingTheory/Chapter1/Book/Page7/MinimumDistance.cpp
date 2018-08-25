#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;

//---------------------- CodeWord ----------------------

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

//---------------------- Hamming Distance ----------------------

template <size_t Q, size_t N>
int HammingDistance(CodeWord<Q,N> x, CodeWord<Q,N> y)
{
    int count = 0;
    
    for (size_t idx = 0; idx < N; idx++)
    {
        if (x.GetSymbolAt(idx) != y.GetSymbolAt(idx))
            count++;
    }
    
    return count;
}

//---------------------- Code ----------------------

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
		    int distance = HammingDistance(codeword[i], codeword[j]);
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

//---------------------- Random ----------------------

void RandomInit(void)
{
    srand(time(NULL));
}

double Random(void)
{
    return rand()/double(RAND_MAX);
}

//---------------------- Combinatorics ----------------------

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

//---------------------- Probability ----------------------

// Probability that 'i' symbols are correct.
double BinomialDistributionMassFunction(double p, int n, int i)
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
    
    return int(nCk(n,i)) * pow(p,n-i) * pow(1-p,i);
}

template<size_t M, size_t Q, size_t N>
void PrintValidityProbabilities(Code<M,Q,N> code, double p)
{
    double sum = 0.0;
    for (int nValid = N; nValid >= 0; nValid--)
    {
        double probability = BinomialDistributionMassFunction(p, N, nValid);
        cout << "P(VALID = " << nValid << ") = " << probability << endl;
        sum += probability;
    }
    cout << "P(VALID = 0,...," << N << ") = " << sum << endl;
}

//---------------------- Simulation ----------------------

template<size_t Q, size_t N>
CodeWord<Q,N> Mutate(CodeWord<Q,N> original_word, double p)
{	
    int mutated_word_arr[N];
    for(int idx = 0; idx < N; idx++)
    {
        int symbol = original_word.GetSymbolAt(idx);
	
	if (Random() <= p)
	{
	    // NEEDS RENOVATION FOR CASE Q>2!!!
	    symbol = 1-symbol;
	}
	    
	mutated_word_arr[idx] = symbol;
    }
    CodeWord<Q,N> mutated_word(mutated_word_arr);
	
    return mutated_word;
}

template<size_t M, size_t Q, size_t N>
void SimulateSend(Code<M,Q,N> code, int sent_codeword_index, double p, int times)
{
    CodeWord<Q,N> sent_codeword = code.GetCodeWordAt(sent_codeword_index);
    int error_statistics[N+1];

    cout << "BEGIN SIMULATION WITH {sent_codeword = ";
    sent_codeword.Print(false);
    cout << ", p = " << p << ", times = " << times << "}" << endl;
	
    for(int time = 1; time <= times; time++)
    { 
        CodeWord<Q,N> received_vector = Mutate(sent_codeword, p);
	
        int distance = HammingDistance(sent_codeword, received_vector);
	
        error_statistics[distance]++;
	
        cout << "TIME = " << time
	     << ", RECEIVED_VECTOR = ";
        received_vector.Print(false);
	cout << ", DISTANCE = " << distance << endl;
    }
	
    cout << "END SIMULATION" << endl;
}

//---------------------- Creating Codes for Example ----------------------

Code<4,2,2> CreateC1(void)
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

Code<4,2,3> CreateC2(void)
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

Code<4,2,5> CreateC3(void)
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

//---------------------- Main ----------------------

int main() {
	
	Code<4,2,2> C1 = CreateC1();
	Code<4,2,3> C2 = CreateC2();
	Code<4,2,5> C3 = CreateC3();

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
	
        SimulateSend(C3, 1, p, 100);
	
	return 0;
}
