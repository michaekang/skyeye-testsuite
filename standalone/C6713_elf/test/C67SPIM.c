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

#define UART0_CON_ADDR  (long*)0x1b7e078
#define UART0_DATA_ADDR  (long *)0x1b7e070
void init_uart(){
        /* init uart0 */
        volatile long* con_addr = UART0_CON_ADDR;
        *con_addr = 0x3;
}

void uart_putc(char c){
	     volatile long* paddr1 = UART0_DATA_ADDR;
        *paddr1 = c;
}

void uart_puts(char* s){
        char *p = s;
        while(*p != '\0'){
                uart_putc(*p);
                p++;
        }

}
#define MIPS (1000 * 1000)
volatile int delay = 1000 * MIPS;
void main (void)
{
	init_uart();
#if 0
	while(delay--)
	        	;
#endif
	delay = MIPS;
	uart_puts("begin system initilize...\n");
#if 1
    //interrupt_initial();//清GIE,PGIE,清IER，清所有可能存在的中断，设置EXTPOL,MUXH,MUXL使用缺省值
    pll_initial();      //配置嗷?配置时钟
    emif_ini();         //配置GBLCTL，CE0CTL，CE1CTL
    emif_decvfg_int();  //配置DEVCFG(设备配置寄存器)
    emif_sdram_setup(); //配置EMIF_SDCTL，SDTIM，EMIF_SDEXT

    *(unsigned int *)0xb0000038 = 0x00;
    *(unsigned int *)0xb0000038 = 0x01;// CPLD（包括计数器、同?I/O）复位

    //timer_set_and_start_timer(TIMER1,200000);
    //interrupt_hook((void *)&interrupt_can1_rxd_isr,4);
    //interrupt_hook((void *)&interrupt_can2_rxd_isr,5);
#endif
    uart_puts("CAN device initilize...\n");
	CAN_init();	
#if 1
	//sdram_flag = emif_sdram_test_fill(SDRAM_TEST_START_ADDRESS,SDRAM_TEST_LENGTH);
	//flash_flag = emif_flash_program_test(FLASH_TEST_START_ADDRESS,FLASH_TEST_LENGTH);

	//interrupt_hook((void *)&interrupt_timer0_selftest_isr,6);
	//IER |= ((1<<6) + (1<<5) + (1<<4) + (1<<1));// enable timer1 int->6,can2->5,can1->4,and must sure that NMIE bit0->1 is enable.
	//CSR |= 1;
	//uart_puts("Start timer...\n");
    //timer_set_and_start_timer(TIMER0,200000);
#endif
	for(;;)//excute integration test
	{
		CanMessage_struct frame_txd;
		CanMessage_struct frame_rxd;
		uart_puts("begin transmit CAN data... \n");
		frame_txd = can1_txd.queue[0];
		int i = 0;
		for(; i < 8; i++){
			uart_puts("Trans Data: ");
			uart_putc(frame_txd.data[i] + 0x30);
			uart_puts("\n");
		}
	    CAN_dispatch_transmit_CANMessages(CANch1,(CanMessage_queue_struct *)&can1_txd);
	    uart_puts("end transmit CAN data... \n");
	    uart_puts("begin recv CAN data... \n");
        //CAN_dispatch_transmit_CANMessages(CANch2,(CanMessage_queue_struct *)&can2_txd);
        CAN_dispatch_receive_CANMessages(CANch1,(CanMessage_queue_struct *)&can1_rxd);
        //CAN_dispatch_receive_CANMessages(CANch2,(CanMessage_queue_struct *)&can2_rxd);
        frame_rxd = can1_rxd.queue[0];
        i = 0;
        for(; i < 8; i++){
        	uart_puts("Recv Data: ");
        	uart_putc(frame_rxd.data[i] + 0x30);
        	uart_puts("\n");
        }
        uart_puts("receive CAN data end...\n\n");
#if 1
        while(delay--)
        	;
        delay = MIPS;
#endif
	}
}


