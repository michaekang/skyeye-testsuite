#  --------------------------------------------------------------------------
#  Simple bootloader for running uClinux
#
#  Written by Anthony Lee <don.anthony.lee@gmail.com> at 2007
#
#  This program is free software; it may be used and distributed according to
#  the terms of The MIT License.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy of
#  this software and associated documentation files (the "Software"), to deal in
#  the Software without restriction, including without limitation the rights to use,
#  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
#  the Software, and to permit persons to whom the Software is furnished to do so,
#  subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
#  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
#  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
#  File: Makefile
#
#  --------------------------------------------------------------------------

CROSS_COMPILE ?= arm-uclinux-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -O2 -mlittle-endian -march=armv4 -mtune=arm7tdmi
LDFLAGS = -T bootloader.lds

all: boot_code.bin

boot_code.bin: boot_code.elf
	$(OBJCOPY) -O binary --remove-section=.ramvec \
		--remove-section=.bss --remove-section=.data \
		--remove-section=.eram \
		--set-section-flags=.romvec=CONTENTS,ALLOC,LOAD,READONLY,CODE \
		$< $@

boot_code.elf: bootloader.o
	$(LD) $(LDFLAGS) $^ -o $@

bootloader.o: bootloader.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o boot_code.*

