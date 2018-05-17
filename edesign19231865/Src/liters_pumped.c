#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;


void liters_pumped(){

	if(valve_timer == 5){
		pump_flag = 0;
		valve_timer = 0;
		water_acc+=100;
		sprintf(total_water,"%lu", water_acc);

	}
}
