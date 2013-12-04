#ifndef _REGS_H_
#define _REGS_H_

// define control registers
extern cregister volatile unsigned int AMR;     // Address Mode Register
extern cregister volatile unsigned int CSR;     // Control Status Register
extern cregister volatile unsigned int IFR;     // Interrupt Flag Register
extern cregister volatile unsigned int ISR;     // Interrupt Set Register
extern cregister volatile unsigned int ICR;     // Interrupt Clear Register
extern cregister volatile unsigned int IER;     // Interrupt Enable Register
extern cregister volatile unsigned int ISTP;    // Interrupt Service Tbl Ptr
extern cregister volatile unsigned int IRP;     // Interrupt Return Pointer
extern cregister volatile unsigned int NRP;     // Non-maskable Int Return Ptr
extern cregister volatile unsigned int IN;      // General Purpose Input Reg
extern cregister volatile unsigned int OUT;     // General Purpose Output Reg

#endif

