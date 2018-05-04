#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "variables.h"

void uart_comms();
void seven_segment();
void init_peripherals();
void adc_comms();
void seven_segment_display(uint8_t num);
void convert_adc_raw();
void liters_pumped();
void heating_schedule();
void write2Flash();
void readFlash();
void heating_schedule();


#endif
