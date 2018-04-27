#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;



void seven_segment(){

	if(segment_counter == 0){	// Left Most Digit

		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);	// D1
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);		// D2
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);		// D3
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);		// D4
		seven_segment_display(segment_val[segment_counter]-48 );
		segment_counter += 1;
	}
	else if( segment_counter == 1){		// Middle left Digit
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);		// D1
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);		// D2
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);		// D3
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);		// D4
		seven_segment_display(segment_val[segment_counter]-48);
		segment_counter += 1;
	}
	else if( segment_counter == 2){		// Middle Right Digit
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);		// D1
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);		// D2
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);		// D3
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);		// D4
		seven_segment_display(segment_val[segment_counter]-48);
		segment_counter += 1;
	}
	else if( segment_counter == 3){ // Right Most Digit
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);		// D1
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);		// D2
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);		// D3
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);		// D4
		seven_segment_display(segment_val[segment_counter]-48);
		segment_counter = 0;
	}
}
