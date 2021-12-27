#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
    int fd1;
    int fd2;
    int choice = 1;
    int opt;

    if(argc<=1){
        printf("Wrong input!\n");
        exit(1);
    }

    while ((opt = getopt(argc,argv,"a")) != -1)
    {
        switch (opt)
        {
        case 'a':
            choice = 0;
            break;
        
        default:
            break;
        }
    }

    if(choice){
        fd1 = open(argv[1], O_RDONLY, 0777);
        fd2 = open("output_tee.c", O_WRONLY | O_TRUNC | O_CREAT, 0777);

    }else{
        fd1 = open(argv[2], O_RDONLY, 0777);
        fd2 = open("output_tee.c", O_WRONLY | O_APPEND , 0777);
        if(fd2==-1){
            printf("File doesn't exit, so can't append!\n");
            close(fd1);
            exit(2);
        }

    }

    if(fd1 == -1){
        printf("Can't open file!\n");
        close(fd2);
        exit(3);
    }

    char c;
    while(read(fd1,&c,1)>0){
        printf("%c",c);
        write(fd2,&c,1);
    }


    close(fd1);
    close(fd2);
    return 0;
}
