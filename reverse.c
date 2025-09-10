#include <stdio.h>
#include <stdlib.h>

void ReverseTheArray(int* array, int length){
    int temp=0;
    for(int i=0; i<length/2; i++){
        temp=array[i];
        array[i]=array[length-i-1];
        array[length-i-1]=temp;
    }
}

int main(){

    int* array;
    int length;
    printf("Enter the length of the array: ");
    scanf("%d", &length);

    array=(int*)malloc(length*sizeof(int));

    printf("Enter the elements of the array: ");
    for(int i=0; i<length; i++){
        scanf("%d", &array[i]);
    }

    ReverseTheArray(array, length);

    for (int i = 0; i <length; i++){
        printf(" %d", array[i]);
    }
    
    free(array);

    return 0;
}
