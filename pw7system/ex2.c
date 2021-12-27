#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

/*
int main(){
    pid_t p = fork();
    int status;

    if(p==-1){
        exit(-1);
    }

    if(p==0){ // child
        printf("Child: Childs pid: %d\n",getpid());
        printf("Child: Parents pid in childs part: %d\n",getppid());
        exit(getpid()%10);
    }else{
        // sleep(1);
        printf("Parent, child id: %d\n",p);
        wait(&status);
        if(WIFEXITED(SIGKILL)){
            printf("Parent:, return values %d\n",WEXITSTATUS(status));
        }else{
            printf("Something wrong happened!\n");
        }
    }

    return 0;
}*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


int main(){
    int status;

    int n;
    scanf("%d",&n);


    for(int i = 0 ; i < n ; i++){
        pid_t p = fork();
        if(p==-1){
            exit(-1);
        }
        if(p==0){ // child
            printf("Child: Childs pid: %d\n",getpid());
            printf("Child: Parents pid in childs part: %d\n",getppid());
            exit(getpid()%10);
        }else{
            // sleep(1);
            printf("Parent, child id: %d\n",p);
           
        }


    }

    for(int i = 0 ; i < n ; i++){

            wait(&status);
            if(WIFEXITED(status)){
                printf("Parent:, return values %d\n",WEXITSTATUS(status));
            }else{
                printf("Something wrong happened!\n");
            }
    }
    
    return 0;
}