#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external VariabHAL_ADC_Stop_DMAles
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	rx_flag = 1;
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_buffer, 1);

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	adc_flag = 1;
	(&hadc2);
}

void  HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef * htim){
	tim3_flag = 1;
}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
rtcSecFlag = 1; // Flag to indicate 1 second period
}



