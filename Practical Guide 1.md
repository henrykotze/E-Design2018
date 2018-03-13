## Power Supply
Multimeter Resistance is 0.6
### First Objective
1. Max and Min Input voltage to powersupply section
* The peak working reverse voltage of the diode is 1000V, but since we expect fluctuations in out
the peak working reverse RMS input voltage is 700V
* The diode
2. Max and Min Input current to powersupply section
* The diode maximume input current is 1A.
*
### Second Objective
1. Reason for using 100nF Cermamic Cap
* The Capacitors causes any change in instantaneous input voltage to be smoothed out due to the
laws governing the capacitor.
* Since the national grid runs on average on about 60Hz.
2. Reasons for using 100nF Electrolytic cap
* electrolytic capacitors are most often used in lower-frequency applications such as in power
supply filters.
*
3. Reason for use of Diode
* The diode acts as an extra layer of protection, to ensure the current always flow in the direction
of the input of the regulator, even if there is a sudden drop in the input voltage. The cap will thus
always discharge through the regulator.
* The maximum working reverse voltage of the diode is 1000V, and this magnitude of input
voltage will never happen, since the grid in on 220V input.
* The diode and capacitor combinations act as a half-way recitifier, and even if our assumption of
a DC input voltage is wrong due to some error outside of the scope of the design, the product might
still work, but this wont be tested.

### Third Objective

Voltage Input: 7V
* Voltage @ Reg input:6.37V
* Voltage @ Reg Output: 5.07V

* Voltage Across Diode: 0.682V

Voltage Input: 8V
* Voltage @ Reg input:7.27V
* Voltage @ Reg Output: 5.07V

Voltage input: 9V
* Voltage Input at Regulator: 8.245V
This does make sense due to the voltage drop accross the diode and the non-linearities in the
cap.
* Voltage Output at Regulator: 5.073V
* Voltage Difference Between Input and Regulator: 3.351V
* Voltage at J25,J16,J14 Measure: 5.073V
* Voltage Acrosee Diode: 0.682V

Voltage Input: 10V
* Voltage Input at Regulator: 9.4V
* Voltage Output at Regulator: 5.073V
* Voltage Across Diode: 0.682V

Voltage Input: 11V
* Voltage Input at Regulator:10.4V
* Voltage Output: 5.074V
* Voltage Across Diode: 0.682V