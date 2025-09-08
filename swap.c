#include <stdio.h>

void SwapNumbers(int* num1, int* num2){
    int temp;
    temp=*num1;
    *num1=*num2;
    *num2=temp;

    printf("After the swap the first number is:%d\n", *num1);
    printf("After the swap the second number is:%d\n", *num2);

}

int main(){
    int a=6;
    int b=5;
    int* pa=&a;
    int* pb=&b;
    printf("Before the swap the first number is:%d\n", a);
    printf("Before the swap the second number is:%d\n",b);
    SwapNumbers(pa, pb);
    return 0;
}
