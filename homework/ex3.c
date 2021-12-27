#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX 256

char * myttyname(int fd);

int main(int argc, char **argv)
{
    int i;
    int n = 5;
    char *pointer;
    for(i = 0 ; i < n; i++){
        pointer = myttyname(i);
        if(pointer == NULL){
            printf("%d ttyname: null\n",i); 
        }else{
            printf("%d ttyname: %s\n",i,pointer);
        }
    }

    return 0;
}


char * myttyname(int fd){
    static char path[MAX];
    struct stat stin;
    DIR *dp; // directory
    struct stat stdev;
    struct dirent *d;

    // stating the file by the file descriptor
    if(fstat(fd,&stin)==-1){
        return NULL;
    }

    // check if the file is a character special file
    if(!S_ISCHR(stin.st_mode)){
        return NULL;
    }

    dp = opendir("/dev/pts"); // open directory

    // read files from directory
    while((d = readdir(dp))!=NULL){
        if(snprintf(path, sizeof path,"%s/%s", "/dev/pts" ,d->d_name) < sizeof(path)){
            if(stat(path, &stdev) == 0){
                if(stdev.st_dev == stin.st_dev && stdev.st_ino == stin.st_ino){
                    break;
                }
            }
        }
    }

    closedir(dp); // closing directory
    if(d == NULL){
        return NULL;
    }
    return path;
}
