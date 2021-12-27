#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){

    char input[255];
    char input2[255];
    printf("Write something:");
    fgets(input,255,stdin);
    printf("Your string: %s",input);
    strcpy(input2,input);
    printf("Copied string: ");
    puts(input2);
    printf("Length: %ld\n",strlen(input2)-1);


    return 0;
}