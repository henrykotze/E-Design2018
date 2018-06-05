#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>




int main(int argc, char **argv){



	printf("You have entered: %d argumanets \n", argc);

	uint8_t* val = (argv[argc-1]);

	printf("%d \n",*val);


	uint8_t* meep = (uint8_t*)malloc(1*sizeof(uint8_t));

	*meep = 0x0A;


	printf("%d \n",*meep);


	uint8_t swapNibble = ((*meep&240)>>4)|(*meep<<4);

	printf("%d \n", swapNibble);












	return 0;
}
