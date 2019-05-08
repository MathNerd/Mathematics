// "Theoretically" implements Definition-B16 ('Open Cover') in Measure-Theory, Volume-1, Page 47.

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <functional>

#define USE_TIME_MEASURING 0
#if USE_TIME_MEASURING == 1
    #include <chrono>
    
    #define MEASURE_TIME_START(ID) { const char* ___measure___id___ = ID; \
                                           auto ___measure___start___ = std::chrono::high_resolution_clock::now();
    
    #define MEASURE_TIME_STOP() auto ___measure___stop___ = std::chrono::high_resolution_clock::now();  \
                        auto ___measure___duration___ = std::chrono::duration_cast<std::chrono::microseconds>(___measure___stop___ - ___measure___start___); \
                        std::cout << "Time taken by " << ___measure___id___ << " is: "  \
                             << ___measure___duration___.count() << " microseconds" << std::endl; }
#endif

typedef double real;

struct closed_interval
{
    real a;
    real b;
    
    static closed_interval create(real a, real b)
    {
        assert(a <= b);
        closed_interval I;
        I.a = a;
        I.b = b;
        return I;
    }
    
    bool is_in(real x)
    {
        return a <= x && x <= b;
    }
    
    std::string to_string(void)
    {
        std::string s = "[";
        s += std::to_string(a);
        s += ",";
        s += std::to_string(b);
        s += "]";
        return s;
    }
};

struct open_interval
{
    real a;
    real b;
    
    static open_interval create(real a, real b) 
    {
        assert(a < b);
        open_interval I;
        I.a = a;
        I.b = b;
        return I;
    }
    
    bool is_in(real x)
    {
        return a < x && x < b;
    }
    
    std::string to_string(void)
    {
        std::string s = "(";
        s += std::to_string(a);
        s += ",";
        s += std::to_string(b);
        s += ")";
        return s;
    }
};

struct open_family
{
    std::vector<open_interval> _oil; // acronym for: open interval list.
    std::vector<std::function<open_interval(int)>> _oisl; // acronym for: open interval sequence list.
    
    static open_family create(void)
    {
        open_family OP;
        return OP;
    }
    
    void add(open_interval I)
    {
        _oil.push_back(I);
    }
    
    void add(std::function<open_interval(int)> seq)
    {
        _oisl.push_back(seq);
    }
    
    bool is_in(real x, int maximal_sequence_search_depth = 100)
    {
        for (size_t idx = 0; idx < _oil.size(); idx++)
            if (_oil[idx].is_in(x))
                return true;
        if (_oisl.size() > 0)
        {
            for (int n = 1; n <= maximal_sequence_search_depth; n++)
                for (size_t idx = 0; idx < _oisl.size(); idx++)
                    if (_oisl[idx](n).is_in(x))
                        return true;
        }
        return false;
    }
    
    bool is_open_cover(closed_interval C, int maximal_sequence_search_depth = 100)
    {
        // implements a theoretical solution: 'steps' through all points in C:
        const real delta = 0.0001;
        for (real x = C.a; x < C.b; x += delta)
            if (!this->is_in(x, maximal_sequence_search_depth))
                return false;
        return this->is_in(C.b, maximal_sequence_search_depth);
    }
    
    std::string to_string(int maximal_sequence_depth = 3)
    {
        std::string s = "{";
        if (_oil.size() > 0)
        {
            size_t idx;
            for (idx = 0; idx < _oil.size() - 1; idx++)
            {
                s += _oil[idx].to_string();
                s += ",";
            }
            s += _oil[idx].to_string();
        }
        if (_oisl.size() > 0)
        {
            size_t idx;
            for (idx = 0; idx < _oisl.size() - 1; idx++)
            {
                for (int n = 1; n <= maximal_sequence_depth; n++)
                {
                    s += _oisl[idx](n).to_string();
                    s += ",";
                }
                s += "...";
                s += ",";
            }
            for (int n = 1; n <= maximal_sequence_depth; n++)
            {
                s += _oisl[idx](n).to_string();
                s += ",";
            }
            s += "...";
        }
        s += "}";
        return s;
    }
};

int main() {
    closed_interval c1  = closed_interval:: create(0.01,0.8);
    open_interval   o1  = open_interval::   create(-1,1.5);
	open_interval   o2  = open_interval::   create(1.4,2);
	open_interval   o3  = open_interval::   create(3,4);
	open_family     of1 = open_family::     create();
	//of1.add(o1);
	of1.add(o2);
	//of1.add(o3);
	//of1.add([&](int n){ open_interval I_n = open_interval::create(-n, n); return I_n; });
	//of1.add([&](int n){ open_interval I_n = open_interval::create(-1.0/n, 1.0/n); return I_n; });
	of1.add([&](int n){ open_interval I_n = open_interval::create(0, 1-1.0/(n+1)); return I_n; });
	//real x;
	

	std::cout << c1.to_string() << std::endl;
	std::cout << of1.to_string() << std::endl;
	std::cout << of1.is_in(0.9,100) << std::endl;
	
	
	bool result = false;
	
	#if USE_TIME_MEASURING == 1
    	MEASURE_TIME_START("BALH");
    #endif
    
	result = of1.is_open_cover(c1);
	
	#if USE_TIME_MEASURING == 1
	    MEASURE_TIME_STOP();
	#endif
	
	std::cout << result << std::endl;
	
	
	/*const real EXIT_CODE = 12345;
	while(x != EXIT_CODE)
	{
	    std::cin >> x;
	    std::cout << of1.is_in(x) << std::endl;
	}*/
}
