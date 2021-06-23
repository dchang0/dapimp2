CC=avr-gcc
OBJCOPY=avr-objcopy
F_CPU=1000000
MCU=atmega48
#MCU=atmega168p
SERIAL=$(shell ls /dev/tty.USA*)
TARGET=da_pimp2
FILE=$(TARGET).hex
OBJ=$(TARGET).o
OPT=-Os
#FLOATING_POINT= -Wl,-u,vfprintf -lprintf_flt -lm
LDFLAGS= -Wl,--relax,-u,-lm
CFLAGS= -g -mmcu=$(MCU) $(OPT) -DF_CPU=$(F_CPU) \
        -funsigned-char -funsigned-bitfields -fpack-struct \
        -fshort-enums -Wall -Wstrict-prototypes \
        -Wa,-ahlms=$(<:.c=.lst)
#	--param inline-call-cost=2 -finline-limit=3 -fno-inline-small-functions \
	-ffunction-sections -fdata-sections \
	-ffreestanding -mcall-prologues \
	--combine -fwhole-program \
	-fno-split-wide-types \

all : $(TARGET).o $(TARGET).out $(TARGET).elf $(TARGET).hex

$(TARGET).o : $(TARGET).c
	$(CC) $(CFLAGS) -Os -c $(TARGET).c

$(TARGET).hex : $(TARGET).out
	$(OBJCOPY) -j .text -O ihex $(TARGET).out $(TARGET).hex

$(TARGET).out : $(TARGET).elf
	$(CC) $(CFLAGS) -o $(TARGET).out -Wl,-Map,$(TARGET).map $(TARGET).o

$(TARGET).elf : $(TARGET).o
	$(CC) $(CFLAGS) $(OBJ) --output $@ $(LDFLAGS)

clean : 
	rm -f *.o *.out *.map *.hex *.elf

isp :
	sudo avrdude -c avrispv2 -P /dev/cu.usbserial -p m48 -U flash:w:$(TARGET).hex

dragon :
	sudo avrdude -c dragon_isp -p m48 -U flash:w:$(TARGET).hex

usbtiny:
	sudo avrdude -c usbtiny -p m48 -U flash:w:$(TARGET).hex

dasa:
	sudo avrdude -c dasa -P $(SERIAL) -p m48 -U flash:w:$(TARGET).hex

size :
	avr-size $(TARGET).hex $(TARGET).elf $(TARGET).o

piggies :
	avr-nm --size-sort fck.o | tail -20

dis :
	avr-objdump -d fck.elf | less

sch :
	gsch2pcb -v -d custom_pcb_elements $(TARGET).sch

sch-5vps :
	gsch2pcb -v -d custom_pcb_elements 5vps.sch

sch-mcu-board :
	gsch2pcb -v -d custom_pcb_elements mcu-board.sch

sch-charger:
	gsch2pcb -v -d custom_pcb_elements charger.sch

fresh-pcb : 
	rm $(TARGET).pcb
	rm $(TARGET).net

bom :
	gnetlist -g bom -o bom.txt $(TARGET).sch

via-key :
	xmodmap -e 'keycode  66 = Alt_L'

embed-symbols :
	gschlas -e $(TARGET).sch
