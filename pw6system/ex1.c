#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

char ch_arr[20][50];

void split(char *string)
{
    int i = 0;
    char *token = strtok(string, ":");

    while (token != NULL)
    {
        strcpy(ch_arr[i++],token);
        token = strtok(NULL, ":");
        
    }

}

int main(){
    char* str = getenv("PATH");
    // printf("PATH : %s\n", );

    split(str);

    for(int i = 0 ; i < 11;i++){
        printf("%s\n",ch_arr[i]);
    }
    printf("\n");
    struct stat buf;
	struct dirent *dir; DIR *d;
	for(int i=0;i<11;i++){
		d = opendir(ch_arr[i]);
		while((dir=readdir(d))!=NULL){
            if(strcmp(dir->d_name,"ls")==0){
                printf("%s/%s\n", ch_arr[i], "ls");
                
            }
		
		}
		closedir(d);
	}
    return 0;
}