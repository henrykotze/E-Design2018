#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;


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
//				HAL_UART_Transmit(&huart1, ((uint8_t*)studentnumber), 13, 10);
				HAL_UART_Transmit_IT(&huart1, ((uint8_t*)studentnumber), 13);
				break;

				 case 'B':
					memcpy(return_value, uart_command, 2);
					memcpy(return_value+2, endSimbol,2 );
					HAL_UART_Transmit(&huart1, return_value, sizeof(return_value), 1000);
					 if(uart_command[2]=='0'){
					 }
					 else if(uart_command[2] == '1'){
					 }
					 break;

				 case 'C':
					 memcpy(return_value, uart_command, 2);
					 memcpy(return_value+2, endSimbol,2 );
					 HAL_UART_Transmit(&huart1, return_value, sizeof(return_value), 1000);
					 if(uart_command[2]=='0'){
						heater_state = heater_OFF;	// auto heating off
					 }
					 else if(uart_command[2] == '1'){
						 heater_state = heater_ON;	// auto heating on
					 }
					 break;

				 case 'D':
					 memcpy(return_value, uart_command, 2);
					 memcpy(return_value+2, endSimbol,2 );
					 HAL_UART_Transmit(&huart1, return_value, sizeof(return_value), 1000);
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
					 HAL_UART_Transmit(&huart1, return_value, sizeof(return_value), 1000);
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
					 memset(set_temp, 0x00, 4);
					 memcpy(set_temp, uart_command+3, sizeOfTemp * sizeof(uint8_t) );
					 segment_val =set_temp;

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
					HAL_UART_Transmit(&huart1,return_value, sizeof(return_value)+1, 1000);
					 break;

				 case 'I': // get time
					HAL_UART_Transmit(&huart1,(uint8_t*)time, sizeof(time), 1000);
					 break;

				 case 'J': // set heating schedule
					HAL_UART_Transmit(&huart1,return_value, sizeof(return_value), 1000);
					 break;

				 case 'K':
					 // send telematary
					 memcpy(return_value, uart_command, 2);
					 memcpy(return_value+2,comma,1 );
					 //current
					 memcpy(return_value+3,current_rms,strlen(current_rms));
					 memcpy(return_value+strlen((char*)return_value),comma,1 );
					 //voltage
					 memcpy(return_value+strlen((char*)return_value),voltage_rms,strlen(voltage_rms) );
					 memcpy(return_value+strlen((char*)return_value),comma,1 );
					 //ambient temp
					 memcpy(return_value+strlen((char*)return_value),&send_unk_val,1 );
					 memcpy(return_value+strlen((char*)return_value),comma,1 );
					 // hot water temp
					 memcpy(return_value+strlen((char*)return_value),&send_unk_val,1 );
					 memcpy(return_value+strlen((char*)return_value),comma,1 );
					 // accumulated water
					 memcpy(return_value+strlen((char*)return_value),&send_unk_val,1 );
					 memcpy(return_value+strlen((char*)return_value),comma,1 );
					 // heating element
					 memcpy(return_value+strlen((char*)return_value),heater_OFF,strlen(heater_OFF) );
					 memcpy(return_value+strlen((char*)return_value),comma,1 );
					 //vale state
					 memcpy(return_value+strlen((char*)return_value), valve_OPEN,strlen(valve_OPEN)-1 );
					 memcpy(return_value+strlen((char*)return_value), endSimbol,2 );

					 HAL_UART_Transmit(&huart1,return_value, (uint16_t)strlen((char*)return_value),100);
//					 HAL_UART_Transmit_IT(&huart1,return_value, 28);

					 break;

				 case 'L': // Request log Entry
					 // do something
					 break;
				 }
				memset(uart_command,0x00, 40);
				memset(return_value,0x00, 50);
				uart_counter = 0;
		  }
		  else if(uart_counter > 39 ){
			  uart_counter = 0;
		  }
}

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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
		rx_flag = 1;

}

void init_peripherals(){

	//A
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET); 		// 7_SEG_1

	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);		// 7_SEG_3
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);		// 7_SEG_7
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);		// 7_SEG_6

	// B
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);		// D4
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);		// D2
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);		// D3
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);		// 7_SEG_4
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);		// D1
	// C
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);		// 7_SEG_5

	  studentnumber = (uint8_t*)malloc(15);
	  memset(studentnumber, 0x00, 15);

	  return_value = (uint8_t*)malloc(50);
	  memset(return_value, 0x00, 50);

	  uart_command = (uint8_t*)malloc(40);
	  memset(uart_command, 0x00, 40);

	  set_temp = (uint8_t*)malloc(3);
	  memset(set_temp, 0x00, 4);

	  segment_val =set_temp;
//	  memset(segment_val, 0x00, 4);

	  ADC1_buffer = (uint32_t*)malloc(4*sizeof(uint32_t));
	  memset(ADC1_buffer, 0x00, 4);

	  voltage_rms =(char*)malloc(3*sizeof(char));
	  memset(voltage_rms, 0x00, 3);

	  current_rms =(char*)malloc(4*sizeof(char));
	  memset(current_rms, 0x00, 4);

	  voltage_int_rms = (uint32_t*)malloc(4*sizeof(uint32_t));
	  current_int_rms= (uint32_t*)malloc(4*sizeof(uint32_t));

	  //HEATER
	  heater_state = heater_OFF;

	HAL_TIM_Base_Start_IT(&htim2);
//	HAL_ADCEx_Calibration_Start(&hadc1,ADC_SINGLE_ENDED);

}

void adc_comms(){



	 adc_raw_voltage=  ADC1_buffer[0];
	 adc_raw_current=	ADC1_buffer[1];
	//Converting Voltage
	adc_buffer_voltage = (pow((adc_raw_voltage-2072.202)/0.008629,2))+adc_buffer_voltage;

	//Converting Current
	adc_buffer_current = (pow((adc_raw_current-2072.202)/0.14603,2))+adc_buffer_current;

	adc_counter += 1;
	if(adc_counter == 10000){
		*voltage_int_rms = sqrt(adc_buffer_voltage/10000);
		*current_int_rms = sqrt(adc_buffer_current/10000);
		sprintf(voltage_rms,"%lu", *voltage_int_rms);
		sprintf(current_rms,"%lu", *current_int_rms);
		adc_counter = 0;

		adc_buffer_voltage = 0;
		adc_buffer_current = 0;
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	adc_flag = 1;
}

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
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);//B
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);//D
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);//E
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);

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

