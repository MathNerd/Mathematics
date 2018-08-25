#include <stdio.h>

int main(void)
{
    int code[] = {0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,0,1,1,0,0,1,0,0,1,1,0,0,1,0,0,1,1,0,0,1,0,1,1,1,1,0,0,0,1,
                  0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,1,0,0,1,1,0};
    int length = sizeof(code) / sizeof(code[0]); // length = 77
    
    printf("length = %d\n", length);
    
    printf("code = ");
    for (int i = 0; i < length; i++)
        printf("%d", code[i]);
    printf("\n\n");
    
    int rows_number = 11;
    int columns_number = 7;
    
    for (int row = 0; row < rows_number; row++)
    {
        for (int column = 0; column < columns_number; column++)
        {
            if (code[row * columns_number + column])
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    
    return 0;
}
