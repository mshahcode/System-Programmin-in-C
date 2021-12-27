#include <stdio.h>
#include <stdlib.h>
#include "area.h"
#include "perimeter.h"

int main(){
    double radius;
    printf("Enter radius to compute area and perimeter: ");
    scanf("%lf",&radius);
    printf("Area %lf\n",area(radius));
    printf("Perimeter %lf\n",perimeter(radius));
	return 0;
}
