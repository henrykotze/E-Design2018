#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;
extern RTC_HandleTypeDef hrtc;


void heating_scheduling(){


	if(auto_heating == 1){
		HAL_RTC_GetTime(&hrtc,time,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,date,RTC_FORMAT_BIN);


		// checking heating schedule 1
		if( (time->Hours - heating_schedule[0].Hours) > 0 && (time->Hours - heating_schedule[1].Hours) < 0){
			heater_state = heater_ON;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		}

		else if( (time->Hours - heating_schedule[0].Hours == 0 || time->Hours - heating_schedule[1].Hours == 0 )
				&& ( (time->Minutes - heating_schedule[0].Minutes > 0) && (time->Minutes - heating_schedule[1].Minutes < 0) ) ){
			heater_state = heater_ON;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		}
		else if( (time->Hours - heating_schedule[0].Hours == 0 || time->Hours - heating_schedule[1].Hours == 0 )
				&& ( (time->Minutes - heating_schedule[0].Minutes == 0) || (time->Minutes - heating_schedule[1].Minutes == 0) )
				&& ( (time->Seconds - heating_schedule[0].Seconds > 0) && (time->Seconds - heating_schedule[1].Seconds < 0) ) ){
			heater_state = heater_ON;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		}

		// checking schedule 2

		else if( (time->Hours - heating_schedule[2].Hours) > 0 && (time->Hours - heating_schedule[3].Hours) < 0){
					heater_state = heater_ON;
					HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		}

		else if( (time->Hours - heating_schedule[2].Hours == 0 || time->Hours - heating_schedule[3].Hours == 0 )
				&& ( (time->Minutes - heating_schedule[2].Minutes > 0) && (time->Minutes - heating_schedule[3].Minutes < 0) ) ){
			heater_state = heater_ON;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		}
		else if( (time->Hours - heating_schedule[2].Hours == 0 || time->Hours - heating_schedule[3].Hours == 0 )
				&& ( (time->Minutes - heating_schedule[2].Minutes == 0) || (time->Minutes - heating_schedule[3].Minutes == 0) )
				&& ( (time->Seconds - heating_schedule[2].Seconds > 0) && (time->Seconds - heating_schedule[3].Seconds < 0) ) ){
			heater_state = heater_ON;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		}
		// checking schedule 3
		else if( (time->Hours - heating_schedule[4].Hours) > 0 && (time->Hours - heating_schedule[5].Hours) < 0){
			heater_state = heater_ON;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		}

		else if( (time->Hours - heating_schedule[4].Hours == 0 || time->Hours - heating_schedule[5].Hours == 0 )
				&& ( (time->Minutes - heating_schedule[4].Minutes > 0) && (time->Minutes - heating_schedule[5].Minutes < 0) ) ){
			heater_state = heater_ON;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		}
		else if( (time->Hours - heating_schedule[4].Hours == 0 || time->Hours - heating_schedule[5].Hours == 0 )
				&& ( (time->Minutes - heating_schedule[4].Minutes == 0) || (time->Minutes - heating_schedule[5].Minutes == 0) )
				&& ( (time->Seconds - heating_schedule[4].Seconds > 0) && (time->Seconds - heating_schedule[5].Seconds < 0) ) ){
			heater_state = heater_ON;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		}
		else{
			heater_state = heater_OFF;
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
		}
	}
}


void heating_control(){
	if(geyser_temp_int - *set_temp > 2.5f || *set_temp - geyser_temp_int > 2.5f){
		heater_state = heater_ON;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	}
}
