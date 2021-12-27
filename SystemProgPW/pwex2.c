#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct month{
    char name[10];
    int days;
};

int main(){

    int flag = 0;
    struct month months[12]={
        "January",31,
        "February",28,
        "March",31,
        "April",30,
        "May",31,
        "June",30,
        "July",31,
        "August",31,
        "September",30,
        "October",31,
        "November",30,
        "December",31
    };

    char month[10];

    printf("Month:");
    scanf("%s",month);

    for(int i = 0 ; i < 12 ; i++){
        if(strcmp(month,months[i].name)==0){
            flag = 1;
            printf("Number of month: %d\n",i+1);
            printf("Number of days in this month: %d\n",months[i].days);
        }
    }

    if(flag==0){
        printf("No such month exits!");
    }
    
    


    return 0;
}