all:hello

hello:hello.c
	arm-linux-gcc -o hello hello.c -I /opt/arm/3.3.2/include -L/opt/arm/3.3.2/lib  -lc -static
	arm-linux-objdump -xS hello > hello.s
	arm-linux-objdump -d hello > hello.dis
	arm-linux-readelf -a hello > hello.r
	arm-linux-nm hello > hello.n

clean:
	rm -rf *.o *.elf *.gdb hello *.r *.n *.s
