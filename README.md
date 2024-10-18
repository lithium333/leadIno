# leadIno
Arduino based 12V lead-acid batteries

# Code configuration:
- Arduino Uno 1.1V internal reference is used for ADC to avoid 5V fluctuations propagation on measured battery voltage
- voltage is measured using analog pin A0, max admitted value will be the refence one, so a voltage divider scale down the voltage
- K coefficient must be set after you finish to build the hardware (is suggested to measure both resistors of voltage divider with a good ohm meter)
- this project support 3 kinds of lead-acid batteries(flooded, sealed and AGM), to select operation mode 2 MSB are extracted from A1 reading, 10k resistor is put between A1 and 3.3V pin, A1 is grounded to have 0, 1.2k resistor between A1 and GND to get 1 and 2.7k to get 2
- if you want more state (4 or 8 for example) to measure more kinds of batteries you can build your voltage divider but take into account the reference (in this sketch is 1.1V and not 5V so MSB is 1 when the volatage on pin A1 reaches 0.55V and not 2.5V)
