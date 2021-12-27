#include <stdio.h>
#define MAX_SIZE 100

int read_array (double *a, int max_elem, int *nb_elem);
void sort_array (double *a, int nb_elem);
void display_array (double *a, int nb_elem);

int main(){
	int nb_elem;
	double a[MAX_SIZE];
	if(read_array(a,5,&nb_elem) == 0 ){
		display_array(a,nb_elem);
		sort_array(a,nb_elem);
		display_array(a,nb_elem);
	}else{
		printf("Enter correct numbers!\n");
	}	
	return 0;
}


int read_array (double *a, int max_elem, int *nb_elem){
	if(MAX_SIZE < max_elem){
		return -1;
	}
	int size = 0;
	for(int i = 0 ; i < max_elem; i++){
		if(scanf("%lf",&a[i])){
			size++;
		}
	}
	*nb_elem = size;

	if(*nb_elem<max_elem){
		return -1;
	}
	return 0;
}


void sort_array (double *a, int nb_elem){
	double temp;
	for(int i = 0 ; i < nb_elem ; i++){
		for(int j = i+1; j < nb_elem;j++){
			if(a[i]>a[j]){
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

void display_array (double *a, int nb_elem){
	for(int i = 0 ; i < nb_elem; i++){
		printf("%lf ",a[i]);
	}
	printf("\n");
}