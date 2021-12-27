#include <dirent.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

void prepare(void){
    struct sigaction s ;
    s.sa_flags = SA_RESTART ; 
    sigemptyset (&s.sa_mask) ; 
    sigaddset (&s.sa_mask , SIGUSR1) ; 
    sigaction (SIGUSR1 , &s, NULL) ;
    struct sigaction s2 ;

    //second
    s.sa_flags = SA_RESTART ;
    sigemptyset (&s.sa_mask) ;
    sigaddset (&s.sa_mask , SIGUSR2) ;
    sigaction (SIGUSR2 , &s, NULL) ;
    struct sigaction s3 ;


    // third
    s.sa_flags = SA_RESTART ;
    sigemptyset (&s.sa_mask) ; 
    sigaddset (&s.sa_mask , SIGTERM) ;
    sigaction (SIGTERM , &s, NULL) ;
}

int endswith (const char * name, const char * sufx){
    // const char *extension = name + strlen(name) - 3;

    // if(strcmp(extension, sufx)==0){
    //         return 1;
    // }else{
    //     return 0;
    // }

    const char *dot = strrchr(name, '.');
    if(strcmp(dot + 1,sufx)==0){
        return 1;
    }
    return 0;
}

void rename1(const char *filename, const char *osufx, const char *nsufx){
    char *retStr;
    char *lastExt;
  
    strcpy (retStr, filename);
    lastExt = strrchr (retStr, '.');
    if (lastExt != NULL)
        *lastExt = '\0';

    strcat(retStr,'.');
    strcat(retStr,nsufx);
    printf("%s\n",retStr);
    filename = retStr;
}


int traverse (const char *filename, const char *osufx, int desc){
    DIR* directory;
    struct dirent *entry;
    directory = opendir(filename);
    int files = 0;

    if(directory == NULL){
        perror("Unable to read directory.");
    }
    while((entry = readdir(directory))!=NULL){
        if(endswith(entry->d_name[0],osufx)==1){
            printf("File %d: %s\t%lu\n", files, entry->d_name, entry->d_ino);
            files++;
        }
    }
    closedir(directory);
    return files;
}

int modify(const char *osufx, const char *nsufx, int desc, pid_t pid)
{
    char c;
    char buffer[1024];
    int i = 0, n = 0;

    while (read(desc, &c, 1) > 0)
    {
        if (c == '\n')
        {
            buffer[i] = '\0';
            rename1(buffer, osufx, nsufx);
            kill(pid, SIGUSR1);
            n++;
            i = 0;
        }
        else
            i++;
    }
    kill(pid, SIGTERM); // terminate the proccess
    return n;
}

int wait_children(int nb_files)
{
    int status1;
    int status2;

    wait(&status1);
    wait(&status2);

    int return1 = WIFEXITED(status1);
    int return2 = WIFEXITED(status2);

    if(return1 == return2){
        if(return1 == nb_files){
            return 0;
        }
    }  
    return 1;

}

int wait_signals (pid_t pid){
    struct sigaction sa;
    sa.sa_handler = &wait;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &sa, NULL);
    return 1;
}


int main(int argc, char* argv[]){
    int status;
    int tube[2];
    int pid1;
    pid1 = pipe(tube);

    if(pid1==-1){
        printf("Sometging went wrong!\n");
        exit(1);
    }

    if(argc != 4){
        printf("Wrong number of inputs!\n");
    }

    pid_t pid = fork();

    if(pid < 0){
        printf("Something went wrong!\n");
    }

    if(pid == 0){
        // child
        close(tube[0]);
        int nb_files = traverse(argv[1],argv[2],0);
        dup2(tube[1],1);
    }else{
        // parent
        // wait_children()

        pid_t pid2 = fork();

        if(pid2 == -1){
            printf("Something went wrong!\n");
            exit(2);
        }

        if(pid2 == 0){
            // child2
        }
    }

    return 0;
}