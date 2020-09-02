NAME            = quasselsperre
OBJECTS         = main.o adc.o io.o timer.o
CPU             = attiny10

CFLAGS          = -mmcu=${CPU} -O2 -Wall -g

#switch the compiler (for the internal make rules)
CC              = avr-gcc

.PHONY: all FORCE clean

#all should be the first target. it's built when make is run without args
all: ${NAME}.elf ${NAME}.hex


#additional rules for files
${NAME}.elf: ${OBJECTS}
	${CC} -mmcu=${CPU} -o $@ ${OBJECTS}

${NAME}.hex: ${NAME}.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

clean:
	rm -f ${NAME}.elf ${NAME}.hex ${OBJECTS}
