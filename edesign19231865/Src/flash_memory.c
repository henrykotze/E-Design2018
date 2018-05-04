#include "functions.h"
#include "variables.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_flash.h"
// external Variables
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc2;
extern RTC_HandleTypeDef hrtc;


//#define memoryStartLoc (uint32_t*)0x0800 0000
//#define memoryStopLoc 0x0800 FFFF;


void write2Flash(){
	if(log_counter < 100){
		HAL_RTC_GetTime(&hrtc,time,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,date,RTC_FORMAT_BIN);
		// Time
		//hours
		itoa((time->Hours),temp_time_var,10  );
		memcpy(flash_stored+strlen((char*)flash_stored),temp_time_var,strlen(temp_time_var));
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );
		//minutes
		itoa((time->Minutes),temp_time_var,10  );
		memcpy(flash_stored+strlen((char*)flash_stored),temp_time_var,strlen(temp_time_var));
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );
		//seconds
		itoa((time->Seconds),temp_time_var,10  );
		memcpy(flash_stored+strlen((char*)flash_stored),temp_time_var,strlen(temp_time_var));
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );

		//current
		memcpy(flash_stored+strlen((char*)flash_stored),current_rms,strlen(current_rms));
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );
		//voltage
		memcpy(flash_stored+strlen((char*)flash_stored),voltage_rms,strlen(voltage_rms) );
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );
		//ambient temp
		memcpy(flash_stored+strlen((char*)flash_stored),ambient_temp,strlen(ambient_temp) );
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );
		// hot water temp
		memcpy(flash_stored+strlen((char*)flash_stored),geyser_temp,strlen(geyser_temp) );
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );
		// accumulated water
		memcpy(flash_stored+strlen((char*)flash_stored),total_water,strlen(total_water) );
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );
		// heating element
		memcpy(flash_stored+strlen((char*)flash_stored),heater_state,strlen(heater_state));
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );
		//vale state
		if(valve_state == valve_OPEN){
			memcpy(flash_stored+strlen((char*)flash_stored), valve_state,strlen(valve_state) -1);
		}
		else{
			memcpy(flash_stored+strlen((char*)flash_stored), valve_state,strlen(valve_state) );
		}

		memcpy(flash_stored+strlen((char*)flash_stored), endSimbol,2 );
		HAL_FLASH_Unlock();
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, 0x08000000, *((uint64_t*)flash_stored) );
		HAL_FLASH_Lock();
		memset(flash_stored, 0x00, 50);


		log_counter += 1;
	}
	else{
		log_counter = 0;
		log_full = 1;
	}


}


void readFlash(uint8_t log_num){






}
