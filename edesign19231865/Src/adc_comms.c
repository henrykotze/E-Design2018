#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
//extern TIM_HandleTypeDef htim2;
//extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;


void adc_comms(){

	adc_raw_voltage =  ADC1_buffer[0];
	adc_raw_current =	ADC1_buffer[1];
	raw_ambient_temp = ADC1_buffer[2];
	raw_geyser_temp = ADC1_buffer[3];


	//Converting Voltage
	adc_buffer_voltage = ((float)(adc_raw_voltage-2059.908f)/0.008686f)*((float)(adc_raw_voltage-2059.908f)/0.008686f)+adc_buffer_voltage;

	//Converting Current
	adc_buffer_current = ((adc_raw_current-2059.908f)/0.1469f)*((adc_raw_current-2059.908f)/0.1469f)+adc_buffer_current;

	//Converting Ambient temperature
	if( (raw_ambient_temp-620.5f)/12.4f < 100){
		raw_ambient_temp = (raw_ambient_temp-620.4f)/12.4f;
		sprintf(ambient_temp,"%ld", raw_ambient_temp);
	}
	//Converting Geyser Temperature
	if( (raw_geyser_temp-620.5f)/12.4f < 100){
		raw_geyser_temp = (raw_geyser_temp-620.4f)/12.4f;
		geyser_temp_int = raw_geyser_temp;
		sprintf(geyser_temp,"%lu", raw_geyser_temp);
		sprintf(segment_val, "%lu", raw_geyser_temp);
	}
//	else{
//		raw_geyser_temp = (raw_geyser_temp-620.4f)/12.41f;
//		raw_geyser_temp = 50;
//		geyser_temp_int = 50;
//		sprintf(geyser_temp,"%lu", raw_geyser_temp);
//		sprintf(segment_val, "%lu", raw_geyser_temp);
//	}
	adc_counter += 1;
	if(adc_counter == 5000){
		*voltage_int_rms = sqrt(adc_buffer_voltage/5000.f);
		*current_int_rms = sqrt(adc_buffer_current/5000.f);
		sprintf(voltage_rms,"%lu", *voltage_int_rms);
		sprintf(current_rms,"%lu", *current_int_rms);

		adc_counter = 0;

		adc_buffer_voltage = 0;
		adc_buffer_current = 0;
	}

}
