TOOL=arm-none-eabi
CFLAGS=-mcpu=cortex-m3 -mthumb -O2 -g -ffreestanding -nostdlib
LDFLAGS=-T boards/qemu-mps2/linker.ld -Wl,--gc-sections -nostartfiles
SRC=$(wildcard src/*.c) $(wildcard asm/*.S) boards/qemu-mps2/startup.S
OUT=build/firmware.elf

all:
	mkdir -p build
	$(TOOL)-gcc $(CFLAGS) $(LDFLAGS) -o $(OUT) $(SRC)

size:
	$(TOOL)-size $(OUT)

clean:
	rm -f $(OUT)
