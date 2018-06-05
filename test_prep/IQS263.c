/*
 * IQS263.c
 *
 *  Created on: 10 May 2018
 *      Author: 18225713
 */

/* INCLUDES */
#include "IQS263.h"

/* DEFINES & CONSTANTS */
// device addresses
#define SLIDER_ADDR 0x44 // linear slider address
#define WHEEL_ADDR 0x45 // rotary slider address

// IQS263 device register & memory map addresses
#define ADDR_DEVI_INFO 0x00 // device information (R)
#define ADDR_SYS_FLAGS 0x01 // system flags (RW)
#define ADDR_COORD 0x02 // coordinates (R)
#define ADDR_TOUCH 0x03 // touch bytes (R)
#define ADDR_COUNTS 0x04 // counts (R)
#define ADDR_LTA 0x05 // LTA (R)
#define ADDR_DELTAS 0x06 // deltas (R)
#define ADDR_MULTIPL 0x07 // multipliers (RW)
#define ADDR_COMPENS 0x08 // conpensation (RW)
#define ADDR_PROXSET 0x09 // prox settings (RW)
#define ADDR_THRESH 0x0A // thresholds (RW)
#define ADDR_TIM_TARG 0x0B // timings & targets (RW)
#define ADDR_GEST_TIM 0x0C // gesture timers (RW)
#define ADDR_ACT_CH 0x0D // active channels (RW)

#define P_MAX 255
#define SUM_DELTA_MIN 50
#define T_INPUT_MIN 30
#define T_INPUT_MAX 100


/* VARIABLES */
uint16_t slider_address = SLIDER_ADDR;
uint8_t prod_num;
uint8_t ver_num;
uint8_t sysflags;
uint8_t events;


/* PRIVATE FUNCTION PROTOTYPES */

