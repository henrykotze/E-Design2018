#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;


void uart_comms(){
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_buffer, 1);
	rx_flag = 0;
	uart_command[uart_counter] = rx_buffer;
	if(uart_command[0] == '$'){

	uart_counter += 1;
	}

	if(uart_command[0] == '$' && uart_command[uart_counter-1] == '\n' && uart_command[uart_counter - 2] == '\r' && uart_counter > 2){

		switch(uart_command[1]){
			case  'A': // Request Serial number

				memcpy(studentnumber, uart_command, 2 );
				memcpy(studentnumber+2,comma,1);
				memcpy(studentnumber+3 ,studentnumber1,8 );
				memcpy(studentnumber+11,endSimbol,sizeof(endSimbol));
				HAL_UART_Transmit(&huart1, ((uint8_t*)studentnumber), 13, 10);
				break;

				 case 'B':
					memcpy(return_value, uart_command, 2);
					memcpy(return_value+2, endSimbol,2 );
					HAL_UART_Transmit(&huart1, return_val, sizeof(return_value), 1000);
					 if(uart_command[2]=='0'){
					 }
					 else if(uart_command[2] == '1'){
					 }
					 break;

				 case 'C':
					 memcpy(return_value, uart_command, 2);
					 memcpy(return_value+2, endSimbol,2 );
					 HAL_UART_Transmit(&huart1, return_val, sizeof(return_value), 1000);
					 if(uart_command[2]=='0'){
						auto_heating = 0;	// auto heating off
					 }
					 else if(uart_command[2] == '1'){
						auto_heating = 1;	// auto heating on
					 }
					 break;

				 case 'D':
					 memcpy(return_value, uart_command, 2);
					 memcpy(return_value+2, endSimbol,2 );
					 HAL_UART_Transmit(&huart1, return_val, sizeof(return_value), 1000);
					 if(auto_heating == 0){	// if auto heating off
						 if(uart_command[2]=='0'){

						 }
						 else if(uart_command[2] == '1'){
							 // do something
						 }
					 }
					 break;

				 case 'E': //Enable/Disble logging to flash memory
					 memcpy(return_value, uart_command, 2);
					 memcpy(return_value+2, endSimbol,2 );
					 HAL_UART_Transmit(&huart1, return_val, sizeof(return_value), 1000);
					 if(uart_command[2]=='0'){ // logging disable
						 //do something
					 }
					 else if(uart_command[2] == '1'){ // logging enable
						 // do something
					 }
					 break;

				 case 'F'://Set new temperature set-point
					 memcpy(return_value, uart_command,2);
					 memcpy(return_value+2,endSimbol, 2);
					HAL_UART_Transmit(&huart1,(uint8_t*)return_value, sizeof(return_value), 1000);

					 sizeOfTemp = uart_counter - 5;
					 memcpy(set_temp, uart_command+3, sizeOfTemp * sizeof(uint8_t) );

					break;

				 case 'G':
					 // transmit temperature
					 memcpy(return_value, uart_command, 2);
					 memcpy(return_value+2, comma, 1);
					 memcpy(return_value+3, set_temp, sizeOfTemp * sizeof(uint8_t));
					 memcpy(return_value+3+sizeOfTemp * sizeof(uint8_t),endSimbol, 2);

					HAL_UART_Transmit(&huart1,(uint8_t*)return_value, (2+3+sizeOfTemp)*sizeof(uint8_t), 1000);
					 break;

				 case 'H': //set time
					HAL_UART_Transmit(&huart1,(uint8_t*)return_val, sizeof(return_value)+1, 1000);
					 break;

				 case 'I': // get time
					HAL_UART_Transmit(&huart1,(uint8_t*)time, sizeof(time), 1000);
					 break;

				 case 'J': // set heating schedule
					HAL_UART_Transmit(&huart1,(uint8_t*)return_val, sizeof(return_val), 1000);
					 break;

				 case 'K':
					 // send telematary
					 break;

				 case 'L': // Request log Entry
					 // do something
					 break;
				 }
				memset(uart_command,0x00, 40);
				memset(return_value,0x00, 15);
				uart_counter = 0;
		  }
		  else if(uart_counter > 39 ){
			  uart_counter = 0;
		  }
}

void seven_segment(){
	if(segment_counter == 1){	// Left Most Digit
		segment_counter += 1;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);	// D1
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);		// 7_SEG_2
	}
	else if( segment_counter == 2){		// Middle left Digit
		segment_counter += 1;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);		// D2
	}
	else if( segment_counter == 3){		// Middle Right Digit
		segment_counter += 1;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);		// D3
	}
	else if( segment_counter == 4){ // Right Most Digit
		segment_counter = 1;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);		// D4
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
		rx_flag = 1;

}

void init_peripherals(){

	//A
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET); 	// 7_SEG_1

	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);		// 7_SEG_3
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);		// 7_SEG_7
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);		// 7_SEG_6

	// B
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);		// D4
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);		// D2
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);		// D3
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);		// 7_SEG_4
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);	// D1


	  studentnumber = (uint8_t*)malloc(15);
	  memset(studentnumber, 0x00, 15);

	HAL_TIM_Base_Start_IT(&htim2);

}

void adc_comms(){
	adc_raw_value = HAL_ADC_GetValue(&hadc2);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	adc_flag = 1;
}
