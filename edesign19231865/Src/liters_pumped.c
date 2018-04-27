#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;


void liters_pumped(){

	tim3_now = htim3.Instance->CNT; // timer value

	// register auto-reload value: 65535

	if(tim3_prev - tim3_now  > 0 && valve_trig == 0){
		if( (52 + tim3_now)-tim3_prev > 52 && valve_trig == 0){
			tim3_prev = tim3_now;
			water_acc+=100;
			valve_trig =1;
			sprintf(total_water,"%lu", water_acc);
		}
	}
	else if(tim3_now - tim3_prev > 52 && valve_trig == 0){
		tim3_prev = tim3_now;
		water_acc+=100;
		valve_trig = 1;
		sprintf(total_water,"%lu", water_acc);
	}

	else if (tim3_prev - tim3_now  > 0 && valve_trig == 1){
		if( (52 + tim3_now) - tim3_prev > 52 && valve_trig == 1){
			tim3_prev = tim3_now;
			water_acc+=100;
			sprintf(total_water,"%lu", water_acc);
			valve_trig = 0;
		}
	}
	else if(tim3_now - tim3_prev > 52 && valve_trig == 1){
		tim3_prev = tim3_now;
		water_acc+=100;
		sprintf(total_water,"%lu", water_acc);
		valve_trig = 0;
	}

}