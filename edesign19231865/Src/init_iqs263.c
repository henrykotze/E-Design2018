#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_flash.h"
// external Variables
//extern TIM_HandleTypeDef htim2;
//extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;
extern RTC_HandleTypeDef hrtc;
extern I2C_HandleTypeDef hi2c1;

//unsigned char sliderCoords;                     // variable identified with a Slide event
//unsigned char data_buffer[30];
//unsigned char events = 0;                       // variable identified with all events
int init_iqs263(){
	// READING DEVICE INFORMATION
//	 data_buffer[0] = SYSTEM_FLAGS_VAL;
	 while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	 uint8_t sysflag_byte[] = {0};
	 HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, (uint8_t)SYS_FLAGS, I2C_MEMADD_SIZE_8BIT,  sysflag_byte, 1,50);
	 while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};

	 	HAL_Delay(42);
	    // Set active channels
	 data_buffer[0] = ACTIVE_CHS;
	 while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	 HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, ACTIVE_CHANNELS, I2C_MEMADD_SIZE_8BIT,  data_buffer, 1,50);
	 while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	 HAL_Delay(42);
	 // Setup touch and prox thresholds for each channel
	 data_buffer[0] = PROX_THRESHOLD;
	 data_buffer[1] = TOUCH_THRESHOLD_CH1;
	 data_buffer[2] = TOUCH_THRESHOLD_CH2;
	 data_buffer[3] = TOUCH_THRESHOLD_CH3;
	 data_buffer[4] = MOVEMENT_THRESHOLD;
	 data_buffer[5] = RESEED_BLOCK;
	 data_buffer[6] = HALT_TIME;
	 data_buffer[7] = I2C_TIMEOUT;

	 while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	 HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, THRESHOLDS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 8,50);
	 while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	 HAL_Delay(42);

	// Set the ATI Targets (Target Counts)
	data_buffer[0] = ATI_TARGET_TOUCH;
	data_buffer[1] = ATI_TARGET_PROX;
	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, TIMINGS_AND_TARGETS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 2,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);
	// Set the BASE value for each channel
	data_buffer[0] = MULTIPLIERS_CH0;
	data_buffer[1] = MULTIPLIERS_CH1;
	data_buffer[2] = MULTIPLIERS_CH2;
	data_buffer[3] = MULTIPLIERS_CH3;

	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, MULTIPLIERS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 4,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);

//	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1()){}; // Waiting for device
//	HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 5,50);
//	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};

	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 5,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);
	// Setup prox settings
//	data_buffer[0] = 0;
	data_buffer[0] = PROXSETTINGS0_VAL;
	data_buffer[1] = PROXSETTINGS1_VAL;
//	data_buffer[2] = 8;
	data_buffer[2] = PROXSETTINGS2_VAL;
	data_buffer[3] = PROXSETTINGS3_VAL;
	data_buffer[4] = EVENT_MASK_VAL;


	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 5,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);

	//reading prox Settings

//	data_buffer[0] = 0;
//	data_buffer[1] = 0;
//	data_buffer[2] = 0;
//	data_buffer[3] = 0;
//	data_buffer[4] = 0;

	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 5,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);

    // Setup Compensation (PCC)
    data_buffer[0] = COMPENSATION_CH0;
    data_buffer[1] = COMPENSATION_CH1;
    data_buffer[2] = COMPENSATION_CH2;
    data_buffer[3] = COMPENSATION_CH3;

    while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
    HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, COMPENSATION, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 4,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);

	// Set timings on the IQS263
	data_buffer[0] = LOW_POWER;
	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, TIMINGS_AND_TARGETS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 1,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);
	// Set gesture timers on IQS263
	data_buffer[0] = TAP_TIMER;
	data_buffer[1] = FLICK_TIMER;
	data_buffer[2] = FLICK_THRESHOLD;
	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, GESTURE_TIMERS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 3,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);

	// Redo ati
	data_buffer[0] = 0x10;
	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 1,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);
	do
	    {
			HAL_Delay(10);
	        while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	        HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, SYS_FLAGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 1,50);
	        while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	        HAL_Delay(42);
	    }
	    while ((data_buffer[0] & 0b00000100) == 0b00000100);

	// read the error bit to determine if ATI error occured
	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1){}; // Waiting for device
	HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 2,50);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
	HAL_Delay(42);
	if ( (data_buffer[1] & 0x02) == 0x02){
		return -1;
	}
	return 1;
}

void handleEvents(void){

//	uint8_t recv_buffer[16];
//	uint8_t touch_bytes_buffer[2] = {0x03, 0x0};
	display_set_temp = 0;

//	 uint16_t detected_channel = 0;
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1);
		//select sysflags
//		uint8_t sysflag_buffer[] = {SYS_FLAGS, 0, 0, 0};
//	    HAL_I2C_Master_Sequential_Transmit_IT(&hi2c1, IQS263_ADD, sysflag_buffer, 1, I2C_FIRST_FRAME);
//	    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}
//
//		// Get sysflags byte
//	    HAL_I2C_Master_Sequential_Receive_IT(&hi2c1, (uint16_t)IQS263_ADD, &recv_buffer[1], 1, I2C_NEXT_FRAME);
//	    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}

		//select touch event
	    HAL_I2C_Master_Sequential_Transmit_IT(&hi2c1, IQS263_ADD, touch_bytes_buffer, 1, I2C_FIRST_FRAME);
	    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}

		// Get touch event byte
	    HAL_I2C_Master_Sequential_Receive_IT(&hi2c1, (uint16_t)IQS263_ADD, &recv_buffer[2], 1, I2C_LAST_FRAME);
	    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}



		//Part 2 coords
		// Select coord register
//		uint8_t coordinates_buffer[2] = {0x02};
//		HAL_I2C_Master_Sequential_Transmit_IT(&hi2c1, IQS263_ADD, coordinates_buffer, 1, I2C_FIRST_FRAME);
//	    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}
//
//		// Read coord register of 3 bytes
////
//
//	    HAL_I2C_Master_Sequential_Receive_IT(&hi2c1, (uint16_t)IQS263_ADD, &recv_buffer[4], 3, I2C_LAST_FRAME);
//	    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}



		if(recv_buffer[2]== 0x03) // most left position on slider
		{
			if(*set_temp - 1 >= 0 ){
				*set_temp -= 1;
				display_set_temp = 1;
			}
		}
		else if(recv_buffer[2]== 0x05)	// middle position on slider
		{
			display_set_temp = 1;
		}


		else if (recv_buffer[2]== 0x09)	// right most position on slider
		{
			if(*set_temp +1 <= 100){
				*set_temp += 1;
				display_set_temp = 1;
			}
		}
}






