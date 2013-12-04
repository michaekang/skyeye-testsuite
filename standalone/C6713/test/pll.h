#ifndef _PLL_H_
#define _PLL_H_

#define	PLLPID		0x1B7C000	//Peripheral identification register (PID)
#define	PLLCSR		0x1B7C100	//PLL control/status register
#define	PLLM 		0x1B7C110	//PLL multiplier control register
#define	PLLDIV0 	0x1B7C114	//PLL controller divider 0 register
#define	PLLDIV1 	0x1B7C118	//PLL controller divider 1 register
#define	PLLDIV2 	0x1B7C11c	//PLL controller divider 2 register
#define	PLLDIV3 	0x1B7C120	//PLL controller divider 3 register
#define	OSCDIV1 	0x1B7C124	//Oscillator divider 1 register

void pll_initial(void);

#endif

