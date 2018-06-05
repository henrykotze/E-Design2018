# EDesign Test Prep

# Lecture 1

## How do we handle complex systems
* We use a process called: V-Process. It is a structured top-down and bottom up process. We brake the big problem up in smaller chunks, synthesize each of the parts separately and then integrate the parts to form the completed system.

* We will be focusing on the bottom up part of the V-process.

## Processor Choice:
* Based on Historical: experience and Tools, development cost
* Size, form and features: Production and field


## Power supply: Design, implementation and measurements
### LM7805 Electrical Characteristic

#### Maximum Ratings
Vinput = 35V,40V
Thermal Resistance: Junction-Case: 5 degrees per Watt
Thermal Resistance: Juncation-air: 65 degrees per Watt
Quiescent Current: Typical 5mA, Max: 8mA


#### Typical Values
Voutput: Min:4.75V Max: 5.25V
Vinput: Minimum: 7V

#### Reasons for Capacitors:
From datasheet: Cap @ input: is required if regulator is located an appreciable distance from the power supply filter
From dataheet: Cap @ ouput: Improves stability and transient response

### 1N4007 Electrical Characteristics

#### Maximum Ratings
Forward Voltage @ 1.0A is 1V

# Lecture 2:

Since the FT230X and the STM32F334 is powered separately, a dead parasitic current is a reality. A simple safety solution is using a series resistor.

#### Logic compatibility:
If the CMOS level does not comply with the requiered levels. we can select TTL to allow it.

#### UART Comms
Based on asynchronous, meaning no clock transmitted, 8 bit, least significant bit first, bi-directional communication


### FT230 X USB to BASIC UART IC
#### Maximum Ratings:
VCCIO IO Voltage: -0.3V~5.5V
VCC Supply Voltage: -0.3~5.5V
DC Output Current: 22mA

Ouput Voltage High: Min:0.9VCCIO Max: VCCIO
Output Voltage Low: Min:0V Max: 0.4V


# Lecture 3
### ADC Review
Quantization- process of converting from analog to digital representation
Successive Approximation (SAR) (good trade-off: accuracy & speed)
Sampling Frequency: Nyquist Frequency = 2 * Maximum frequency in signal

# Lecture 4
What is the possible error in a ADC sampling?

## MCP601 Electrical Sheet
Supply Voltage Vdd: Min: 2.7V Max: 6V

### Values for input resistors & and their reasons:
Resisor are their for current limiting, to protect the input pins
Values for R1 and R2 are: R1 and R2 are connected to the +- terminals of the opamp look at p12 on datasheet

R1 > [ Vss - (minumum expected V1) ]/(2mA)



#### Designing Gain in 30 Seconds

# Lecture 5
Division is by right bit-shift >>
Computational very efficient
When Adding and mutiplying check for overflows
Check how to do Fixed Point Arithmetix

# Lecture 6
Nothing

# Lecture 7
#### Debouncing buttons
How to fix: Use a digital low pass filter in software or simple low pass RC-filter

#### What is a Realtime system:
Real time means to meet deadlines
Hard Real-time: Needs to meet a task deadline EVERY time
Soft Real-time: Task meeats deadline most of the time
Non-preemptive scheduling vs Preemptive scheduling: We use non-preemptive approach

#### I2C
Synchronous Serial Communication
Has Bi-directional Data, SDA lines
Open-Drain configuration, open-collector for BJT
Line is active when low


# From the PDD

## USB to Serial Interface
What is the role of R6 and R10 in the circuit: Parasitic effect and to protect the pins connected not to exceed their maximum ratings
How must I determine the values for these Resisitor

To test the circuit, make sure the curcuit enumerates correctly when the USB canle is conected to the PC. Secondly, a simple comms test can be performed bytemporarily shorting TXD and RXD pins, called a loopback test, and checking that characters sent via a terminal program is echoed back



3.7 Azoteq ProxSense Cappo Daughter Board
The two sliders are interfaced through two separate Azoteq IQS263 devices, both on a shared I2C bus. They are addressed as 0x44 for the linear slider and 0x45 for the rotary slider. Two separate open-collector active low ready lines.

