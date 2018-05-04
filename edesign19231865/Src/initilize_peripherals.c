
#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;
extern RTC_HandleTypeDef hrtc;

void init_peripherals(){

	//A
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET); 		// 7_SEG_1

	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);		// 7_SEG_3
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);		// 7_SEG_7
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);		// 7_SEG_6

	// B
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);		// D4
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);		// D2
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);		// D3
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);		// 7_SEG_4
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);		// D1
	// C
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);		// 7_SEG_5

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);		// Heater
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);		// Valve

	studentnumber = (uint8_t*)malloc(15);
	memset(studentnumber, 0x00, 15);

	return_value = (uint8_t*)malloc(50);
	memset(return_value, 0x00, 50);

	uart_command = (uint8_t*)malloc(60);
	memset(uart_command, 0x00, 60);

	uart_command_copy = (uint8_t*)malloc(60);
	memset(uart_command, 0x00, 60);


	set_temp = (uint8_t*)malloc(3);
	memset(set_temp, 0x00, 4);

	segment_val =set_temp;
	//	  memset(segment_val, 0x00, 4);

	ADC1_buffer = (uint32_t*)malloc(7*sizeof(uint32_t));
	memset(ADC1_buffer, 0x00, 7);

	ADC2_buffer = (uint32_t*)malloc(7*sizeof(uint32_t));
	memset(ADC2_buffer, 0x00, 7);

	voltage_rms =(char*)malloc(3*sizeof(char));
	memset(voltage_rms, 0x00, 3);

	current_rms =(char*)malloc(4*sizeof(char));
	memset(current_rms, 0x00, 4);

	total_water =(char*)malloc(20*sizeof(char));
	memset(total_water, 0x00, 20);
	sprintf(total_water,"%lu", water_acc);


	voltage_int_rms = (uint32_t*)malloc(4*sizeof(uint32_t));
	current_int_rms = (uint32_t*)malloc(4*sizeof(uint32_t));

	ambient_temp = (char*)malloc(4*sizeof(char));
	geyser_temp = (char*)malloc(4*sizeof(char));

	//HEATER
	heater_state = (char*)malloc(5*sizeof(char));
	heater_state = heater_OFF;

	//Valve
	valve_state = (char*)malloc(8*sizeof(char));
	valve_state = valve_CLOSE;

	// Heating schedule
	heat_schedule1 = (char*)malloc(15*sizeof(char));
	memset(heat_schedule1, 0x00, 15);
	heat_schedule2 = (char*)malloc(15*sizeof(char));
	memset(heat_schedule2, 0x00, 15);
	heat_schedule3 = (char*)malloc(15*sizeof(char));
	memset(heat_schedule3, 0x00, 15);

	heating_schedule_info[0] = heat_schedule1;
	heating_schedule_info[1] = heat_schedule2;
	heating_schedule_info[2] = heat_schedule3;

	heating_info = (char*)malloc(20*sizeof(char));
	memset(heating_info, 0x00, 10);

	heating_time_size = 0;


	// Initiliazing the RTC
	time = malloc(6*sizeof(uint32_t));
	memset(time, 0x00, 6);
//
	time->Hours = 0x0;
	time->Minutes = 0x0;
	time->Seconds = 0x0;
	time->DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	time->StoreOperation = RTC_STOREOPERATION_RESET;

	date = malloc(sizeof(uint32_t));
	memset(date,0x00,1);

	date->WeekDay = RTC_WEEKDAY_MONDAY;
	date->Month = RTC_MONTH_JANUARY;
	date->Date = 0x1;
	date->Year = 0x0;




	new_time = malloc(6*sizeof(uint32_t));
	memset(new_time, 0x00, 6);

	temp_time_var = (char*)malloc(3*sizeof(uint8_t));
	memset(temp_time_var, 0x00, 3);


	// get time
	HAL_RTC_GetTime(&hrtc, time, RTC_FORMAT_BCD);

	HAL_TIM_Base_Start_IT(&htim2);
	//HAL_TIM_Base_Start_IT(&htim3);
	// p696 on HAL & Low level drivers

	//	HAL_ADCEx_Calibration_Start(&hadc1,ADC_SINGLE_ENDED);

}
