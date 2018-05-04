#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;
extern RTC_HandleTypeDef hrtc;


#define memoryStartLoc 0x0800 0000;
#define memoryStopLoc 0x0800 FFFF;


void write2Flash(){




}


void readFlash(){






}
