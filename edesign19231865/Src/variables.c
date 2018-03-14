#include "variables.h"


// UART Variables

uint8_t rx_flag = 0;
uint8_t rx_buffer;
uint8_t* uart_command = NULL;
uint8_t uart_counter = 0;
uint8_t rx_val = 0;
char studentnumber1[] = {'1', '9','2','3','1','8','6','5'};
unsigned char* studentnumber;
char endSimbol[] = {'\r', '\n'};
char comma[] = {','};
uint8_t* return_value = NULL;

uint8_t auto_heating = 0;
char* time = "00:00:00";

// Heater On Off Variables
char heater_ON[] = {'O','N'};
char heater_OFF[] = {'O','F','F'};
char* heater_state = NULL;

// Water Flow Variables


// Temperature Variables
uint8_t* set_temp = NULL;
uint8_t sizeOfTemp = 0;
uint8_t* geyser_temp = NULL;
uint8_t* ambient_temp = NULL;

// Seven Segment Variables
uint8_t segment_counter = 0;
uint8_t* segment_val = NULL;

// ADC Variables
uint8_t adc_flag = 0;
uint32_t adc_raw_voltage = 0;
uint64_t adc_buffer_voltage = 0;
uint64_t adc_buffer_current = 0;
uint16_t adc_counter = 0;
char* voltage_rms = NULL;
char* current_rms = NULL;

// interger value of voltage and current RMS
uint32_t* voltage_int_rms = NULL;
uint32_t* current_int_rms = NULL;

uint32_t adc_raw_current = 0;

uint32_t* ADC1_buffer = NULL;
