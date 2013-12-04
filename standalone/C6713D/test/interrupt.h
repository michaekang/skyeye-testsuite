#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#define  MUXH            0x19c0000   // Address of Interrupt Multiplexer High(INT10 - 15)
#define  MUXL            0x19c0004   // Address of Interrupt Multiplexer Low (INT4 - 9)
#define  EXTPOL          0x19c0008   // Address of External interrupt polarity Sets

//----------------------------------------------------------
//-- save restore IRP
//----------------------------------------------------------
#define SAVE_CREG(temp_XXX,CREG_XXX)                                          \
        do {                                                                  \
               temp_XXX = CREG_XXX;                                           \
           } while (0)

//#define RESTORE_CREG(CREG_XXX,temp_XXX)                                       \
//        do {                                                                  \
//               CREG_XXX = temp_XXX;                                           \
//           } while (0)
#define RESTORE_CREG(CREG_XXX,temp_XXX)      ((CREG_XXX) = (temp_XXX))

#define SAVE_CLEAR_CSR_GIE_BIT(CSR_GIE_BIT)                                   \
        do {                                                                  \
               CSR_GIE_BIT = CSR&0x01;                                        \
               CSR = CSR & 0xfffe;                                            \
           } while (0)

#define SET_CSR_GIE_BIT(CSR_GIE_BIT)                                          \
        do {                                                                  \
               CSR = CSR | CSR_GIE_BIT;                                       \
           } while (0)

void           interrupt_initial(void);
unsigned char  interrupt_hook(void *isr_add,int cpu_intr);
interrupt void interrupt_can1_rxd_isr();
interrupt void interrupt_can2_rxd_isr();
interrupt void interrupt_timer0_selftest_isr();


#endif

