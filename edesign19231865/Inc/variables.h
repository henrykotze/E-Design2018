#ifndef VARIABLES_H_
#define VARIABLES_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// UART Variables

extern uint8_t rx_flag;
extern uint8_t rx_buffer;
extern uint8_t* uart_command;
extern uint8_t uart_counter;
extern uint8_t* studentnumber;
extern char endSimbol[8];
extern char comma[2];
extern uint8_t* return_value;
extern uint8_t sizeOfTemp;
extern uint8_t auto_heating;
extern uint8_t* set_temp;
extern uint8_t sizeOfTemp0;
extern char* time;
extern char studentnumber1[];

// Seven Segment Variables
extern uint8_t segment_counter;
extern uint8_t* segment_val;


// ADC Variables
extern uint8_t adc_flag;
extern uint32_t adc_raw_voltage;
extern uint32_t adc_raw_current;

extern uint64_t adc_buffer_voltage;
extern uint64_t adc_buffer_current;
extern uint16_t adc_counter;
extern uint16_t adc_buffer_array[];
extern uint64_t voltage_rms;
extern uint64_t current_rms;

extern uint32_t* ADC1_buffer;


#endif
