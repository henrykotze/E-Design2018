#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;


void seven_segment_display(uint8_t num){
	switch(num){
	case 1:
		// ON
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
		//OFF
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);
		break;
	case 2:
		//ON
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);//A
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);//B
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);//G
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET);//E
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);//B
		//OFF
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);//F
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);//C
		break;

	case 3:
		//ON
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET); //A
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET); //B
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);//G
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//C
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);//D

		// OFF
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);//F
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);//E

		break;
	case 4:
		//ON
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);//F
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);//G
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//C
		//OFF
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET); //A
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);//E
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET); //A
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);//D

		break;
	case 5:
		//ON
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET); //A
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);//F
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);//G
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//C

		//OFF
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET); //B
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);//E
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);//d
		break;

	case 6:
		// ON
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET); //A
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);//F
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);//G
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//C
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);//D
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET);//E
		//OFF
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET); //B
		break;
	case 7:
		//ON
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET); //A
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);//B
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//C
		//OFF
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);//E
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);//F
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);//G
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);//D

		break;
	case 8:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET); //A
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);//B
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//C
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);//D
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET);//E
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);//F
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);//G
		break;
	case 9:
		//ON
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET); //A
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);//B
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//C
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);//F
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);//G
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
		//OFF
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);//E
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);//D
		break;
	case 0:
		//ON
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET); //A
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);//B
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);//C
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);//D
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET);//E
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);//F
		//OFF

		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);//G
		break;
	default:
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET); //A
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);//B
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);//C
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);//D
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);//E
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);//F
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);//
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);


	}



}