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
	adc_buffer_voltage = ((float)(adc_raw_voltage-2072.202f)/0.008629f)*((float)(adc_raw_voltage-2072.202f)/0.008629f)+adc_buffer_voltage;

	//Converting Current
	adc_buffer_current = ((adc_raw_current-2072.202f)/0.14603f)*((adc_raw_current-2072.202f)/0.14603f)+adc_buffer_current;

	//Converting Ambient temperature
	if( (raw_ambient_temp-615.f)/12.3f < 100){
		raw_ambient_temp = (raw_ambient_temp-615.0f)/12.3f;
		sprintf(ambient_temp,"%ld", raw_ambient_temp);
	}
	//Converting Geyser Temperature
	if( (raw_geyser_temp-615.f)/12.3f < 100){
		raw_geyser_temp = (raw_geyser_temp-615.f)/12.3f;
		geyser_temp_int = raw_geyser_temp;
		sprintf(geyser_temp,"%lu", raw_geyser_temp);
		sprintf(segment_val, "%lu", raw_geyser_temp);
	}

	adc_counter += 1;
	if(adc_counter == 80){
		*voltage_int_rms = sqrt(adc_buffer_voltage/80.f);
		*current_int_rms = sqrt(adc_buffer_current/80.f);
		sprintf(voltage_rms,"%lu", *voltage_int_rms);
		sprintf(current_rms,"%lu", *current_int_rms);

		adc_counter = 0;

		adc_buffer_voltage = 0;
		adc_buffer_current = 0;
	}

}
