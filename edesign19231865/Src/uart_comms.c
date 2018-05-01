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
			// Update the Calendar (cancel write protection and enter init mode)
//			time->DayLightSaving = time->DayLightSaving;
//			new_time->SecondFraction = time->SecondFraction;
//			new_time->StoreOperation = time->StoreOperation;
//			new_time->TimeFormat = time->TimeFormat;
//			new_time->SubSeconds = time->SubSeconds;
			HAL_RTC_SetTime(&hrtc, time, RTC_FORMAT_BCD);
//			halStatus = HAL_RTC_SetDate(&hrtc, &rtcDate, RTC_FORMAT_BCD);
			__HAL_RTC_WRITEPROTECTION_ENABLE(&hrtc);

			break;

		case 'I': // get time
			HAL_RTC_GetTime(&hrtc,time,RTC_FORMAT_BCD);
			memcpy(return_value, uart_command, 2);
			memcpy(return_value+2,comma,1);
			itoa((time->Hours),temp_time_var,10  );
			memcpy(return_value+strlen((char*)return_value),temp_time_var,strlen(temp_time_var));
			memcpy(return_value+strlen((char*)return_value),comma,1 );
			itoa((time->Minutes),temp_time_var,10  );
			memcpy(return_value+strlen((char*)return_value),temp_time_var,strlen(temp_time_var));
			itoa((time->Seconds),temp_time_var,10  );
			memcpy(return_value+strlen((char*)return_value),comma,1 );
			memcpy(return_value+strlen((char*)return_value),temp_time_var,strlen(temp_time_var));
			memcpy(return_value+strlen((char*)return_value), endSimbol,2 );


			HAL_UART_Transmit_IT(&huart1,(uint8_t*)return_value, strlen((char*)return_value));
			break;

		case 'J': // set heating schedule
			if(auto_heating == 1){
				memcpy(return_value, uart_command, 2);
				memcpy(return_value+2, endSimbol,2 );
				HAL_UART_Transmit_IT(&huart1,return_value, strlen((char*)return_value));
				if(uart_command[3] == '1'){ // first heating schedule

					heating_info = strtok((char*)uart_command_copy, "$J,1");
					memcpy(heat_schedule1, heating_info, strlen((char*)heating_info) );
					memcpy(heat_schedule1+strlen((char*)heat_schedule1),comma,1 );

					heating_info = (strtok(NULL, ","));
					memcpy(heat_schedule1+strlen((char*)heat_schedule1), heating_info, strlen((char*)heating_info) );
					memcpy(heat_schedule1+strlen((char*)heat_schedule1),comma,1 );

					heating_info = (strtok(NULL, ",\r\n"));
					memcpy(heat_schedule1+strlen((char*)heat_schedule1), heating_info, strlen((char*)heating_info) );


				}
				else if(uart_command[3] == '2'){

					memcpy(heat_schedule2, heating_info, strlen((char*)heating_info) );
					memcpy(heat_schedule2+strlen((char*)heat_schedule2),comma,1 );

					heating_info = (strtok(NULL, ","));
					memcpy(heat_schedule2+strlen((char*)heat_schedule2), heating_info, strlen((char*)heating_info) );
					memcpy(heat_schedule2+strlen((char*)heat_schedule2),comma,1 );

					heating_info = (strtok(NULL, ",\r\n"));
					memcpy(heat_schedule2+strlen((char*)heat_schedule2), heating_info, strlen((char*)heating_info) );
				}
				else if(uart_command[3] == '3'){

					memcpy(heat_schedule3, heating_info, strlen((char*)heating_info) );
					memcpy(heat_schedule3+strlen((char*)heat_schedule3),comma,1 );

					heating_info = (strtok(NULL, ","));
					memcpy(heat_schedule3+strlen((char*)heat_schedule3), heating_info, strlen((char*)heating_info) );
					memcpy(heat_schedule3+strlen((char*)heat_schedule3),comma,1 );

					heating_info = (strtok(NULL, ",\r\n"));
					memcpy(heat_schedule3+strlen((char*)heat_schedule3), heating_info, strlen((char*)heating_info) );
					memcpy(heat_schedule3+strlen((char*)heat_schedule3),comma,1 );
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
			break;
		}
		memset(uart_command,0x00, 60);

		uart_counter = 0;
	}
	else if(uart_counter > 59 ){
		uart_counter = 0;
	}
}