/* PUBLIC FUNCTIONS */
void IQS263_run (I2C_HandleTypeDef* hi2c)
{
   HAL_StatusTypeDef I2C_State = HAL_BUSY;
   uint32_t timeout = 1;
   static uint8_t curr_state_count = 0;

   uint8_t pData[30];
   uint16_t data_size;

   uint8_t ATIbusy;
   uint8_t ATIerr;

   uint16_t delta_C1, delta_C2, delta_C3, sum_delta;
   uint8_t position;

   static uint32_t starttime;
   uint32_t curr_time;

   switch (IQS263_state)
   {
      case POR:
         /* Default streaming mode
          * Clear "show reset"
          * */
         I2C_State = IQS263_I2C_Capture(hi2c);

         if (I2C_State == HAL_OK)
         {
            pData[0] = ADDR_SYS_FLAGS;
            pData[1] = 0x00;
            data_size = 2;

            I2C_State = IQS263_I2C_Master_Transmit(hi2c, (slider_address << 1),
                                                    pData, data_size, timeout);
         }
         if (I2C_State == HAL_OK)
         {
            IQS263_I2C_Release(hi2c);
            IQS263_state = init_IQS263;
            curr_state_count = 0;
         } else
         {
            curr_state_count++;
         }



      break;
      case init_IQS263:
         /* Event mode
          * Redo-ATI
          * */
         I2C_State = IQS263_I2C_Capture(hi2c);

         if (I2C_State == HAL_OK)
         {
            pData[0] = ADDR_PROXSET;
            pData[1] = 0b00010000;
            pData[2] = 0b01011101;
//            pData[3] = 0x00;
//            pData[4] = 0x00;
//            pData[5] = 0xFF;
            data_size = 3;

            I2C_State = IQS263_I2C_Master_Transmit(hi2c, (slider_address << 1),
                                                    pData, data_size, timeout);
         }
         if (I2C_State == HAL_OK)
         {
            IQS263_I2C_Release(hi2c);
            IQS263_state = ATI;
            curr_state_count = 0;
         } else
         {
            curr_state_count++;
         }



      break;
      case ATI:
         I2C_State = IQS263_I2C_Capture(hi2c);

         if (I2C_State == HAL_OK)
         {
            pData[0] = ADDR_SYS_FLAGS;
            data_size = 1;
            I2C_State = IQS263_I2C_Master_Transmit(hi2c, (slider_address << 1),
                                                    pData, data_size, timeout);
         }

         if (I2C_State == HAL_OK)
         {
            memset(pData, 0xFF, 30);
            data_size = 2;

            I2C_State = IQS263_I2C_Master_Receive(hi2c, (slider_address << 1),
                                                   pData, data_size, timeout);

            if (I2C_State == HAL_OK)
            {
               sysflags = pData[0];
               events = pData[1];
            }
         }

         if (I2C_State == HAL_OK)
         {
            IQS263_I2C_Release(hi2c);

            ATIbusy = (sysflags >> 2) & 0b1;
            ATIerr = (sysflags >> 5) % 0b1;

            if ((!ATIbusy) && (ATIerr))
            {
               /* ATI event 2
                * ATI_busy = 0
                * ATI_error = 1
                * */
               IQS263_state = ATI_error;
               curr_state_count = 0;
            } else if ((!ATIbusy) && (!ATIerr))
            {
               /* ATI event 2
                * ATI_busy = 0
                * ATI_error = 0
                * */
               IQS263_state = Idle;
               curr_state_count = 0;
            } else
            {
               /* ATI event 1
                * Dummy read
                * ATI_busy = 1
                * */
               IQS263_state = ATI;
               curr_state_count++;
            }
         } else
         {
            curr_state_count++;
         }



      break;
      case ATI_error:
         /* x sec time-out
          * */
         curr_time = HAL_GetTick();
         if (curr_state_count == 0)
         {
            starttime = curr_time;
            curr_state_count++;
         } else if ((curr_time - starttime) > timeout)
         {
            IQS263_state = Force_comms;
            curr_state_count = 0;
         } else
         {
            curr_state_count++;
         }

      break;
      case Force_comms:
         /* Command: Redo-ATI
          * */
         I2C_State = IQS263_I2C_Capture(hi2c);

         if (I2C_State == HAL_OK)
         {
            pData[0] = ADDR_PROXSET;
            pData[1] = 0b00010000;
            pData[2] = 0b01011101;
            pData[3] = 0x00;
            pData[4] = 0x00;
            pData[5] = 0xFF;
            data_size = 6;

            I2C_State = IQS263_I2C_Master_Transmit(hi2c, (slider_address << 1),
                                                    pData, data_size, timeout);
         }
         if (I2C_State == HAL_OK)
         {
            IQS263_I2C_Release(hi2c);
            IQS263_state = ATI;
            curr_state_count = 0;
         } else
         {
            curr_state_count++;
         }

      break;
      case Idle: // includes event handler, rapid state events, and event state
         /* RDY low detect
          * */
         /* READ SYSTEM FLAGS */
         I2C_State = IQS263_I2C_Capture(hi2c);

         if (I2C_State == HAL_OK)
         {
            pData[0] = ADDR_SYS_FLAGS;
            data_size = 1;
            I2C_State = IQS263_I2C_Master_Transmit(hi2c, (slider_address << 1),
                                                    pData, data_size, timeout);
         }

         if (I2C_State == HAL_OK)
         {
            memset(pData, 0xFF, 30);
            data_size = 2;

            I2C_State = IQS263_I2C_Master_Receive(hi2c, (slider_address << 1),
                                                   pData, data_size, timeout);

            if (I2C_State == HAL_OK)
            {
               sysflags = pData[0];
               events = pData[1];

               /* READ DELTAS */
               if (I2C_State == HAL_OK)
               {
                  pData[0] = ADDR_DELTAS;
                  data_size = 1;
                  I2C_State = IQS263_I2C_Master_Transmit(hi2c, (slider_address << 1),
                                                          pData, data_size, timeout);
               }

               if (I2C_State == HAL_OK)
               {
                  memset(pData, 0x0, 30);
                  data_size = 8;

                  timeout = 3;
                  I2C_State = IQS263_I2C_Master_Receive(hi2c, (slider_address << 1),
                                                         pData, data_size, timeout);

                  if (I2C_State == HAL_OK)
                  {
                     delta_C1 = (pData[3] << 4) | pData[2];
                     delta_C2 = (pData[5] << 4) | pData[4];
                     delta_C3 = (pData[7] << 4) | pData[6];
                     sum_delta = delta_C1 + delta_C2 + delta_C3;

                     if (sum_delta > SUM_DELTA_MIN)
                     {
                        position = P_MAX*((delta_C2/2) + delta_C3)/sum_delta;
                        g_TEMP_SETPOINT = position*(T_INPUT_MAX-T_INPUT_MIN)/P_MAX + T_INPUT_MIN;
                        _7_SEG_disp_int_set(g_TEMP_SETPOINT);
                        IQS263_touch = true;
                     } else
                     {
                        IQS263_touch = false;
//                        _7_SEG_disp_int_set(g_T_water);
                     }
                  }
               }

            }

            IQS263_I2C_Release(hi2c);
         }

      break;
      default:
         break;
   }

   /* Reset I2C if fail */
   if (I2C_State != HAL_OK)
   {
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TXE);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ADDR);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_STOPF);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ARLO);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_OVR);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_PECERR);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TIMEOUT);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ALERT);

      __HAL_UNLOCK(hi2c);

      hi2c->Instance = I2C1;
      hi2c->Init.Timing = 0x0000020B;
      hi2c->Init.OwnAddress1 = 0;
      hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
      hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
      hi2c->Init.OwnAddress2 = 0;
      hi2c->Init.OwnAddress2Masks = I2C_OA2_NOMASK;
      hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
      hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
   }

   return;
}


