#include<iostream>
#include<iomanip>

int error_detection(int d)
{
    return d-1;
}

int error_correction(int d)
{
    return (d-1)/2;
}

int main(void)
{
    std::cout << "| " << std::left << std::setw(3) << "d" 
              << " | " << std::left << std::setw(15) << "error_detection" 
              << " | " << std::left << std::setw(16) << "error_correction" << " |" << std::endl;
    for (int d = 1; d <= 20; d++)
        std::cout << "| " << std::left << std::setw(3) << d 
                  << " | " << std::left << std::setw(15) << error_detection(d) 
                  << " | " << std::left << std::setw(16) << error_correction(d) << " |" << std::endl;
    
    return 0;
}
