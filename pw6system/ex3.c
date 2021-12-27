#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


char* my_ttyname(int fd){
    char* name;
    char* res;
    if((name = ttyname(fd)) == NULL){
        printf("File is not found!\n");
        res = "NULL";
    }else{
        strcpy(name,res);
    }
    return res;
}

int main(int argc,char **argv){
    int fd = open(argv[1], O_RDONLY, 0666);
    printf("%s\n",my_ttyname(fd));
    return 0;
}