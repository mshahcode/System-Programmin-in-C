#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


int main(){
    FILE* f = fopen("foo.txt","r");
    pid_t p = fork();
    int status;
    char c;


    if(p==-1){
        exit(-1);
    }

    if(p==0){ // child
        if(f){
            while((c = getc(f)) != EOF){
                write(1,&c,1);
            }
        }
        exit(getpid()%10);
    }else{
        if(f){
            while((c = getc(f)) != EOF){
                write(1,&c,1);
            }
        }
        wait(&status);
        if(WIFEXITED(status)){
            printf("Parent:, return values %d\n",WEXITSTATUS(status));
        }else{
            printf("Something wrong happened!\n");
        }
    }

    return 0;
}
