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

extern int totalTime ;

extern  CanMessage_queue_struct    can1_txd;
extern  CanMessage_queue_struct    can2_txd;
extern  CanMessage_queue_struct    can1_rxd;
extern  CanMessage_queue_struct    can2_rxd;

extern  unsigned int  istp;
extern  unsigned int  NMI,RESV1,RESV2;
extern  unsigned int  unexp_int04,unexp_int05,unexp_int06,unexp_int07;
extern  unsigned int  unexp_int08,unexp_int09,unexp_int10,unexp_int11;
extern  unsigned int  unexp_int12,unexp_int13,unexp_int14,unexp_int15;

extern  void interrupt c_int00(void);

unsigned int isr_jump_table[16] =
{
    (unsigned int) c_int00,
    (unsigned int) (&NMI),
    (unsigned int) (&RESV1),
    (unsigned int) (&RESV2),
    (unsigned int) (&unexp_int04),
    (unsigned int) (&unexp_int05),
    (unsigned int) (&unexp_int06),
    (unsigned int) (&unexp_int07),
    (unsigned int) (&unexp_int08),
    (unsigned int) (&unexp_int09),
    (unsigned int) (&unexp_int10),
    (unsigned int) (&unexp_int11),
    (unsigned int) (&unexp_int12),
    (unsigned int) (&unexp_int13),
    (unsigned int) (&unexp_int14),
    (unsigned int) (&unexp_int15),
};

//----------------------------------------------------------------------------
//-- set CSR,IER,ICR,EXTPOL
//   set ISTP
//   ext 4\5\7 high-to-low transition on a interrupt source is recognized as a interrupt
//   ext 6     low-to-high transition on a interrupt source is recognized as a interrupt
//----------------------------------------------------------------------------
void interrupt_initial(void)
{
    unsigned int    istp_address;
    CSR = 0x100;	         	             // disable GIE PGIE bit8:EN=1 little endian mode
    IER = 0x1;                               // disable all interrupts£¬bit0 must be 1
    ICR = 0xfff0; 				             // clear all pending interrupts,bit0-bit reserved

    *(unsigned volatile int *)EXTPOL = 0xb;

    //istp_address = (unsigned int)&istp;
    istp_address = (unsigned int)isr_jump_table;
    ISTP = istp_address;

}

//----------------------------------------------------------------------------
//-- set one ISR table,ISR hook
//----------------------------------------------------------------------------
unsigned char interrupt_hook(void *isr_add,int cpu_intr)
{
    unsigned char res;

    res = 0x01;
    if((cpu_intr>0) && (cpu_intr<16))
    {
        *((unsigned int *)isr_jump_table + cpu_intr) = (unsigned int)isr_add;
    }
    else
    {
        res = 0x00;
    }

    return res;
}

//----------------------------------------------------------------------------
//-- can1 rxd interrupt
//-----------------------------------------------------------------------------
interrupt void interrupt_can1_rxd_isr()
{

    CanMessage_struct frame;
		if(Sja1k_CAN_Msg_Read(CTRL_BUS_BASE,(CanMessage_struct *)&frame) == SUCCESS)
		{
			if((can1_rxd.head>=0) && (can1_rxd.head<queue_use_len))
			{
			  can1_rxd.queue[can1_rxd.head] = frame;
			  can1_rxd.head++;
			  if(can1_rxd.head>=queue_use_len)
			  {
			      can1_rxd.head = 0;
			  }
			}
		}
}

//----------------------------------------------------------------------------
//-- can2 rxd interrupt
//----------------------------------------------------------------------------
interrupt void interrupt_can2_rxd_isr()
{

    CanMessage_struct frame;


	if(Sja1k_CAN_Msg_Read(TEST_BUS_BASE,(CanMessage_struct *)&frame) == SUCCESS)
	{

			if((can2_rxd.head>=0) && (can2_rxd.head<queue_use_len))
			{
			  can2_rxd.queue[can2_rxd.head] = frame;
			  can2_rxd.head++;
			  if(can2_rxd.head>=queue_use_len)
			  {
			      can2_rxd.head = 0;
			  }
			}
	}
}


interrupt void interrupt_timer0_selftest_isr(void)
{
    unsigned int  tmp_irp,tmp_csr,tmp_amr;

    SAVE_CREG(tmp_irp,IRP);
    SAVE_CREG(tmp_csr,CSR);
    SAVE_AMR(tmp_amr);

    //CSR |= 1;

	totalTime+=10;
   
	//CSR &= 0xFFFFFFFE;
	asm(" nop 8");
    RESTORE_AMR(tmp_amr);
    RESTORE_CREG(CSR,tmp_csr);
    RESTORE_CREG(IRP,tmp_irp);
}

