#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




int main(int argc, char** argv){

	char string[] = "32-3";
	uint8_t neg = 0;

	uint16_t val = 0;

	uint8_t j = 0;

	uint8_t sizeOfString = strlen(string);
	printf("%d \n", sizeOfString);


	if(string[0]== '-'){
		neg = 1;
	}



	for(j = neg; j < sizeOfString; j++){
		if(val + (string[j]- 48)*pow(10,sizeOfString-1-neg-j) > 32767 ){
			return 1;
		}

		if(string[j] < 48 || string[j] > 58){
			return 1;
		}

		val += (string[j]- 48)*pow(10,sizeOfString-1-j);

	}

	if(neg == 1){
		printf("%d \n", -1*val);

		return -1*val;
	}
	else{
		
		printf("%d \n", val);
	
		return val;
	}








	return 0;
}
