MCU=atmega8
F_CPU=1000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.cpp HD44780.cpp

compile:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	sudo avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb -B 128

hot:
	make compile
	make flash

clean:
	rm -f *.bin *.hex
