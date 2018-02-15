### FTDI Chip: USB to UART
----

The VCCIO is connect to the 3v3OUT pin. 3V3OUT is able to gives 3.3V at 50mA

#### Absolute Maximum Ratings

* VCC Supply Voltage: -0.3V o 5.5V
* VCCIO Supply Voltage: -0.3V to 4V ( we automatically fillfull this specification due to 3V3OUT supplying to VCCIO
* DC Input Voltage for USBDP and USBDM: -0.3V->3.63V
* DC Input Voltage - High Impedance: -0.3V -> 5.8V
* DC Output Current: 22mA


#### DC Characteristics
* Max Operating Supply Current during normal Operation: 8.3mA
* Max operating supply current during USB Suspend: 125uA

##### For 3.3V for I/O cells
* Ouput Voltage High: 2.97V -> 3.3V
* Output Voltage Low:  0 -> 0.4V
* Input Low Threshold: 0.8V
* Input High Threshold: 2V


#### Layout Design Reasoning
----
Caps create a matching network for robost communication. The capacitors reduces ringing on the network and the effect of reflection.

The 2 100 Ohm resitors between P7 and microcontrolller, because the microcontroller is running on a different power supply we need to protect it.