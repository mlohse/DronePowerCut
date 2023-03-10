# DronePowerCut

This board is supposed to be connected between the main battery and the flight controller of a drone/opto-copter and provides an emergency power-off in case the drone get's out of control.
The board has been designed for 6s LiPo batteries (22.2V) and can handle continuous currents of up to 80A.



# Bill of Material (BOM)
The PCB can be ordered at OSH Park (they ship worldwide):

* https://oshpark.com/shared_projects/SKaDHxAu (rev.A)

It doesn't really matter of which brand/type you order resistors and capacitors, nor does this board require any tight tolerances. You can purchase whatever your local hardware dealer has on stock fitting the value/package described by the schematic.
However, for convenience I've created a virtual shopping basket at Reichelt Elektronik:

* https://www.reichelt.de/my/2021258

MosFETs and Voltage regulator are available at Farnell:

* https://de.farnell.com/infineon/auirfs8409-7trl/mosfet-n-kanal-40v-240a-to-263/dp/2839427?st=auirfs8409
* https://de.farnell.com/microchip/mic5219-3-6ym5-tr/ldo-0-5vdo-0-5a-3-6v-1-5sot23/dp/2510256?st=mic5219


# Building and Flashing the Firmware
You need to have an AVR toolchain installed (make, gcc, binutils)

On Arch Linux simply install the following packages:

`# pacman -S community/avr-gcc community/avr-binutils community/avr-libc`

You may likely want to install avrdude (of course if your programmer requires a different software you can skip this step):

`# pacman -S avrdude`

Please don't forget to adapt the `PROGRAMMER`/`PORT` section in the `Makefile` according to your programmer.


To build the firmware change into the `src` directory and run:

`# make`

...then connect the board to your ISP programmer - the boards needs to be powered (consumes < 50mA) through the programmer - and flash the firmware:

`# make program`

**Optional**: It shouldn't be necessary to flash fuses, as they are left to defaults. But in case the MCU behaves weird in any way...

`# make fuses`

Done.


# LED States (Debugging)

## Power LED (blue)
This led should always be flashing with 1Hz during opartion. If constantly lid or off the MCU has crashed - should never happen of course ;)

## Activity LED (green)
This led indicated whether there is a signal from the receiver:

* **off**: no signal
* **flashing with 5Hz**: invalid signal (pulse to short/long, see `CTRL_DECODER_VAL_MIN`/`CTRL_DECODER_VAL_MAX`)
* **constantly lid**: signal ok (during normal operation this should always be the case)

## OFF LED (red)
This led indicates when lid that power has been cut (emergency off active).
