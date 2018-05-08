#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_flash.h"
#include "IQS263.h"

// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;
extern RTC_HandleTypeDef hrtc;
extern I2C_HandleTypeDef hi2c1;



//static int PROX_THRESHOLD	 = 0x10; //0x10
//static int TOUCH_THRESHOLD = 0x20;
//static int TOUCH_THRESHOLD_CH1 = 0x20; //0x20
//static int TOUCH_THRESHOLD_CH2 = 0x20; //0x20
//static int TOUCH_THRESHOLD_CH3 = 0x20; //0x20
//
//static int MOVEMENT_THRESHOLD = 0x03;
//static int RESEED_BLOCK = 0x00;
//static int HALT_TIME = 0x00;
//static int I2C_TIMEOUT = 0x04;
//
//
//
//uint8_t CH1_Event=0;
//uint8_t CH2_Event=0;
//uint8_t CH3_Event=0;
//uint8_t IQS263_Threshold[8];
//
//
//
///**
// *
// * @param NONE
// * @return NONE
//
//*/
//int Init_IQS263()
//{
//	//GPIO_InitTypeDef GPIO_InitStruct;
//
//	/* GPIO Ports Clock Enable */
//
//	//__HAL_RCC_GPIOA_CLK_ENABLE();
//
//	/*Configure GPIO pin : SD_CS_Pin */
////	GPIO_InitStruct.Pin = GPIO_PIN_1;
////	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
////	GPIO_InitStruct.Pull = GPIO_NOPULL;
////	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
////	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
////  	uint8_t data_buffer[8]={0};
////	 HAL_Delay(10);
//
//
//	/*....................READING SYSTEM FLAGS..........................*/
//	 while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1){}
//
//		HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, (uint8_t)SYS_FLAGS, I2C_MEMADD_SIZE_8BIT,  data_buffer, 2,50);
//		while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//		{
//		}
//
//
//	/*....................READING DEVICE INFO..........................*/
//	 while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1){}
//
//		HAL_I2C_Mem_Read(&hi2c1, IQS263_ADD,( uint8_t ) DEVICE_INFO, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0],2,	70);
//		while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//		{
//		}
//
//		/*....................READING ACTIVE CHANNELS..........................*/
//
//		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1);
//
//		HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, ACTIVE_CHANNELS, I2C_MEMADD_SIZE_8BIT,  data_buffer, 1,60);
//		while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//		{
//		}
//
//		/*....................READING THRESHOLDS..........................*/
//
//		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1);
//
//		HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, THRESHOLDS, I2C_MEMADD_SIZE_8BIT,  IQS263_Threshold, 8,60);
//		while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//		{
//		}
//
//		/*....................WRITING THRESHOLDS..........................*/
//
//	IQS263_Threshold[0]= PROX_THRESHOLD	  ; //0x10
//	IQS263_Threshold[1]= TOUCH_THRESHOLD  ;
//	IQS263_Threshold[2]= TOUCH_THRESHOLD_CH1  ; //0x20
//	IQS263_Threshold[3]= TOUCH_THRESHOLD_CH2  ; //0x20
//	IQS263_Threshold[4]= TOUCH_THRESHOLD_CH3  ; //
//	IQS263_Threshold[5]= 14  ; //
//	IQS263_Threshold[6]= HALT_TIME ;
//	IQS263_Threshold[7]=250;
//
//		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1);
//
//		HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, THRESHOLDS, I2C_MEMADD_SIZE_8BIT,  IQS263_Threshold, 8,60);
//	  while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//		{
//		}
//		while (HAL_I2C_IsDeviceReady(&hi2c1, IQS263_ADD, 10, 300) == HAL_TIMEOUT);
//
//		/*....................READING THRESHOLDS..........................*/
//
//		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1);
//
//		HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, THRESHOLDS, I2C_MEMADD_SIZE_8BIT,  IQS263_Threshold, 8,60);
//	 	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//		{
//		}
//		while (HAL_I2C_IsDeviceReady(&hi2c1, IQS263_ADD, 10, 300) == HAL_TIMEOUT)
//
//		/*....................READING PROXI SETTING..........................*/
//
//		 while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1);
//
//	   HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  data_buffer, 5,60);
//	   while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//		 {
//		 }
//		 while (HAL_I2C_IsDeviceReady(&hi2c1, IQS263_ADD, 10, 300) == HAL_TIMEOUT);
//
//		/*....................WRITING PROXI SETTING..........................*/
//
//	  while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1){}
//
//		  data_buffer[0]=0;
//	  	  data_buffer[2]=8;
//
//		HAL_I2C_Mem_Write( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  data_buffer, 5,	60);
//	 while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
//		{
//		}
//		while (HAL_I2C_IsDeviceReady(&hi2c1, IQS263_ADD, 10, 300) == HAL_TIMEOUT){}
//
//
//
//
//
//
//		data_buffer[0] = 0x10;
//		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1){}; // Waiting for device
//		HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 1,50);
//		while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
//
//		do
//		    {
//				HAL_Delay(10);
//		        while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1){}; // Waiting for device
//		        HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, SYS_FLAGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 1,50);
//		        while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
//		    }
//		    while ((data_buffer[0] & 0b00000100) == 0b00000100);
//
//		// read the error bit to determine if ATI error occured
//		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1){}; // Waiting for device
//		HAL_I2C_Mem_Read( &hi2c1, IQS263_ADD, PROX_SETTINGS, I2C_MEMADD_SIZE_8BIT,  &data_buffer[0], 2,50);
//		while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){};
//
//		if ( (data_buffer[1] & 0x02) == 0x02){
//			return -1;
//		}
//		return 1;
//
//
//
//
//
//
//
//
//}

/**
 *
 * @param NONE
 * @return NONE

*/


void IQS263_READ_TOUCH_Events(){

	uint8_t data[3]={0};
/*....................READING TOUCH EVENTS..........................*/

//	while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1)
////HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
//
//		HAL_I2C_Mem_Read(&hi2c1, IQS263_ADD, TOUCH_BYTES, I2C_MEMADD_SIZE_8BIT,data,3,70);
//	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY){}
//	while (HAL_I2C_IsDeviceReady(&hi2c1, IQS263_ADD, 10, 300) == HAL_TIMEOUT){}
//
//	CH1_Event=data[0]&0x02;
//    CH2_Event=data[0]&0x04;
//    CH3_Event=data[0]&0x08;
//    HAL_UART_Transmit_IT(&huart1, data, 3);

}

void CommsIQS_start(void){







}

