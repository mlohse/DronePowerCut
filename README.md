# DronePwrCut

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

You may likely want to install avrdude (of course if your programmer requires different software you can skip this step):

`# pacman -S avrdude`

Keep in mind to adapt the `PROGRAMMER`/`PORT` sections in the `Makefile`.


To build the firmware change into the `src` directory and run:

`# make`

...then connect the board to your ISP programmer - the boards needs to be powered (consumes < 50mA) through the programmer - and flash the fuses:

`# make fuses`

...and firmware:

`# make program`

Done.
