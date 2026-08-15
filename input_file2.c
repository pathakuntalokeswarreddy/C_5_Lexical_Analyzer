#include "header.h"
#include<stdio.h>
int sum(int num1,int num2);
//lokeswar reddy
int main()
{
    #ifdef 1
    int num1=0, num2=2+6; /*addition*/
    #endif
    /*I am
     Loki*/
    char name[5]="loki";
    if(num1==0)
        printf("Result: %d",num2);
    else
    {
        printf("Result: %d",sum(num1,num2));
    }
    return 0;
}
int sum(int num1,int num2)
{
    num1<<5;
    return num1+num2;
}