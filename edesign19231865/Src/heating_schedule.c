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
//	if(time->Hours > heating_schedule1)






}
