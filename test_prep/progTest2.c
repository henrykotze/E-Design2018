#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




int main(int argc, char** argv){



	float* data = malloc(10*sizeof(float));

	float meep[] = {1,2,3,4,5,6,7,8,9,10};
	int num = 9;
	data = meep;

	float sumOfData = 0;

	int count =0;

	while(count < num){
		sumOfData += pow(meep[count],2);
		count++;
	}

	sumOfData = sqrt(sumOfData/num);


	printf("%f", sumOfData);



	






	return 0;



}

