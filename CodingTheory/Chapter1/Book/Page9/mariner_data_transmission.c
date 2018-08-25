#include <stdio.h>
#include <math.h>

int main()
{
    int width = 200; // Width of the picture.
    int height = 200; // Height of the picture.
    int bits = 6; // Number of bits per picture-element/pixel.
    double transmit_rate = 8.0+1.0/3.0; // Number of bits that can be transmitted in one second.
    
    int total_pixels = width * height; // Total number of picture-elements/pixels.
    int total_bits = total_pixels * bits; // Total number of bits.
    double total_time = total_bits / transmit_rate; // Total time reqiured to transmit the picture in seconds.
    double total_time_h = total_time / 3600; // Total time required to transmit the picture in hours,
    
    printf("%f\n", result);
    return 0;
}
