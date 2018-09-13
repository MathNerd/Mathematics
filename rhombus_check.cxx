// WARNING: NOT WORKING CODE!!!

#include <iostream>
#include <cmath>

using namespace std;

struct rhombus
{
    double a;
    double b;
};

struct point
{
    double x;
    double y;
};

#define square(x) ((x)*(x))
double distance(point a, point b)
{
    return sqrt(square(b.x-a.x)+square(b.y-a.y));
}

#define MAX_POINTS 4
bool is_rhombus(point points[MAX_POINTS])
{
    double distances[6];
    
    int k = 0;
    for (int i = 0; i < MAX_POINTS - 1; i++)
    {
        for (int j = i+1; j < MAX_POINTS; j++)
        {
            distances[k++] = distance(points[i], points[j]);
        }
    } 
    
    for (k = 0; k < 6; k++)
        cout << distances[k] << endl;
    
    return false;
}

int main() {
	
	point points[4] = {{-2,-1},{-7,9},{4,7},{9,-3}};
	
	is_rhombus(points);
	
	cout<<"rhombus: " << endl;
	
	return 0;
}
