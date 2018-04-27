#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;


void adc_comms(){

	adc_raw_voltage =  0;
	adc_raw_current =	0;
	raw_ambient_temp = ADC1_buffer[0];
	raw_geyser_temp = ADC1_buffer[1];


	//Converting Voltage
	adc_buffer_voltage = (pow((adc_raw_voltage-2072.202)/0.008629,2))+adc_buffer_voltage;

	//Converting Current
	adc_buffer_current = (pow((adc_raw_current-2072.202)/0.14603,2))+adc_buffer_current;

	//Converting Ambient temperature
	if( (raw_ambient_temp-615)/12.3 < 100){
		raw_ambient_temp =(raw_ambient_temp-615)/12.3;
		sprintf(ambient_temp,"%lu", raw_ambient_temp);
	}
	//Converting Geyser Temperature
	if( (raw_geyser_temp-615)/12.3 < 100){
		raw_geyser_temp = (raw_geyser_temp-615)/12.3;
		sprintf(geyser_temp,"%lu", raw_geyser_temp);
	}

	adc_counter += 1;
	if(adc_counter == 200){
		*voltage_int_rms = sqrt(adc_buffer_voltage/200);
		*current_int_rms = sqrt(adc_buffer_current/200);
		sprintf(voltage_rms,"%lu", *voltage_int_rms);
		sprintf(current_rms,"%lu", *current_int_rms);
		adc_counter = 0;

		adc_buffer_voltage = 0;
		adc_buffer_current = 0;
	}
	HAL_ADC_Stop_DMA(&hadc2);
}
