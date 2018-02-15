### Connections
---
#### 1. Power
There are mutiple ways of connecting the Dev board. The power supply is provided either by the host PC through the USB cable, or by an external source: VIN (7V-12V), E5V (5V) or +3.3V power supply pins on CN6 or CN7
#### Powering using 5V input
When power the Dev Board using the E5V (5V), the connector pin is: CN7 pin 6. ***Max current is: 500mA*** and voltage range is: 4.75V - 5.25V
##### Procedure for using 5V input and debugging using USB:
1. Connect the jumper between pin 2 and pin 3 of JP5
2. Check that JP1 is removed
3. Connect the external power source to VIN or E5V
4. Power on the external power supply 7 V< VIN < 12 V to VIN, or 5 V for E5V
5. Check that LD3 is turned ON
6. Connect the PC to USB connector CN
Look at p22 of STM User manual for causes if above is not followed

#### Powering using USB
When JP1 Connection is off the ***max Current is: 300mA***
When JP1 connection is on the ***max Current is: 100mA***

When the Board needs to pull more than 300mA, than the external Power supply should be use