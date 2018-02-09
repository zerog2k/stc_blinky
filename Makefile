SDCCOPTS ?= --iram-size 256
PORT ?= /dev/ttyUSB0
STCGAL ?= stcgal/stcgal.py
FLASHFILE ?= blinky.hex
SYSCLK ?= 11059

SRC = src/serial.c

OBJ=$(patsubst src%.c,build%.rel, $(SRC))

all: blinky

build/%.rel: src/%.c
	mkdir -p $(dir $@)
	sdcc $(SDCCOPTS) -o $@ -c $<

blinky: $(OBJ)
	sdcc -o build/ src/$@.c $(SDCCOPTS) $^
	cp build/$@.ihx $@.hex
	
flash:
	$(STCGAL) -p $(PORT) -t $(SYSCLK) $(FLASHFILE)

clean:
	rm -f *.ihx *.hex *.bin
	rm -rf build/*

