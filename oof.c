#include<stdio.h>

int main()
{
    {
        int i;
        int x = 10, y = 20;
        {
            for(i = 1; i<=1; i++)
            {
            printf("x = %d , y = %d\n", x,y);
            {
                int y = 40;
                
                x++;
                y++;
                
                printf("x = %d, y = %d\n", x,y);
            }
            printf("x = %d, y = %d\n",x,y);
            }
            
        }
         printf("x = %d, y = %d\n",x,y);
    }
    return 0;
}
