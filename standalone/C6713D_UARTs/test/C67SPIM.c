#include"math.h"
#include"c6x.h"
#include "struct.h"
#include "can.h"
#include "common.h"
#include "emif.h"
#include "interrupt.h"
#include "SJA1000.h"
#include "pll.h"
#include "regs.h"
#include "timer.h"
CanMessage_queue_struct    can1_txd;//already initialize : main.c
CanMessage_queue_struct    can2_txd;//already initialize : main.c
CanMessage_queue_struct    can1_rxd;//already initialize : main.c
CanMessage_queue_struct    can2_rxd;//already initialize : main.c
int totalTime = 0;
unsigned char sdram_flag;
unsigned char flash_flag;

#define UART0_CON_ADDR  (int*)0x1b7e078
#define UART0_STATUS_ADDR  (int*)0x1b7e074
#define UART0_DATA_ADDR  (int *)0x1b7e070

#define UART1_CON_ADDR  (int*)0x1b7e088
#define UART1_STATUS_ADDR  (int*)0x1b7e084
#define UART1_DATA_ADDR  (int *)0x1b7e080

void init_uart(){
        /* init uart0 */
        volatile int* con_addr = UART0_CON_ADDR;
        *con_addr = 0x3;
        con_addr = UART1_CON_ADDR;
        *con_addr = 0x3;
}

void uart0_putc(char c){
	     volatile int* paddr1 = UART0_DATA_ADDR;
        *paddr1 = c;
}

void uart0_puts(char* s){
        char *p = s;
        while(*p != '\0'){
                uart0_putc(*p);
                p++;
        }
}
void uart1_putc(char c){
	     volatile int* paddr1 = UART1_DATA_ADDR;
        *paddr1 = c;
}

void uart1_puts(char* s){
        char *p = s;
        while(*p != '\0'){
                uart1_putc(*p);
                p++;
        }

}
#define MIPS (100 * 1000)
volatile int delay = MIPS;
void main (void)
{
	init_uart();

	uart0_puts("begin system initilize...\n");
	volatile int* StatusAddr = UART1_STATUS_ADDR;
	volatile int* DataAddr = UART1_DATA_ADDR;
	char recv_buf[50];
	for(;;)//excute integration test
	{
#if 0
		uart0_puts("######################################################\n");
		while(delay)
			delay--;
		delay = MIPS;
        uart0_puts("Send data to core_1 with uart1\n");
        uart1_puts("Can you hear Me\n");
        int i = 0;
        uart0_puts("waiting for the data from Core1\n");
        while(1){
        	int status  = *StatusAddr;
        	if(status & 0x1){
        		/* uart1 receive te data */
        		char c = *DataAddr;
        		recv_buf[i++] = c;
        		if(c == '\n')
        			break;
        	}
        }
        uart0_puts("receive the string\t");
        uart0_puts(recv_buf);
        uart0_puts("Send again\n");

#else
        uart0_puts("######################################################\n");
        uart0_puts("Waiting for the data from Core0\n");
        int i = 0;
        while(1){
        	int status = *StatusAddr;
        	if(status & 0x1){
        		/* uart1 receive te data */
        		char c = *DataAddr;
        		recv_buf[i++] = c;
        		if(c == '\n')
        			break;
        	}
        }
        uart0_puts("receive the string from Core0\t");
        uart0_puts(recv_buf);

		while(delay)
			delay--;
		delay = MIPS;
        uart0_puts("Reply core_0 with uart1\n");
        uart1_puts("Yeah I can\n");
#endif
	}
}


