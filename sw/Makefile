-include $(CURDIR)/.config

CROSS_COMPILE ?= arm-none-eabi-

TESTS := $(wildcard tests/*-main.c)
BINARIES-y = $(TESTS:-main.c=.bin)
BINARIES-y += puntel.bin

OBJECTS  = $(BINARIES-y:.bin=.o)
ELFS     = $(BINARIES-y:.bin=)

CC =		$(CROSS_COMPILE)gcc
LD =		$(CROSS_COMPILE)ld
OBJDUMP =	$(CROSS_COMPILE)objdump
OBJCOPY =	$(CROSS_COMPILE)objcopy
SIZE =		$(CROSS_COMPILE)size

GIT_VER = $(shell git describe --always --dirty)

# linker configuration and rule (we preprocess it)
LDS-y = lds/lpc-flash.lds
ldflags-y	= -nostdlib -T $(LDS-y) -Wl,--gc-sections -Os -lgcc

# This comes from a .config driven thing, here simplified
%.lds: %.lds.S
	cp $^ $@

# compiler flags
cflags-y		= -g -Wall -ffreestanding -O2 -Wstrict-prototypes
cflags-y		+= -include config.h
cflags-y		+= -include include/cpu.h
cflags-y		+= -ffunction-sections -fdata-sections -fno-common
cflags-y		+= -Wno-format-zero-length
cflags-y		+= -march=armv6-m -mthumb -mtune=cortex-m0
cflags-y +=  -Iinclude -Ipp_printf -I.

# object file selection
obj-y			= boot.o setup.o
obj-y			+= lib/io.o lib/string.o lib/udelay.o lib/jiffies.o
obj-y			+= lib/ctype.o
obj-y			+= pp_printf/printf.o pp_printf/vsprintf-full.o
obj-y			+= lib/io-11xx.o lib/gpio-11xx.o
obj-y			+= lib/pll.o lib/uart.o lib/rand.o
obj-y			+= lib/regs.o lib/panic.o lib/usb.o lib/usb-serial.o
obj-y			+= lib/neopixel.o

# eventually, really build rules
all: tools $(LDS-y) $(ELFS) $(BINARIES-y)

.PHONY: all tools clean

tools:
	$(MAKE) -s -C tools

clean:
	$(MAKE) -C tools clean
	rm -f *.o tests/*.o $(BINARIES-y) $(ELFS) $(LDS-y)

%.bin: %
	${OBJCOPY} -O binary $^ $@
	./tools/fix-checksum $@

%: %.o
	$(CC) $(cflags-y) -D__GITC__="\"$(GIT_VER)\"" -c revision.c
	$(CC) $(cflags-y) -o $@ revision.o $*.o \
		-Wl,-Map=$@.map $(ldflags-y)

puntel.o: $(obj-y) puntel-main.o
	$(LD) -r $(obj-y) puntel-main.o -T lds/bigobj.lds -o $@



tests/%.o: $(obj-y) tests/%-main.o
	$(LD) -r $(obj-y) tests/$*-main.o -T lds/bigobj.lds -o $@

%.o: %.c
	$(CC) $(cflags-y) -c $*.c -o $@

%.o: %.S
	$(CC) $(cflags-y) -c $*.S -o $@

%.i: %.c
	$(CC) $(cflags-y) -E $*.c -o $@

%.S: %.c
	$(CC) $(cflags-y) -S $*.c -o $@

lds/%.lds: lds/%.lds.S
	$(CC) $(cflags-y) -E -P lds/$*.lds.S -o $@

# This forces more compilations than needed, but it's useful
# (we depend on .config and not on include/generated/autoconf.h
# because the latter is touched by silentoldconfig at each build)
$(obj-y): $(wildcard include/*.h)

