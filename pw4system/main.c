#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <string.h>
#define SIZE 10000


typedef struct MYFILE{
    char buffer[SIZE]; // buffer
    int fd; // for open
    char *filename; // filename
} MYFILE;

int my_open(MYFILE f,char mode){
    int fd;
    if(mode == 'r'){ // read
        fd = open(f.filename, O_CREAT | O_RDONLY, 0666);

    }else if(mode == 'w')  // write
        fd = open(f.filename, O_WRONLY | O_CREAT, 0666);
    else{
        printf("No such thing!");
        return -1;
    }
    return fd;
}

MYFILE my_getc(MYFILE f){
    int c;
    for(int i = 0 ; read(f.fd,&c,1) != 0; i++){
        f.buffer[i] = c;
    }
    return f;
}

void my_putc(MYFILE f){
    write(1,f.buffer,strlen(f.buffer)); // firts method
    //printf("%s\n",f.buffer);  // second method
}

void my_close(MYFILE f){
    close(f.fd);
}


int main(){
    MYFILE f;
    f.filename = "foo1.txt";
    f.fd = my_open(f,'r');
    f = my_getc(f);
    my_putc(f);
    
    MYFILE f2;
    f2.filename = "foo2.txt";
    f2.fd = my_open(f2,'r');
    f2 = my_getc(f2);
    my_putc(f2);


    printf("\n");

    my_close(f);
    my_close(f2);

    
    return 0;
}