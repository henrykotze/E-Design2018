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




void write2Flash(){

	if(log_counter <= 100){
		log_empty = 0;
		HAL_RTC_GetTime(&hrtc,time,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,date,RTC_FORMAT_BIN);

		// Identifier
		memcpy(flash_stored+strlen((char*)flash_stored),loggingIdentifier,strlen(loggingIdentifier));
		memcpy(flash_stored+strlen((char*)flash_stored),comma,1 );

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

//		sizeoflogging = strlen((char*)flash_stored)/64;


		if(log_counter == 0){
//			HAL_FLASH_Unlock();
//			pEraseInit->NbPages = 1;
//			pEraseInit->PageAddress = (uint32_t)(0x08008000);
//			pEraseInit->TypeErase = (uint32_t)FLASH_TYPEERASE_PAGES;

//			HAL_FLASHEx_Erase(pEraseInit,flash_error);
//			HAL_FLASH_Lock();

			HAL_FLASH_Unlock();
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008800, *((uint64_t*)(flash_stored)) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008808, *((uint64_t*)(flash_stored)+1) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008810, *((uint64_t*)(flash_stored)+2) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008818, *((uint64_t*)(flash_stored)+3) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008820, *((uint64_t*)(flash_stored)+4) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008828, *((uint64_t*)(flash_stored)+5) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008830, *((uint64_t*)(flash_stored)+6) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008838, *((uint64_t*)(flash_stored)+7) );
			HAL_FLASH_Lock();
		}
		else{
			HAL_FLASH_Unlock();
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008800+64*log_counter, *((uint64_t*)(flash_stored)) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008808+64*log_counter, *((uint64_t*)(flash_stored)+1) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008810+64*log_counter, *((uint64_t*)(flash_stored)+2) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008818+64*log_counter, *((uint64_t*)(flash_stored)+3) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008820+64*log_counter, *((uint64_t*)(flash_stored)+4) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008828+64*log_counter, *((uint64_t*)(flash_stored)+5) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008830+64*log_counter, *((uint64_t*)(flash_stored)+6) );
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, 0x08008838+64*log_counter, *((uint64_t*)(flash_stored)+7) );
			HAL_FLASH_Lock();
		}

	}

			memset(flash_stored, 0x00, 50);


			log_counter += 1;



}


void logPosition(){
	uint32_t* mem = (uint32_t*)(0x08008800);
	while(*mem != 0xFFFFFFFF){
		log_counter += 1;
		mem = (uint32_t*)(0x08008800 + 64*log_counter);
		log_empty = 0;

	}




}
