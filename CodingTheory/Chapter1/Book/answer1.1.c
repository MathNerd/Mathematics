#include <stdio.h>

int main(void)
{
    int code[] = {0,0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,0,1,1,0,0,1,0,0,1,1,0,0,1,0,0,1,1,0,0,1,0,1,1,1,1,0,0,0,1,
                  0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,1,0,0,1,1,0};
    int length = sizeof(code) / sizeof(code[0]);
    
    printf("length = %d\n", length);
    
    printf("code = ");
    for (int i = 0; i < length; i++)
        printf("%d", code[i]);
    printf("\n");
    
    int rows_number = 11;
    int cols_= 7;
    
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (code[row * cols + col])
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
