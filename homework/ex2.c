#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int pipet[2];
    pipe(pipet);

    
    int pid = fork();

    if(pid == -1){
        printf("Couldn't fork!\n");
        exit(1);
    }

    if(pid == 0){
        close(pipet[0]);
        dup2(pipet[1],1);
        close(pipet[1]);
        execlp("ls","ls","-l",NULL);
        printf("Error!\n");
        exit(2);
    }else{
        close(pipet[1]);
        dup2(pipet[0],0);
        close(pipet[0]);
        execlp("sort","sort",NULL);
        printf("Error!\n");
        exit(3);  
    }

    return 0;
}
