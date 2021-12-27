
#include<dirent.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char **argv){
    DIR* directory;
    struct dirent *entry;
    directory = opendir(argv[1]);
    int files = 0;

    if(directory == NULL){
        perror("Unable to read directory.");
    }
    while((entry = readdir(directory))!=NULL){
        files++;
        if(entry->d_name[0] != '.')
            printf("File %d: %s\t%lu\n", files, entry->d_name, entry->d_ino);
    }

    closedir(directory);

    return 0;
}