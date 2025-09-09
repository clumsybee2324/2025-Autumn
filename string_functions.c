#include <stdio.h>
#include <string.h>

int StringLength(char* name){
    int i=0;
    while (name[i] !='\0'){
        i++;
    }
    return i;
}

char* StringCopy(char* dest, char* src){
    dest=src;
    return dest;
}

char* StringConcat(char* dest, char* src){

    char* concat;
    int length1=StringLength(src);
    int length2=StringLength(dest);
    int totallength=length1+length2;

    for(int i=0; i<totallength; i++){
        if(i<length1){
            concat[i]=src[i];
        }
        else{
            concat[i]=dest[i-length1];
        }
    }
    return concat;
}

int main(){
    char* name1="ayda";
    char* name2="arda";

    int length=StringLength(name1);
    printf("The length of the name is: %d\n", length);   //string length function  we've written before
    
    char* copy= StringCopy(name2, name1);         
    printf("The name of the boy is:%s\n", copy);         //string copy function we've just written

    char name3[]="ayda";
    char name4[60]="arda";

    strcpy(name4, name3);             
    printf("The name of the boy is:%s\n", name4);        //default string copy function on string.h

    char* concat=StringConcat(name2, name1);
    printf("The concat is:%s\n", concat);               //string concat function we've just written

    return 0;
}
