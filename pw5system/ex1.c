#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char **argv){
    struct stat buf;
    if(argc==1){
        printf("No file provided!\n");
        return -1;
    }

    char* filename = argv[1];
    printf("%s\n",filename);
    stat(argv[1],&buf);

    if(S_ISREG(buf.st_mode)){
        printf("Regular file!\n");
    }
    if(S_ISDIR(buf.st_mode)){
        printf("Directory!\n");
    }
    if(S_ISLNK(buf.st_mode)){
        printf("Symbolic link\n");
    }


    if((buf.st_mode & S_IRUSR) ) printf("Owner has read permission\n");
	if((buf.st_mode & S_IWUSR) ) printf("Owner has write permission\n");
	if((buf.st_mode & S_IXUSR) ) printf("Owner has execute permission\n");

    printf("Owner permissions: ");
    if( buf.st_mode & S_IRUSR )
        printf("read \n");
    if( buf.st_mode & S_IWUSR )
        printf("write \n");
    if( buf.st_mode & S_IXUSR )
        printf("execute\n");

    printf("Group permissions: ");
    if( buf.st_mode & S_IRGRP )
        printf("read \n");
    if( buf.st_mode & S_IWGRP )
        printf("write \n");
    if( buf.st_mode & S_IXGRP )
        printf("execute\n");

    if( buf.st_mode & S_IROTH )
        printf("read \n");
    if( buf.st_mode & S_IWOTH )
        printf("write \n");
    if( buf.st_mode & S_IXOTH )
        printf("execute\n");

   
    return 0;
}