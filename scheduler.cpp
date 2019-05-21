#include <iostream>
#include <vector>
#include <string>

struct delays
{
    int d1;
    int d2;
    int d3;
    
    std::string to_string(void)
    {
        std::string str = "[";
        str += std::to_string(d1);
        str += ",";
        str += std::to_string(d2);
        str += ",";
        str += std::to_string(d3);
        str += "]";
        return str;
    }
};

std::vector<delays> delays_list;

std::string to_string(std::vector<delays> delays_list)
{
    std::string str = "{";
    if (delays_list.size() > 0)
    {
        size_t idx;
        for (idx = 0; idx < delays_list.size() - 1; idx++)
        {
            str += delays_list[idx].to_string();
            str += ",";
        }
        str += delays_list[idx].to_string();
    }
    str += "}";
    return str;
}

int main() {
	delays_list.push_back({1, 4, 7});
	delays_list.push_back({5, 2, 8});
    delays_list.push_back({4, 9, 6});

    std::cout << to_string(delays_list) << std::endl;
}