3.10 Temperature
The voltage will vary linearly with a temperature, ata temperature coeffiecient of 10mV/deg and a zero reading 0f 0.5V at 0 degrees.


Why use Git:
Is very handy tool for source control versioning.  not only keeps backups, but also makes is very easy for you to see what has
changed in your source code and when.

4.9 RTC
The real-time clock should use the Nucleo 32 kHz oscillator (LSE) as clock source. The internal HSI main
clock is not as accurate, so we would like to update the timing using the RTC clock as well.  This can be
done by enabling the wake-up timer in the RTC module and generating a 1 second wake-up interrupt.


## Development Board Pin Specification
Input Voltage: Min: -0.3V Max 3.7V
Output current sunk/source by an I/O and control pin: 25mA

Low-Level Input Voltage: 0.3Vdd + 0.07 High-Level input voltage: 0.7Vdd
Low-level output voltage for an I/O pin: Max: 1.3V for current I = 20mA High-Level output voltage for an I/O pin: Min: Vdd-1.3 for current I = 20mA

## STD FUNTIONS AND THEIR DESCRIPTION:
### memset
void * memset ( void * ptr, int value, size_t num );\

### strlen
size_t strlen ( const char * str );

### sprintf
Composes a string with the same text that would be printed if format was used on printf, but instead of being printed, the content is stored as a C string in the buffer pointed by str.
int sprintf ( char * str, const char * format, ... );

### strtok
char * strtok ( char * str, const char * delimiters )


## HAL Function

### HAL FLASH GENERIC
HAL_StatusTypeDef HAL_FLASH_Program (uint32_t TypeProgram, uint32_t Address, uint64_t Data)

TypeProgram: Indicate the way to program at a specified address. This parameter can be a value of FLASH Type Program
Address: Specifie the address to be programmed.
Data: Specifie the data to be programmed
The function HAL_FLASH_Unlock() should be called before to unlock the FLASH interface The function HAL_FLASH_Lock() should be called after to lock the FLASH interface
If an erase and a program operations are requested simultaneously, the erase operation is performed before the program one.
FLASH should be previously erased before new programmation (only exception to this is when 0x0000 is programmed)

FLASH_TYPEPROGRAM_HALFWORD Program a half-word (16-bit) at a specified address.

FLASH_TYPEPROGRAM_WORD Program a word (32-bit) at a specified address.

FLASH_TYPEPROGRAM_DOUBLEWORD Program a double word (64-bit) at a specified address

### HAL ADC GENERIC DRIVER



### HAL I2C GENERIC DRIVER
I2C_FIRST_AND_LAST_FRAME: No sequential usage, functionnal is same as associated interfaces in no sequential mode

I2C_FIRST_FRAME: Sequential usage, this option allow to manage a sequence with start condition, address and data to transfer without a final stop condition

I2C_FIRST_AND_NEXT_FRAME: Sequential usage (Master only), this option allow to manage a sequence with start condition, address and data to transfer without a final stop condition, an then permit a call the same master sequential interface several times (like HAL_I2C_Master_Sequential_Transmit_IT() then HAL_I2C_Master_Sequential_Transmit_IT())

I2C_NEXT_FRAME: Sequential usage, this option allow to manage a sequence with a restart condition, address and with new data to transfer if the direction change or manage only the new data to transfer if no direction change and without a final stop condition in both cases

I2C_LAST_FRAME: Sequential usage, this option allow to manage a sequance with a restart condition, address and with new data to transfer if the direction change or manage only the new data to transfer if no direction change and with a final stop condition in both cases



## I2C IQS263 DATASHEET

### I2C Read

To  read  from  the  device  a current  address read can  be  performed.  This  assumes  that  the  address-command is already setup as desired.

If  the  address -command  must  first  be  specified,  then  a random  readmust  be  performed.    In this case a WRITE is initially performed to setup the address-command, and then a repeated start is used to initiate the READ section\

### I2C WRITE
To  write  settings  to  the  device  a Data  Write is  performed.    Here  the  Address-Command  is always required, followed by the relevant data bytes to write to the device.


