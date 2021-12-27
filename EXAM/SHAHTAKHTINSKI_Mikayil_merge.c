#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <fcntl.h>    
#include <string.h>
#include <sys/wait.h> 
#include <sys/stat.h> 



int main(int argc, char **argv)
{

    int i = 0;
    int break_even=0;
    int break_odd=0;

    // check if exatcly 4 inputs were written
    if(argc != 4){
        printf("Wrong input!\n");
        exit(1);
    }

    // opening files
    int fd2 = open(argv[1], O_RDONLY, 0777);
    int fd3 = open(argv[2], O_RDONLY, 0777);
    int fd1 = open(argv[3], O_WRONLY | O_CREAT , 0777);
    

    if(fd1 == -1){
        printf("Something went wrong!\n");
        exit(2);
    }

    if(fd2 == -1){
        printf("Something went wrong!\n");
        exit(3);
    }

    if(fd3 == -1){
        printf("Something went wrong!\n");
        exit(4);
    }

    // character to read from files
    char buf;
    while(1)
        {
            if(i%2==0 && break_even==0){
                // write even
                if(read(fd2, &buf, 1)){
                    write(fd1, &buf, 1);
                }
                else{
                    break_even=1;
                }
                
            }else if(break_odd==0){
                // write odds
                if(read(fd3, &buf, 1)){
                    write(fd1, &buf, 1);
                }
                else{
                    break_odd=1;
                }
            }
            i++;
            if(break_even==1 && break_odd==1){
                break;
            }
        }


    // close file
    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}