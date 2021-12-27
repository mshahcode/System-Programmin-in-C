#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>

int main(int argc, char **argv){
    
    char* d;
    int status;

    if(argc!=2){
        printf("Please correct the input!\n");
    }


    pid_t pid = fork();

    if(pid < 0){
        exit(-1);
    }


    if(pid==0){ // child
        printf("In child right now\n");

        int fd=open("/dev/null",O_WRONLY | O_TRUNC ,0666);
		dup2(fd,1);
        close(fd);
        execlp("/bin/ls","ls","-R",argv[1],NULL);
        printf("Execelp was not successfull :(\n");
        exit(1);
    }else{
        wait(&status); // waiting for child to be executed
        		
        if(WIFEXITED(status)){
            printf("exitting\n");
        } 
    }


    return 0;
}