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


// Timer variables
uint8_t tim3_flag = 0;
uint32_t tim3_now = 0;
uint32_t tim3_prev = 0;

// Heater On Off Variables
char heater_ON[] = {'O','N'};
char heater_OFF[] = {'O','F','F'};
char* heater_state = NULL;

// Unknown parameters:
uint8_t send_unk_val = 48 ;

// Water Accumulated
uint32_t water_acc = 0;
char* total_water = NULL;
uint8_t valve_trig = 0;

// Water Flow Variables
char valve_OPEN[4] = {'O','P','E','N'};
char valve_CLOSE[6] = {'C','L','O','S','E','D'};
char* valve_state = NULL;

// Temperature Variables
uint8_t* set_temp = NULL;
uint8_t sizeOfTemp = 0;
//uint8_t* geyser_temp = NULL;
//uint8_t* ambient_temp = NULL;

// Seven Segment Variables
uint8_t segment_counter = 0;
uint8_t* segment_val = NULL;

// ADC Variables
uint8_t adc_flag = 0;
uint32_t adc_raw_voltage = 0;
uint32_t adc_raw_current = 0;
uint32_t raw_ambient_temp = 0;
uint32_t raw_geyser_temp = 0;
uint64_t adc_buffer_voltage = 0;
uint64_t adc_buffer_current = 0;
uint16_t adc_counter = 0;
char* voltage_rms = NULL;
char* current_rms = NULL;

// interger value of voltage and current RMS
uint32_t* voltage_int_rms = NULL;
uint32_t* current_int_rms = NULL;

char* ambient_temp = NULL;
char* geyser_temp = NULL;

// Logging to flash memory;
uint8_t enableFlashLogging = 0;

// Heating Schedule
char* heating_schedule_info[3];
char* heat_schedule1 = NULL;
char* heat_schedule2 = NULL;
char* heat_schedule3 = NULL;
char* heating_info = NULL;



uint32_t* ADC1_buffer = NULL;
uint32_t* ADC2_buffer = NULL;
