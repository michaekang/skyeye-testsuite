#include "struct.h"
#include "can.h"
#include "common.h"
#include "emif.h"
#include "interrupt.h"
#include "SJA1000.h"
#include "pll.h"
#include "regs.h"

#include "timer.h"


//----------------------------------------------------------------------------
//--DSP PLL initiate:Set the frequence of SYSCLK1,SYSCLK2,SYSCLK3
//
//  EMIF   -- SYSCLK3
//  EDMA   -- CPU CLOCK Frequence
//  Timer  -- 1/4 of SYSCLK1
//  More detailed information in SPRU233a.pdf
//  Input clock CLKIN = 40MHz
//  SYSCLK1(DSP core) = 200MHz
//  SYSCLK2           = 100MHz
//  SYSCLK3           = 100MHz
//  CLKOUT3           = 2MHz
//
//  PLLOUT            = 400MHz
//  PLLREF            = 50MHz
//-----------------------------------------------------------------------------
void pll_initial(void)
{
	int    i,exceedT;

	*(unsigned volatile int *)PLLCSR  = 0x0;	 // Must enter Bypass mode first
	for(i=0;i<32;i++);	                         // Wait 4 cycles of the slowest of PLLOUT,

	*(unsigned volatile int *)PLLCSR  = 0x8;	 // Reset and disable the PLL

	*(unsigned volatile int *)PLLDIV0 = 0x8000;	 // PLLREF=40M/1=40M
	*(unsigned volatile int *)PLLM    = 0x0a;	 // PLLOUT=40M*10=400M
	*(unsigned volatile int *)OSCDIV1 = 0x800d;  // CLKOUT3=40M/14=2.857M
	for(i=0;i<64;i++);	                         // Wait 8 cycles of the slowest of the old and new SYSCLK1-3 clock rates

	*(unsigned volatile int *)PLLDIV3 = 0x8003;  // SYSCLK3=400M/4=100M
	for(i=0;i<64;i++);	                         // Wait 8 cycles of the slowest of the old and new SYSCLK1-3 clock rates

	*(unsigned volatile int *)PLLDIV2 = 0x8003;  // SYSCLK2=400M/4=100M,must be the half of f_CORE,must change before D1 when descend frequence
	for(i=0;i<64;i++);	                         // Wait 8 cycles of the slowest of the old and new SYSCLK1-3 clock rates

    *(unsigned volatile int *)PLLDIV1 = 0x8001;	 // SYSCLK1(DSP core)=400M/2=200M,
	for (i=0;i<4096;i++);			             // Wait for PLL to properly reset,512 CLKIN cycles ??

	*(unsigned volatile int *)PLLCSR  = 0x0;	 // Bring PLL out of reset

    exceedT = 0;
	while (((*((unsigned volatile int *)PLLCSR) & 0x40)==0)&&((exceedT++)<4096));
	                                             //Wait for PLL to lock, STABLE=1

	*(unsigned volatile int *)PLLCSR  = 0x1;	 // Enable inter PLL
}

