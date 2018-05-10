#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;
extern RTC_HandleTypeDef hrtc;



void uart_comms(){
	//HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_buffer, 1);
	rx_flag = 0;
	uart_command[uart_counter] = rx_buffer;
	if(uart_command[0] == '$'){

		uart_counter += 1;
	}

	if(uart_command[0] == '$' && uart_command[uart_counter-1] == '\n' && uart_command[uart_counter - 2] == '\r' && uart_counter > 2){
		memset(return_value,0x00, 50);
		uart_command_copy = uart_command;
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

				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);		// Valve
			}
			else if(uart_command[3] == '0'){
				valve_state=valve_CLOSE;
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);		// Valve
			}
			break;

		case 'C':
			memcpy(return_value, uart_command, 2);
			memcpy(return_value+2, endSimbol,2 );
			HAL_UART_Transmit_IT(&huart1, return_value, strlen((char*)return_value));
			if(uart_command[3]=='0'){
				// auto heating off
				auto_heating = 0;
			}
			else if(uart_command[3] == '1'){
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
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);	// Heater

				}
				else if(uart_command[3] == '1'){
					heater_state = heater_ON;
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);	// Heater
				}
			}
			break;

		case 'E': //Enable/Disble logging to flash memory
			memcpy(return_value, uart_command, 2);
			memcpy(return_value+2, endSimbol,2 );
			HAL_UART_Transmit_IT(&huart1, return_value, strlen((char*)return_value));
			if(uart_command[3]=='0'){ // logging disable
				enableFlashLogging = 0;
			}
			else if(uart_command[3] == '1'){ // logging enable
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
			memcpy(return_value, uart_command, 2);
			memcpy(return_value+2,endSimbol, 2);
			HAL_UART_Transmit_IT(&huart1,return_value, strlen((char*)return_value));

			__HAL_RTC_WRITEPROTECTION_DISABLE(&hrtc); // Disable write protection
			RTC_EnterInitMode(&hrtc); // Enter init mode

			heating_info = strtok((char*)uart_command_copy, "$H,");
			time->Hours = strtol(heating_info, NULL,10);
			heating_info = (strtok(NULL, ","));
			time->Minutes = strtol(heating_info, NULL,10);
			heating_info = (strtok(NULL, ",\r\n"));
			time->Seconds = strtol(heating_info, NULL,10);


			HAL_RTC_SetTime(&hrtc, time, RTC_FORMAT_BIN);
			HAL_RTC_SetDate(&hrtc, date, RTC_FORMAT_BIN);
			__HAL_RTC_WRITEPROTECTION_ENABLE(&hrtc);
			HAL_RTC_GetTime(&hrtc,time,RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc,date,RTC_FORMAT_BIN);

			break;

		case 'I': // get time
			HAL_RTC_GetTime(&hrtc,time,RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc,date,RTC_FORMAT_BIN);
			memcpy(return_value, uart_command, 2);
			memcpy(return_value+2,comma,1);

			itoa((time->Hours),temp_time_var,10  );
			memcpy(return_value+strlen((char*)return_value),temp_time_var,strlen(temp_time_var));
			memcpy(return_value+strlen((char*)return_value),comma,1 );

			itoa((time->Minutes),temp_time_var,10  );
			memcpy(return_value+strlen((char*)return_value),temp_time_var,strlen(temp_time_var));
			memcpy(return_value+strlen((char*)return_value),comma,1 );

			itoa((time->Seconds),temp_time_var,10  );
			memcpy(return_value+strlen((char*)return_value),temp_time_var,strlen(temp_time_var));
			//memcpy(return_value+strlen((char*)return_value),comma,1 );

			//memcpy(return_value+strlen((char*)return_value),temp_time_var,strlen(temp_time_var));
			memcpy(return_value+strlen((char*)return_value), endSimbol,2 );


			HAL_UART_Transmit_IT(&huart1,(uint8_t*)return_value, strlen((char*)return_value));
			break;

		case 'J': // set heating schedule
			if(auto_heating == 1){
				memcpy(return_value, uart_command, 2);
				memcpy(return_value+2, endSimbol,2 );
				HAL_UART_Transmit_IT(&huart1,return_value, strlen((char*)return_value));


				if(uart_command[3] == '1'){ // first heating schedule

					heating_info = strtok((char*)uart_command_copy, ",");
					heating_info = (strtok(NULL, ","));
					heating_info = (strtok(NULL, ","));
					heating_schedule[0].Hours = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, ","));
					heating_schedule[0].Minutes = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, ","));
					heating_schedule[0].Seconds = strtol(heating_info, NULL,10);


					heating_info = (strtok(NULL, ","));
					heating_schedule[1].Hours = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, ","));
					heating_schedule[1].Minutes = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, "\r\n"));
					heating_schedule[1].Seconds = strtol(heating_info, NULL,10);


				}
				else if(uart_command[3] == '2'){ // second heating schedule

					heating_info = strtok((char*)uart_command_copy, ",");
					heating_info = (strtok(NULL, ","));
					heating_info = (strtok(NULL, ","));
					heating_schedule[2].Hours = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, ","));
					heating_schedule[2].Minutes = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, ","));
					heating_schedule[2].Seconds = strtol(heating_info, NULL,10);

					heating_info = (strtok(NULL, ","));
					heating_schedule[3].Hours = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, ","));
					heating_schedule[3].Minutes = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, "\r\n"));
					heating_schedule[3].Seconds = strtol(heating_info, NULL,10);

				}
				else if(uart_command[3] == '3'){ // 3rd heating schedule

					heating_info = strtok((char*)uart_command_copy, ",");
					heating_info = (strtok(NULL, ","));
					heating_info = (strtok(NULL, ","));
					heating_schedule[4].Hours = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, ","));
					heating_schedule[4].Minutes = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, ","));
					heating_schedule[4].Seconds = strtol(heating_info, NULL,10);

					heating_info = (strtok(NULL, ","));
					heating_schedule[5].Hours = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, ","));
					heating_schedule[5].Minutes = strtol(heating_info, NULL,10);
					heating_info = (strtok(NULL, "\r\n"));
					heating_schedule[5].Seconds = strtol(heating_info, NULL,10);
				}
			}
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
			log_receiced_num = uart_command[3] - 48;
			if(log_receiced_num > log_counter && log_full == 0){

			}
			else{
				//flash_mem_start=flash_mem_start+64*log_receiced_num;
				//memcpy(flash_stored, flash_mem_start+64*log_receiced_num, 60 );
				//flash_stored = flash_mem_start;
				//return_value = (char*)flash_stored;
				HAL_UART_Transmit_IT(&huart1,(uint8_t*)(flash_mem_start+64*log_receiced_num), strlen((char*)(flash_mem_start+64*log_receiced_num)));
				//HAL_FLASH_Lock();
			}
			break;
		}
		memset(uart_command,0x00, 60);

		uart_counter = 0;
	}
	else if(uart_counter > 59 ){
		uart_counter = 0;
	}
}
