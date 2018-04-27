#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;



void uart_comms(){
	//HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_buffer, 1);
	rx_flag = 0;
	uart_command[uart_counter] = rx_buffer;
	if(uart_command[0] == '$'){

		uart_counter += 1;
		//	if(uart_counter > 10){
		//		memset(uart_command,0x00, 40);
		//	}
	}

	if(uart_command[0] == '$' && uart_command[uart_counter-1] == '\n' && uart_command[uart_counter - 2] == '\r' && uart_counter > 2){
		memset(return_value,0x00, 50);
		switch(uart_command[1]){
		case  'A': // Request Serial number

			memcpy(studentnumber, uart_command, 2 );
			memcpy(studentnumber+2,comma,1);
			memcpy(studentnumber+3 ,studentnumber1,8 );
			memcpy(studentnumber+11,endSimbol,sizeof(endSimbol));
			HAL_UART_Transmit_IT(&huart1, ((uint8_t*)studentnumber), 13);
			break;

		case 'B':
			memcpy(return_value, uart_command, 2);
			memcpy(return_value+2, endSimbol,2 );
			HAL_UART_Transmit_IT(&huart1, return_value,  strlen((char*)return_value));
			if(uart_command[3]=='1'){
				valve_state = valve_OPEN;

				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);		// Valve
			}
			else if(uart_command[3] == '0'){
				valve_state=valve_CLOSE;
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);		// Valve
			}
			break;

		case 'C':
			memcpy(return_value, uart_command, 2);
			memcpy(return_value+2, endSimbol,2 );
			HAL_UART_Transmit_IT(&huart1, return_value, strlen((char*)return_value));
			if(uart_command[2]=='0'){
				// auto heating off
				auto_heating = 0;
			}
			else if(uart_command[2] == '1'){
				auto_heating = 1;
			}
			break;

		case 'D':
			memcpy(return_value, uart_command, 2);
			memcpy(return_value+2, endSimbol,2 );
			HAL_UART_Transmit_IT(&huart1, return_value,  strlen((char*)return_value));
			if(auto_heating == 0){	// if auto heating off
				if(uart_command[3]=='0'){
					heater_state = heater_OFF;
					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);	// Heater

				}
				else if(uart_command[3] == '1'){
					heater_state = heater_ON;
					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);	// Heater
				}
			}
			break;

		case 'E': //Enable/Disble logging to flash memory
			memcpy(return_value, uart_command, 2);
			memcpy(return_value+2, endSimbol,2 );
			HAL_UART_Transmit_IT(&huart1, return_value, strlen((char*)return_value));
			if(uart_command[2]=='0'){ // logging disable
				enableFlashLogging = 0;
			}
			else if(uart_command[2] == '1'){ // logging enable
				enableFlashLogging = 1;
			}
			break;

		case 'F'://Set new temperature set-point
			memcpy(return_value, uart_command,2);
			memcpy(return_value+2,endSimbol, 2);
			HAL_UART_Transmit_IT(&huart1,(uint8_t*)return_value, strlen((char*)return_value));

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

			HAL_UART_Transmit_IT(&huart1,(uint8_t*)return_value, strlen((char*)return_value));
			break;

		case 'H': //set time
			HAL_UART_Transmit_IT(&huart1,return_value, sizeof(return_value)+1);
			break;

		case 'I': // get time
			HAL_UART_Transmit_IT(&huart1,(uint8_t*)time, sizeof(time));
			break;

		case 'J': // set heating schedule
			HAL_UART_Transmit_IT(&huart1,return_value, sizeof(return_value));
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
			memcpy(return_value+strlen((char*)return_value),ambient_temp,strlen(ambient_temp) );
			memcpy(return_value+strlen((char*)return_value),comma,1 );
			// hot water temp
			memcpy(return_value+strlen((char*)return_value),geyser_temp,strlen(geyser_temp) );
			memcpy(return_value+strlen((char*)return_value),comma,1 );
			// accumulated water
			memcpy(return_value+strlen((char*)return_value),total_water,strlen(total_water) );
			memcpy(return_value+strlen((char*)return_value),comma,1 );
			// heating element
			memcpy(return_value+strlen((char*)return_value),heater_state,strlen(heater_state));
			memcpy(return_value+strlen((char*)return_value),comma,1 );
			//vale state
			if(valve_state == valve_OPEN){
				memcpy(return_value+strlen((char*)return_value), valve_state,strlen(valve_state) -1);
			}
			else{
				memcpy(return_value+strlen((char*)return_value), valve_state,strlen(valve_state) );
			}

			memcpy(return_value+strlen((char*)return_value), endSimbol,2 );
			HAL_UART_Transmit_IT(&huart1,(uint8_t*)return_value, strlen((char*)return_value));

			break;

		case 'L': // Request log Entry
			// do something
			break;
		}
		memset(uart_command,0x00, 40);

		uart_counter = 0;
	}
	else if(uart_counter > 39 ){
		uart_counter = 0;
	}
}
