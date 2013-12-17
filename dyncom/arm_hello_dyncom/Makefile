#
#makefile for helloforSkyeye
#
#author: SU Hang
#Date:   2004-08-28

#begin
	CROSS_PATH=/home/ou/cross/4.2.1/bin/
	CC=$(CROSS_PATH)arm-linux-gcc
	LD=$(CROSS_PATH)arm-linux-ld
    #CC=arm-elf-gcc
    #LD=arm-elf-ld
    //CFLAGS= -c -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -pipe -g -mapcs-32 -march=armv4 -mtune=arm7tdmi 
    CFLAGS= -c -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -pipe -g -march=armv5
    LDFLAGS= -N -p -X -Thello.lds
    
    LIB=
    
    all: hello 

    hello: start.o hello.o
	$(LD) $(LDFLAGS)  start.o hello.o -o hello
	$(CROSS_PATH)arm-linux-objdump -xS hello > hello.s
	$(CROSS_PATH)arm-linux-readelf -a hello > hello.r
	$(CROSS_PATH)arm-linux-nm hello > hello.n
	 
    start.o:start.S
	$(CC) $(CFLAGS) start.S	 
	
    hello.o:hello.c
	$(CC) $(CFLAGS) hello.c

    clean:
	rm -rf *.o *.elf *.gdb hello *.r *.n *.s


#end
