#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void copy(int fdsrc, int fddst){
    char buf;
    while(read(fdsrc, &buf, 1))
	{
		write(fddst, &buf, 1);
	}
}


int main(){
    int pid;
    int tube[2];
    pid = pipe(tube);
    // 
    if(pid == -1){
        exit(12);
    }

    pid = fork();

    int status;

    if(pid==-1){
        exit(-1);
    }

    if(pid==0){ // child
        char c;
        close(tube[1]);
        copy(tube[0],1);
        exit(1);
    }else{
        close(tube[0]);
        copy(0,tube[1]);
        exit(1);
    }

    return 0;
}