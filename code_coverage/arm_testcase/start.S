/*
 *  start.S 
 *  very simple code for ARM 7TDMI 
 *
 *  author: SU Hang 
 *  date:   2004-08-28 
 */
 	

#define MODE_SVC 0x13
#define I_BIT   0x80
	
.text
	.align 4
	.global begin
	.type begin, function

begin:
	
	/*disable I-bit*/
	mov     r0, #I_BIT|MODE_SVC
	msr     cpsr_c, r0

	mov r0, #0x10000000
	add r0, r0, #0x4000
	mov r1, #0x1000000
	add r1, r1, #0x8000
	str     r0, [r1]
/*
	mov r0, #0x0
	add r0, r0, 0x4000
	mov r1, #0x1000000
	add r1, r1, #0x8000
	strb     r0, [r1]
*/
	mov r0, #0x0

	mov r1, #0x1000000
	add r1, r1, #0x8000
	ldrb     r0, [r1]

	mov	r1,#0xd2
	sub	r2,r0,r1
	ldr 	sp, =irq_stack           @ set sp_irq = irq_stack
	bl	hello
	b	begin
			
.data
	.align  4
irq_stack:
	.space	4096

