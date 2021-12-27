#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <sys/stat.h> 
#include <unistd.h>   
#include <fcntl.h>    
#include <string.h>


int main(int argc, char **argv)
{

    // creating two tubes
    int pipe1[2];
    int pipe2[2];
    // creating two forks
    int pid1;
    int pid2;

    // if number of arguments doesn't equal 2, exit
    if (argc != 2)
    {
        printf("Wrong input, please write correct!\n");
        exit(1);
    }

    
    // piping
    pipe(pipe1);

    // forking
    pid1 = fork();

    if(pid1 == -1){
        printf("Failed to fork\n");
        exit(2);
    }

    if (pid1 == 0)
    {
        //child part
        close(pipe1[0]);
        dup2(pipe1[1], 1);
        execlp("ls", "ls", "-all", NULL);
        fprintf(stderr, "Error in exec\n");
        exit(3);
    }
    else
    {
        // parent part
        close(pipe1[1]);
        dup2(pipe1[0], 0);

        // pipe second
        pipe(pipe2);

        // fork second time
        pid2 = fork();

        if(pid2 == -1){
            printf("Failed to fork!\n");
            exit(4);
        }

        if (pid2 == 0)
        {
            // second child
            close(pipe2[0]);
            dup2(pipe2[1], 1);
            execlp("grep", "grep", argv[1], NULL);
            fprintf(stderr, "Error in exec\n");
            exit(5);
        }
        else
        {
            close(pipe2[1]);
            dup2(pipe2[0], 0);
            execlp("wc", "wc", "-l", NULL);
            fprintf(stderr, "Error in exec\n");
            exit(6);
        }
    }

    return 0;
}