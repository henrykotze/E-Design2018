/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define I2C_SCL_Pin GPIO_PIN_0
#define I2C_SCL_GPIO_Port GPIOC
#define I2C_SDA_Pin GPIO_PIN_1
#define I2C_SDA_GPIO_Port GPIOC
#define VOLTAGE_RMS_Pin GPIO_PIN_2
#define VOLTAGE_RMS_GPIO_Port GPIOC
#define CURRENT_RMS_Pin GPIO_PIN_3
#define CURRENT_RMS_GPIO_Port GPIOC
#define TOUCH_TOGGLE_Pin GPIO_PIN_0
#define TOUCH_TOGGLE_GPIO_Port GPIOA
#define TOUCH_TOGGLE_EXTI_IRQn EXTI0_IRQn
#define w_RDY_Pin GPIO_PIN_1
#define w_RDY_GPIO_Port GPIOA
#define s_RDY_Pin GPIO_PIN_4
#define s_RDY_GPIO_Port GPIOA
#define SEG_1_Pin GPIO_PIN_5
#define SEG_1_GPIO_Port GPIOA
#define SEG_2_Pin GPIO_PIN_6
#define SEG_2_GPIO_Port GPIOA
#define SEG_3_Pin GPIO_PIN_7
#define SEG_3_GPIO_Port GPIOA
#define AMBIENT_TEMP_Pin GPIO_PIN_2
#define AMBIENT_TEMP_GPIO_Port GPIOB
#define SEG_8_Digit_1_Pin GPIO_PIN_10
#define SEG_8_Digit_1_GPIO_Port GPIOB
#define VALVE_CONTROL_Pin GPIO_PIN_13
#define VALVE_CONTROL_GPIO_Port GPIOB
#define HEATER_CONTROL_Pin GPIO_PIN_14
#define HEATER_CONTROL_GPIO_Port GPIOB
#define GEYSER_TEMP_Pin GPIO_PIN_15
#define GEYSER_TEMP_GPIO_Port GPIOB
#define FLOW_TRIGGER_Pin GPIO_PIN_6
#define FLOW_TRIGGER_GPIO_Port GPIOC
#define FLOW_TRIGGER_EXTI_IRQn EXTI9_5_IRQn
#define SEG_5_Pin GPIO_PIN_7
#define SEG_5_GPIO_Port GPIOC
#define SEG_7_Pin GPIO_PIN_8
#define SEG_7_GPIO_Port GPIOA
#define SEG_6_Pin GPIO_PIN_9
#define SEG_6_GPIO_Port GPIOA
#define SEG_11_Digit_4_Pin GPIO_PIN_3
#define SEG_11_Digit_4_GPIO_Port GPIOB
#define SEG_9_Digit_2_Pin GPIO_PIN_4
#define SEG_9_Digit_2_GPIO_Port GPIOB
#define SEG_10_Digit_3_Pin GPIO_PIN_5
#define SEG_10_Digit_3_GPIO_Port GPIOB
#define SEG_4_Pin GPIO_PIN_6
#define SEG_4_GPIO_Port GPIOB
#define I2C_SCLB8_Pin GPIO_PIN_8
#define I2C_SCLB8_GPIO_Port GPIOB
#define I2C_SDAB9_Pin GPIO_PIN_9
#define I2C_SDAB9_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
