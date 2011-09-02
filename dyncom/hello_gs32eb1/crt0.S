#include <reg.h>

####################################
#   	crt0.S  for GODSON1 
####################################
#define sr			sw
#define lr			lw	
#define MTC0		mtc0
#define MFC0		mfc0
#define REGSZ		4
#define CACHELINE	16


#define SERIAL_BASE 0xb4000100
#define STKSIZE 	0x3000


#####################################
# 		startup code  Entry		    
#####################################
	.text

	.comm   stack, STKSIZE
	.set	at
	.globl 	start
	.ent 	start

start:						# This is the entry point of the BIOS ROM Image
	.globl 	__start
	.aent 	__start
__start:

	move	k0, zero

#
#	initialize cp0 registers
#
#	setup KSEG1 stack
#
	la      sp, stack+STKSIZE-24
    li      t0, K1BASE
    or      sp, sp, t0

#
#	init uart
#
	.set reorder
	li		a0, 0xb400010c
	li		a1, 0xb4000108

	li		a2, 651			# Baudrate = 9600
	sw		a2, 0(a0)
	li		a2, 15
	sw		a2, 0(a1)
	.set noreorder

#
#	Init&Flush the Cache of CPU
#
#	Re-set stack pointer for C code
#
	la      sp, stack+STKSIZE-24		# Re-Set stack pointer
	nop


####################################
#		Clean BSS sections         
####################################
	.set	reorder
zbss:	

#
#	clear bss
#
	la		v0, _sbss		# BSS section pre-compiled start in RAM
	la		v1, _ebss		# BSS section pre-compiled end in RAM
	or		v0, K1BASE
	or		v1, K1BASE
	
1:	.set	noreorder
	sw		$0, 0(v0)
	sw		$0, 4(v0)
	sw		$0, 8(v0)
	addu	v0, 16
	bltu	v0, v1, 1b
	sw		$0, -4(v0)		# use delay slot to fill 12(v0)


#####################################
# set stack pointer for C code       
#####################################
	la      sp, __SP_INIT	# Re-Set stack pointer
	la		t0, 1f			# Switch from K1 Seg to K0 Seg.
	j		t0
1:	nop

######################################
# 	Jump to normal BIOS startup code 	  
######################################
	nop
	la		a0, main
	jalr	a0
	nop
#
#	Main program stoped here, continue to download and debug	
#
    break
    break
    
1:	bal		1b
	j		start
    nop
	.end start

LEAF(__main)
	.set noreorder
	.set noat

    nop

	.set at
	.set reorder
	jr	ra
END(__main)
