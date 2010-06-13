#
# Makefile for hello
#
CROSS_COMPILE=bfin-uclinux-
    CC=$(CROSS_COMPILE)gcc
    LD=$(CROSS_COMPILE)ld
    CFLAGS= -c -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -pipe -g  
    LDFLAGS= -N -X -Thello.lds
    
    LIB=
    
    all: hello 

    hello: start.o hello.o
	$(LD) $(LDFLAGS)  start.o hello.o -o hello
	 
    start.o:start.S
	$(CC) $(CFLAGS) start.S	 
	
    hello.o:hello.c
	$(CC) $(CFLAGS) hello.c

    clean:
	rm -rf *.o *.elf *.gdb hello *.r *.n *.s code_cov

#end
