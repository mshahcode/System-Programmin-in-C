#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000
#include <string.h>


int main(int argc, char *argv[]){
	int n;
	int m=1;
	int sizefile;
	int lines=0;  
	char temp[SIZE] = {0};                   
	char *filename, c;			       
	FILE *fp;
	char out[SIZE] = {0};				           

	n = atoi(argv[1]);  
	filename = argv[2]; 
	

	fseek(fp, 0, SEEK_END);  sizefile=ftell(fp);
	while(lines != n){ 
		if(sizefile == m)	break; 
		lines=0;
		fseek(fp,-m,SEEK_END); 
		fread(temp, sizeof(char), m, fp); 
		for(int i=0;temp[i]!='\0';i++){
			if(temp[i] == '\n')	lines++;
		}
		m++;
	}

	if(n > lines+1)
		printf("No %d lines in this file: %s\n", n, filename);
	else if(sizefile == m){
		fseek(fp,-m,SEEK_END); 
		fread(temp, sizeof(char), m, fp); 
		printf("%s\n", temp);
	}
	else if(lines == n){ 
		m-=2; 
		fseek(fp,-m,SEEK_END);
		fread(out, sizeof(char), m, fp);
		printf("%s\n", out); 
	}

	return 0;
}