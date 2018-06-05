#include <stdio.h>
#include <stdlib.h>




enum states {
	stage1,
	stage2,
	stage3
};

enum states stages = stage1;

int main(){
	char button_pressed = 0;
	int bNext = 0 ;
	int bCancel = 0;


	while(scanf("%d", &button_pressed) ){
		printf("%d \n", button_pressed);


		
		// THIS IS JUST TO GET SOME INPUTS, NOT IMPORTANT HOW 
		// STATE MACHINE IS IMPLEMENTED
		// BEGIN
		if(button_pressed == 1){

			bNext = 1 ;
			bCancel = 0;
		}

		if(button_pressed == 2){

			bNext = 0 ;
			bCancel = 1;
		}
		//END

		// STAGE 1	
		if(stages == stage1){		
			if (bNext){
				stages = stage2;
				printf("stage == stage2 \n");
			}

		}
		// STAGE 2
		else if(stages == stage2){
			if(bCancel && !bNext){
				stages = stage1;
				printf("stage == stage1 \n");
				
			}
			else if(bNext){
				stages = stage3;
				printf("stage == stage3 \n");
			}
		}
		// STAGE 3
		//
		else if(stages == stage3){
			if(bNext || bCancel){
				printf("stage == stage1 \n");
				stages = stage1;
			}
		}



		// THIS IS JUST TO GET SOME INPUTS, NOT IMPORTANT HOW 
		// STATE MACHINE IS IMPLEMENTED
		// BEGIN
		bNext = 0 ;
		bCancel = 0;

		if(button_pressed == 0){
			break;
		}
		//END
	}
			


	


	





	return 0;
}
