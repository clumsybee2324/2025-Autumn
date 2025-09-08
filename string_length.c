#include <stdio.h>

int StringLength(char* name){
    int i=0;
    while (name[i] !='\0'){
        i++;
    }
    return i;
}

int main(){
    char* name;
    printf("Enter your name: ");
    scanf("%s", name);
    int length=StringLength(name);
    printf("The length of the name is: %d\n", length);
    return 0;
}
