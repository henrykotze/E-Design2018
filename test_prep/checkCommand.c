#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



int main(int argc, char** argv){
	
	char* buf = malloc(10*sizeof(char));
	char command[] = "$1memasjfnasjkd\r\n";

	size_t len = 3;

	buf = command;

	printf("%d \n", len);


	if(*buf == '$' && ( *(buf+1) == '0' || *(buf+1) == '1') && *(buf+len-2) == '\r' && *(buf+len-1) == '\n' ){
		printf("0 \n");
	}

	else if( strlen(buf) != len ){
		printf("3");
	}
	else{
		printf("1");
	}

	




	for(int i = 0; i < len; i++){
		printf("%d: %c\n", i, *(buf+i));
		



	}




	return 0;
}
