#include <stdio.h>
#include <stdlib.h>

int main(){
    int n=0;
    int* p;

    printf("Enter the size of the array: ");
    scanf("%d",&n);

    p=(int*) malloc(n*sizeof(int));

    printf("Enter the numbers in the array: ");
    for(int i=0; i<n; i++){
        scanf("%d", &p[i]);
    }

    int sum=0;
    for(int i=0; i<n; i++){
        sum +=p[i];
    }
    printf("The sum of the numbers is:%d\n", sum);

    float average=0;
    average= sum/n;
    printf("The average of the numbers is:%.f\n", average);

    free(p);

    return 0;
}
