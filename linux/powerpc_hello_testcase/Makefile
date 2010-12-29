CROSS_COMPILE:=/home/oscenter/freescale-4.4/bin/powerpc-linux-gnu
CFLAGS:= -static -msoft-float
test-ppc:test.c
	$(CROSS_COMPILE)-gcc $(CFLAGS)  $^ -o $@

objdump:
	$(CROSS_COMPILE)-objdump -d test-ppc >test-ppc.s
