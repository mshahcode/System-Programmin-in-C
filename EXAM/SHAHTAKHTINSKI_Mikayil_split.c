#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <sys/stat.h> 
#include <unistd.h>   
#include <fcntl.h>    
#include <string.h>


int main(int argc, char **argv)
{
    if(argc != 4){
        printf("Wrong input!\n");
        exit(1);
    }


    // opening files
    int fd1 = open(argv[1], O_RDONLY, 0777); // read file
    int fd2 = open(argv[2], O_WRONLY | O_CREAT , 0777); // write or create of not exist
    int fd3 = open(argv[3], O_WRONLY | O_CREAT , 0777); // write or create of not exist

    if(fd1 == -1){
        printf("Something went wrong!\n");
        exit(2);
    }

    if(fd2 == -1){
        printf("Something went wrong!\n");
        exit(3);
    }

    if(fd2 == -1){
        printf("Something went wrong!\n");
        exit(4);
    }

    

    int i = 0;
    char buf;
    while(read(fd1, &buf, 1))
	{
        // odd
        if(i%2!=0){
            printf("odd %c\n",buf);
		    write(fd3, &buf, 1);
        }else{
            // even
            printf("even %c\n",buf);
		    write(fd2, &buf, 1);
        }
        i++;
	}

    // closing files
    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}