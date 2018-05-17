#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external VariabHAL_ADC_Stop_DMAles
//extern TIM_HandleTypeDef htim2;
//extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	rx_flag = 1;
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_buffer, 1);

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	adc_flag = 1;
}

//void  HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef * htim){
////	tim3_flag = 1;
//}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
rtcSecFlag = 1; // Flag to indicate 1 second period
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){
	rtcSecFlag = 1; // Flag to indicate 1 second period
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
	rtcSecFlag = 1; // Flag to indicate 1 second period

}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c){
	rtcSecFlag = 1; // Flag to indicate 1 second period

}
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//
////	tim2_flag = 0;
////	pump_flag = 0;
////	HAL_TIM_Base_Stop_IT(&htim2);
//}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_6){
		pump_flag = 1;
	}
}
