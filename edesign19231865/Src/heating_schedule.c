#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;



void heating_scheduling(){
	//HAL_RTC_GetTime(&hrtc,time,RTC_FORMAT_BIN);

	// checking heating schedule 1
	if(time->Hours > heating_schedule[0].Hours){
		if(time->Minutes > heating_schedule[0].Minutes){
			if(time->Seconds > heating_schedule[0].Seconds){
				// switch on
			}
			else{}
		}
	}
	// heating schedule 2
	if(time->Hours > heating_schedule[1].Hours){
		if(time->Minutes > heating_schedule[1].Minutes){
			if(time->Seconds > heating_schedule[1].Seconds){
				// switch on
			}
			else{}
		}
	}

	// heating schedule 3
	if(time->Hours > heating_schedule[2].Hours){
		if(time->Minutes > heating_schedule[2].Minutes){
			if(time->Seconds > heating_schedule[3].Seconds){
				// switch on
			}
			else{}
		}
	}






	}
