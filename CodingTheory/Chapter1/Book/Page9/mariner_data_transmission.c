#include <stdio.h>
#include <math.h>

int main()
{
    int width = 200; // Width of the picture.
    int height = 200; // Height of the picture.
    int bits = 6; // Number of bits per picture-element/pixel.
    double transmit_rate = 8.0+1.0/3.0; // Number of bits that can be transmitted in one second.
    
    int total_pixels = width * height; // Total number of picture-elements/pixels in the whole picture.
    int total_bits = total_pixels * bits; // Total number of bits in the whole picture.
    double total_time_s = total_bits / transmit_rate; // Total time reqiured to transmit the whole picture in seconds.
    double total_time_h = total_time_s / 3600; // Total time required to transmit the whole picture in hours.
    
    printf("width = %d\n", width);
    printf("height = %d\n", height);
    printf("bits = %d\n", bits);
    printf("transmit_rate = %f\n", transmit_rate);
    printf("total_pixels = %d\n", total_pixels);
    printf("total_bits = %d\n", total_bits);
    printf("total_time_s = %f\n", total_time_s);
    printf("total_time_h = %f\n", total_time_h);
    
    return 0;
}
