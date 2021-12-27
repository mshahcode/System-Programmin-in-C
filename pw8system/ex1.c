#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char **argv){
    
    char* d;
    int status;

    if(argc!=2){
        printf("Please correct the input!\n");
    }

    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    printf("seconds : %ld\nmicro seconds : %ld\n",
    current_time.tv_sec, current_time.tv_usec);
    int s = current_time.tv_usec;

    pid_t pid = fork();

    if(pid < 0){
        exit(-1);
    }

    if(pid==0){ // child
        printf("In child right now\n");
        execlp("ls","ls","-l",argv[1],NULL);
        printf("Execelp was not successfull :(\n");
        exit(1);
    }else{
        wait(&status); // waiting for child to be executed
        gettimeofday(&current_time, NULL);
        printf("seconds : %ld\nmicro seconds : %ld\n",
        current_time.tv_sec, current_time.tv_usec);
        printf("\n%ld millisecond was taken to execute\n",current_time.tv_usec-s);
        if(WIFEXITED(status)){
            printf("parent : exit code is %d\n", WEXITSTATUS(status));
        } 

    }


    return 0;
}