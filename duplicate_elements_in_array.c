#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n, i, j, c;
    printf("Enter the size of array: ");
    scanf("%d",&n);
    int a[n];
    for(i = 0 ; i<n ; i++)
    {
        printf("Enter the element %d: ",i+1);
        scanf("%d",&a[i]);
    }
    printf("This is the new array: \n");
    for(i = 0 ; i<n ; i++)
    {
        printf("%d\n",a[i]);
    }
    i = 0;
    j = 0;
    do
    {
        j = i+1;
        do
        {
            if( a[i] == a[j] )
            {
                for( c=j ; c<n ; c++ )
                {
                    a[c] = a[c+1];
                }
                n=n-1;
            }
            else
                j = j+1;
        }while(j<n);
        i=i+1;
    }while(i<n-1);
    printf("This is the updated array: \n");
    for(i = 0 ; i<n ; i++)
    {
        printf("%d\n",a[i]);
    }
    return 0;
}









