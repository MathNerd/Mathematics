// "Theoretically" implements Definition-B16 ('Open Cover') in Measure-Theory, Volume-1, Page 47.

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#define USE_TIME_MEASURING 1
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
    
    static open_family create(void)
    {
        open_family OP;
        return OP;
    }
    
    void add(open_interval I)
    {
        _oil.push_back(I);
    }
    
    bool is_in(real x)
    {
        for (size_t idx = 0; idx < _oil.size(); idx++)
            if (_oil[idx].is_in(x))
                return true;
        return false;
    }
    
    bool is_open_cover(closed_interval C)
    {
        // implements a theoretical solution: 'steps' through all points in C:
        const real delta = 0.0001;
        for (real x = C.a; x < C.b; x += delta)
            if (!this->is_in(x))
                return false;
        return this->is_in(C.b);
    }
    
    std::string to_string(void)
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
        s += "}";
        return s;
    }
};

int main() {
    closed_interval c1 = closed_interval::create(1.4,1.6);
    open_interval o1 = open_interval::create(-1,1.5);
	open_interval o2 = open_interval::create(1.4,2);
	open_interval o3 = open_interval::create(3,4);
	open_family of1 = open_family::create();
	of1.add(o1);
	of1.add(o2);
	of1.add(o3);
	real x;
	

	std::cout << c1.to_string() << std::endl;
	std::cout << of1.to_string() << std::endl;
	
	bool result;
	
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
