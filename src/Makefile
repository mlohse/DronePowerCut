################################################################################
# Makefile for Drone Power Cut                                                 #
# ---------------------------------------------------------------------------- #
# author:  Markus Lohse <mlohse@gmx.net>                                       #
# date:    2023-02-05                                                          #
# license: LGPLv3, see https://www.gnu.org/licenses/lgpl-3.0.txt               #
################################################################################

# Target name:
TARGET = pwrcut

# Fuses (just keep the default)
HFUSE=0x62
LFUSE=0xDF

# Target type
#MCU=atmega48p # bread board
MCU=atmega48a

# AVR Dragon
PROGRAMMER=dragon_isp
PORT=usb

# cheap AVRISP MKII clone, e.g. https://www.amazon.de/-/en/DollaTek-Compatible-Programmer-AVRISP-Supports/dp/B07L2SYF4K
#PROGRAMMER=avrispmkII
#PORT=/dev/ttyUSB0

SRC =	main.c \
		ctrl.c \
		timer.c \
		decoder.c \
		led.c

OBJ = $(SRC:.c=.o)


# Compiler / Linker flags:
CFLAGS = -mmcu=$(MCU) -Wall -g2 -O1 -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
LDFLAGS = -mmcu=$(MCU) -Wl,-Map=$(TARGET).map

###################################
# rules:

.PHONY: all program clean

all:	$(TARGET).hex $(TARGET).eep $(TARGET).lss

fuses:
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(MCU) -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m

program:
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(MCU) -U flash:w:$(TARGET).hex
	sleep 2
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(MCU) -U eeprom:w:$(TARGET).eep

clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).hex $(TARGET).lss $(TARGET).map $(TARGET).eep


###################################
# Psudorules:

%.eep: %.elf
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex $< $@

%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@

%.lss: %.elf
	avr-objdump -h -S $< > $@

%.elf: $(OBJ)
	avr-gcc $^ $(LDFLAGS) -o $@
	avr-size $@

%.o : %.c
	avr-gcc $(CFLAGS) -c $< -o $@
