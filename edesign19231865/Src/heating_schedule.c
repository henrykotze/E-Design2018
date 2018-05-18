#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
extern RTC_HandleTypeDef hrtc;


void heating_scheduling(){


	if(auto_heating == 1){
//		HAL_RTC_GetTime(&hrtc,timeOfRTC,RTC_FORMAT_BIN);
//		HAL_RTC_GetDate(&hrtc,date,RTC_FORMAT_BIN);
		RTC_in_seconds = timeOfRTC->Hours*3600 + timeOfRTC->Minutes*60 +timeOfRTC->Seconds;

		// heating schedule 1
		if( (time_intervals[1] > time_intervals[0] )){ // no overlapping days
			if (RTC_in_seconds > time_intervals[0] && RTC_in_seconds < time_intervals[1]){
				heating_control();
			}
		}
		else if((time_intervals[1] - time_intervals[0] ) != 0){	// overlapping
			if( !( (RTC_in_seconds>time_intervals[1]) && (RTC_in_seconds< time_intervals[0]) )){
				heating_control();
			}
		}
		// heating schedule 2
		if( (time_intervals[3] > time_intervals[2])){ // no overlapping days
			if (RTC_in_seconds > time_intervals[2] && RTC_in_seconds < time_intervals[3]){
				heating_control();
			}
		}
		else if( (time_intervals[3] - time_intervals[2]) != 0 ){	// overlapping
			if( !(RTC_in_seconds>time_intervals[3] && RTC_in_seconds< time_intervals[2] )){
				heating_control();
			}
		}
		// heating schedule 3
		if( (time_intervals[5] > time_intervals[4] )){ // no overlapping days
			if ( (RTC_in_seconds > time_intervals[4]) && RTC_in_seconds < time_intervals[5]){
				heating_control();
			}
		}
		else if( (time_intervals[5] - time_intervals[4] ) != 0){	// overlapping
			if( !(RTC_in_seconds>time_intervals[5] && RTC_in_seconds< time_intervals[4] )){
				heating_control();
			}
		}
	}
}


void heating_control(){

	if( (heater_state == heater_OFF) && !(geyser_temp_int < (*set_temp - 4) ) && !(geyser_temp_int > (*set_temp+4 ))){
		heater_state = heater_OFF;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	}
	else if( (heater_state == heater_OFF) && !(geyser_temp_int < (*set_temp - 4) ) && (geyser_temp_int > (*set_temp+4 ))){
		heater_state = heater_OFF;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	}
	else if( (heater_state == heater_OFF) && (geyser_temp_int < (*set_temp - 4)) && !(geyser_temp_int > (*set_temp+4 ))){
		heater_state = heater_ON;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	}
	else if( (heater_state == heater_ON) && !(geyser_temp_int < (*set_temp - 4 )) && !(geyser_temp_int > (*set_temp+4 ))){
		heater_state = heater_ON;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	}
	else if( (heater_state == heater_ON) && !(geyser_temp_int < (*set_temp - 4 )) && (geyser_temp_int > (*set_temp+4))){
		heater_state = heater_OFF;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	}
	else if( (heater_state == heater_ON) && (geyser_temp_int < (*set_temp - 4)) && !(geyser_temp_int > (*set_temp+4 ))){
		heater_state = heater_ON;
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	}
}
