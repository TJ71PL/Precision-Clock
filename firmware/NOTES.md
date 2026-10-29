# NOTES

## DISPLAY

- the display (six seven segment display) is driven a three 16 bit LED driver, all three are connected in such a way that they create a conitnues 48bit shift register, each bit represents a LED segment on the display.
- the data is sent you to the 48 bit shift register using MCU's on board SPI peripheral, with two pins serial clock (DISPLAY_CLOCK PB3) nad serial data (DISPLAY_DATA PB5).
- in order to send for example clock data, the data needs to follow HH.mm.SS where HH is sent last and SS is sent first
- each 16 bit shift register has two pins that is load enable and output enable needs to be driven, since all the shfit register's load enable pin and output enable are connected and are common. the MCU only needs to drive two pins.
- the output enable pin is used to change the brightness of the whole display by a PWM input, for that a timer TIM4_CH2 is used to generate a PWM signal,