uint8_t IQS263_test (I2C_HandleTypeDef* hi2c)
{
   uint32_t timeout = 2;
   HAL_StatusTypeDef I2C_State = HAL_BUSY;
   static uint8_t state = 0;

   uint8_t pData[30];
   uint16_t data_size;

   switch (state)
   {
      case 0:
         /* READ DEVICE INFORMATION */
         I2C_State = IQS263_I2C_Capture(hi2c);

         if (I2C_State == HAL_OK)
         {
            pData[0] = ADDR_DEVI_INFO;
            data_size = 1;
            I2C_State = IQS263_I2C_Master_Transmit(hi2c, (slider_address << 1),
                                                    pData, data_size, timeout);
         }

         if (I2C_State == HAL_OK)
         {
            memset(pData, 0xFF, 30);
            data_size = 2;

            I2C_State = IQS263_I2C_Master_Receive(hi2c, (slider_address << 1),
                                                   pData, data_size, timeout);

            if (I2C_State == HAL_OK)
            {
               prod_num = pData[0];
               ver_num = pData[1];
            }
         }

         if (I2C_State == HAL_OK)
         {
            IQS263_I2C_Release(hi2c);
            state = 1;
         }
      break;
      case 1:
         /* READ SYSTEM FLAGS */
         I2C_State = IQS263_I2C_Capture(hi2c);

         if (I2C_State == HAL_OK)
         {
            pData[0] = ADDR_SYS_FLAGS;
            data_size = 1;
            I2C_State = IQS263_I2C_Master_Transmit(hi2c, (slider_address << 1),
                                                    pData, data_size, timeout);
         }

         if (I2C_State == HAL_OK)
         {
            memset(pData, 0xFF, 30);
            data_size = 2;

            I2C_State = IQS263_I2C_Master_Receive(hi2c, (slider_address << 1),
                                                   pData, data_size, timeout);

            if (I2C_State == HAL_OK)
            {
               sysflags = pData[0];
               events = pData[1];
            }
         }

         if (I2C_State == HAL_OK)
         {
            IQS263_I2C_Release(hi2c);
            state = 2;
         }
      break;
      case 2:
         /* READ PROXSET REGISTERS */
         I2C_State = IQS263_I2C_Capture(hi2c);

         if (I2C_State == HAL_OK)
         {
            pData[0] = ADDR_PROXSET;
            data_size = 1;
            I2C_State = IQS263_I2C_Master_Transmit(hi2c, (slider_address << 1),
                                                    pData, data_size, timeout);
         }

         if (I2C_State == HAL_OK)
         {
            memset(pData, 0xAA, 30);
            data_size = 5;

            I2C_State = IQS263_I2C_Master_Receive(hi2c, (slider_address << 1),
                                                   pData, data_size, timeout);
         }

         if (I2C_State == HAL_OK)
         {
            IQS263_I2C_Release(hi2c);
            state = 0;
         }
         break;
      default:
         break;
   }

   /* Reset I2C if fail */
   if (I2C_State != HAL_OK)
   {
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TXE);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ADDR);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_STOPF);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ARLO);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_OVR);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_PECERR);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_TIMEOUT);
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ALERT);

      __HAL_UNLOCK(hi2c);

      hi2c->Instance = I2C1;
      hi2c->Init.Timing = 0x0000020B;
      hi2c->Init.OwnAddress1 = 0;
      hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
      hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
      hi2c->Init.OwnAddress2 = 0;
      hi2c->Init.OwnAddress2Masks = I2C_OA2_NOMASK;
      hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
      hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
   }

   return I2C_State;
}

/* PRIVATE FUNCTIONS */

