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
uint8_t* set_temp = NULL;
uint8_t sizeOfTemp = 0;
uint8_t auto_heating = 0;
char* time = "00:00:00";


// Seven Segment Variables
uint8_t segment_counter = 1;
uint8_t segment_val = 0;

// ADC Variables
uint8_t adc_flag = 0;
uint8_t adc_raw_value = 0;
