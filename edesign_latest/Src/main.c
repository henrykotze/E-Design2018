/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"
#include <string.h>
#include <stdlib.h>

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
uint8_t rx_flag = 0;
uint8_t rx_buf[40];
uint8_t rx_buffer;
uint8_t rx_val;
uint8_t uart_counter = 0;
uint8_t* uart_command = rx_buf;
char studentnumber1[] = {'1', '9','2','3','1','8','6','5'};
char endSimbol[] = {'\r', '\n'};
char comma[] = {','};

unsigned char stdnt[15];
unsigned char* studentnumber = stdnt;

uint8_t return_val[15];
uint8_t* return_value = return_val;

char* time = "00:00:00";

uint8_t auto_heating = 0;

uint8_t temperature[4];
uint8_t* set_temp = temperature;
uint8_t sizeOfTemp = 0;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_buffer, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


  /* USER CODE END WHILE */
//	  HAL_UART_Receive_IT(&huart1, rx_buffer, 1);
		//HAL_UART_Receive_IT(&huart1, &rx_buffer, 1);
  /* USER CODE BEGIN 3 */
	  if(rx_flag == 1){
		  HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_buffer, 1);
		  rx_flag = 0;
		  uart_command[uart_counter] = rx_buffer;
		  uart_counter += 1;



			  if(uart_command[0] == '$' && uart_command[uart_counter-1] == '\n' && uart_command[uart_counter - 2] == '\r' && uart_counter > 2){
//					 return_val[0] = uart_command[0];
//					 return_val[1] = uart_command[1];
//					 return_val[2] = uart_command[uart_counter -2];
//					 return_val[3] = uart_command[uart_counter -1];

					 switch(uart_command[1]){

					 case  'A': // Request Serial number

						 memcpy(studentnumber, uart_command, 2 );
						 memcpy(studentnumber+2,comma,1);
						 memcpy(studentnumber+3 ,studentnumber1,sizeof(studentnumber1) );
						 memcpy(studentnumber+11,endSimbol,sizeof(endSimbol));
						 HAL_UART_Transmit(&huart1, ((uint8_t*)studentnumber), 13, 10);
						 //HAL_UART_Transmit(&huart1, ((uint8_t*)studentnumber2), sizeof(studentnumber2), 10);
						 break;

					 case 'B':
						memcpy(return_value, uart_command, 2);
						memcpy(return_value+2, endSimbol,2 );
						HAL_UART_Transmit(&huart1, return_val, sizeof(return_value), 1000);
						 if(uart_command[2]=='0'){
						 }
						 else if(uart_command[2] == '1'){
						 }
						 break;

					 case 'C':
						 memcpy(return_value, uart_command, 2);
						 memcpy(return_value+2, endSimbol,2 );
						 HAL_UART_Transmit(&huart1, return_val, sizeof(return_value), 1000);
						 if(uart_command[2]=='0'){
							auto_heating = 0;	// auto heating off
						 }
						 else if(uart_command[2] == '1'){
							auto_heating = 1;	// auto heating on
						 }
						 break;

					 case 'D':
						 memcpy(return_value, uart_command, 2);
						 memcpy(return_value+2, endSimbol,2 );
						 HAL_UART_Transmit(&huart1, return_val, sizeof(return_value), 1000);
						 if(auto_heating == 0){	// if auto heating off
							 if(uart_command[2]=='0'){

							 }
							 else if(uart_command[2] == '1'){
								 // do something
							 }
						 }
						 break;

					 case 'E': //Enable/Disble logging to flash memory
						 memcpy(return_value, uart_command, 2);
						 memcpy(return_value+2, endSimbol,2 );
						 HAL_UART_Transmit(&huart1, return_val, sizeof(return_value), 1000);
						 if(uart_command[2]=='0'){ // logging disable
							 //do something
						 }
						 else if(uart_command[2] == '1'){ // logging enable
							 // do something
						 }
						 break;

					 case 'F'://Set new temperature set-point
						 memcpy(return_value, uart_command,2);
						 memcpy(return_value+2,endSimbol, 2);
						HAL_UART_Transmit(&huart1,(uint8_t*)return_value, sizeof(return_value), 1000);

						 sizeOfTemp = uart_counter - 5;
						 memcpy(set_temp, uart_command+3, sizeOfTemp * sizeof(uint8_t) );

						break;

					 case 'G':
						 // transmit temperature
						 memcpy(return_value, uart_command, 2);
						 memcpy(return_value+2, comma, 1);
						 memcpy(return_value+3, set_temp, sizeOfTemp * sizeof(uint8_t));
						 memcpy(return_value+3+sizeOfTemp * sizeof(uint8_t),endSimbol, 2);

						HAL_UART_Transmit(&huart1,(uint8_t*)return_value, (2+3+sizeOfTemp)*sizeof(uint8_t), 1000);
						 break;

					 case 'H': //set time
						HAL_UART_Transmit(&huart1,(uint8_t*)return_val, sizeof(return_value)+1, 1000);
						 break;

					 case 'I': // get time
						HAL_UART_Transmit(&huart1,(uint8_t*)time, sizeof(time), 1000);
						 break;

					 case 'J': // set heating schedule
						HAL_UART_Transmit(&huart1,(uint8_t*)return_val, sizeof(return_val), 1000);
						 break;

					 case 'K':
						 // send telematary
						 break;

					 case 'L': // Request log Entry
						 // do something
						 break;

					 }
					memset(uart_command,0x00, 40);
					memset(return_value,0x00, 15);
					uart_counter = 0;
			  }

	//
			  else if(uart_counter > 39 ){
				  uart_counter = 0;
			  }
		 // HAL_UART_Receive_IT(&huart1, &rx_buffer, 1);


	  }

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Pinout Configuration
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
		rx_flag = 1;
	  //HAL_UART_Transmit_IT(&huart1, (uint8_t*)&rx_buffer, 1);
		//HAL_UART_Receive_IT(&huart1, &rx_buffer, 1);

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
