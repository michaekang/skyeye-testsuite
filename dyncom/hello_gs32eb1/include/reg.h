
#ifndef __LX_REG_H__
#define __LX_REG_H__


#include "mips/cpu.h"
#include "mips/prid.h"
	
#include "mips/mips.h"

/* MIPS pt_regs offsets. */
#define PT_R0     24
#define PT_R1     28
#define PT_R2     32
#define PT_R3     36
#define PT_R4     40
#define PT_R5     44
#define PT_R6     48
#define PT_R7     52
#define PT_R8     56
#define PT_R9     60
#define PT_R10    64
#define PT_R11    68
#define PT_R12    72
#define PT_R13    76
#define PT_R14    80
#define PT_R15    84
#define PT_R16    88
#define PT_R17    92
#define PT_R18    96
#define PT_R19    100
#define PT_R20    104
#define PT_R21    108
#define PT_R22    112
#define PT_R23    116
#define PT_R24    120
#define PT_R25    124
#define PT_R26    128
#define PT_R27    132
#define PT_R28    136
#define PT_R29    140
#define PT_R30    144
#define PT_R31    148
#define PT_LO     152
#define PT_HI     156
#define PT_EPC    160
#define PT_BVADDR 164
#define PT_STATUS 168
#define PT_CAUSE  172
#define PT_SIZE   176

/* MIPS task_struct offsets. */
#define TASK_STATE         0
#define TASK_FLAGS         4
#define TASK_SIGPENDING    8
#define TASK_NEED_RESCHED  20
#define TASK_COUNTER       24
#define TASK_PRIORITY      28
#define TASK_MM            928

/* MIPS specific thread_struct offsets. */
#define THREAD_REG16   560
#define THREAD_REG17   564
#define THREAD_REG18   568
#define THREAD_REG19   572
#define THREAD_REG20   576
#define THREAD_REG21   580
#define THREAD_REG22   584
#define THREAD_REG23   588
#define THREAD_REG29   592
#define THREAD_REG30   596
#define THREAD_REG31   600
#define THREAD_STATUS  604
#define THREAD_FPU     608
#define THREAD_BVADDR  872
#define THREAD_BUADDR  876
#define THREAD_ECODE   880
#define THREAD_TRAPNO  884
#define THREAD_PGDIR   888
#define THREAD_MFLAGS  892
#define THREAD_CURDS   896
#define THREAD_TRAMP   900
#define THREAD_OLDCTX  904
#define THREAD_DSEEPC  908
#define THREAD_DSEAERPC 912

/* Linux mm_struct offsets. */
#define MM_COUNT      16
#define MM_PGD        12
#define MM_CONTEXT    36

/* Linux sigcontext offsets. */
#define SC_REGMASK    0
#define SC_STATUS     4
#define SC_PC         8
#define SC_REGS       16
#define SC_FPREGS     272
#define SC_OWNEDFP    528
#define SC_FPC_CSR    532
#define SC_FPC_EIR    536
#define SC_SSFLAGS    540
#define SC_MDHI       544
#define SC_MDLO       552
#define SC_CAUSE      560
#define SC_BADVADDR   564
#define SC_SIGSET     568

#define SAVE_AT                                          \
		sw	$1, PT_R1(sp)

#define SAVE_TEMP                                        \
		mfhi	v1;                              \
		sw	$8, PT_R8(sp);                   \
		sw	$9, PT_R9(sp);                   \
		sw	v1, PT_HI(sp);                   \
		mflo	v1;                              \
		sw	$10,PT_R10(sp);                  \
		sw	$11, PT_R11(sp);                 \
		sw	v1,  PT_LO(sp);                  \
		sw	$12, PT_R12(sp);                 \
		sw	$13, PT_R13(sp);                 \
		sw	$14, PT_R14(sp);                 \
		sw	$15, PT_R15(sp);                 \
		sw	$24, PT_R24(sp)

#define SAVE_STATIC                                      \
		sw	$16, PT_R16(sp);                 \
		sw	$17, PT_R17(sp);                 \
		sw	$18, PT_R18(sp);                 \
		sw	$19, PT_R19(sp);                 \
		sw	$20, PT_R20(sp);                 \
		sw	$21, PT_R21(sp);                 \
		sw	$22, PT_R22(sp);                 \
		sw	$23, PT_R23(sp);                 \
		sw	$30, PT_R30(sp)

#define __str2(x) #x
#define __str(x) __str2(x)

#define save_static(frame)                               \
	__asm__ __volatile__(                            \
		"sw\t$16,"__str(PT_R16)"(%0)\n\t"        \
		"sw\t$17,"__str(PT_R17)"(%0)\n\t"        \
		"sw\t$18,"__str(PT_R18)"(%0)\n\t"        \
		"sw\t$19,"__str(PT_R19)"(%0)\n\t"        \
		"sw\t$20,"__str(PT_R20)"(%0)\n\t"        \
		"sw\t$21,"__str(PT_R21)"(%0)\n\t"        \
		"sw\t$22,"__str(PT_R22)"(%0)\n\t"        \
		"sw\t$23,"__str(PT_R23)"(%0)\n\t"        \
		"sw\t$30,"__str(PT_R30)"(%0)\n\t"        \
		: /* No outputs */                       \
		: "r" (frame))

#define SAVE_SOME                                        \
		.set	push;                            \
		.set	reorder;                         \
		mfc0	k0,C0_STATUS;                    \
		sll	k0, 3;     /* extract cu0 bit */ \
		.set	noreorder;                       \
		bltz	k0, 8f;                          \
		 move	k1, sp;                          \
8:                                                       \
		move	k0, sp;                          \
		subu	sp, k1, PT_SIZE;                 \
		sw	k0, PT_R29(sp);                  \
		sw	$3, PT_R3(sp);                   \
		sw	$0, PT_R0(sp);			 \
		mfc0	v1, C0_STATUS;                  \
		sw	$2, PT_R2(sp);                   \
		sw	v1, PT_STATUS(sp);               \
		sw	$4, PT_R4(sp);                   \
		mfc0	v1, C0_CAUSE;                   \
		sw	$5, PT_R5(sp);                   \
		sw	v1, PT_CAUSE(sp);                \
		sw	$6, PT_R6(sp);                   \
		mfc0	v1, C0_EPC;                     \
		sw	$7, PT_R7(sp);                   \
		sw	v1, PT_EPC(sp);                  \
		sw	$25, PT_R25(sp);                 \
		sw	$28, PT_R28(sp);                 \
		sw	$31, PT_R31(sp);                 \
		ori	$28, sp, 0x1fff;                 \
		xori	$28, 0x1fff;                     \
		.set	pop


#define SAVE_ALL                                         \
		SAVE_SOME;                               \
		SAVE_AT;                                 \
		SAVE_TEMP;                               \
		SAVE_STATIC

#define RESTORE_AT                                       \
		lw	$1,  PT_R1(sp);                  \

#define RESTORE_SP                                       \
		lw	sp,  PT_R29(sp)

#define RESTORE_TEMP                                     \
		lw	$24, PT_LO(sp);                  \
		lw	$8, PT_R8(sp);                   \
		lw	$9, PT_R9(sp);                   \
		mtlo	$24;                             \
		lw	$24, PT_HI(sp);                  \
		lw	$10,PT_R10(sp);                  \
		lw	$11, PT_R11(sp);                 \
		mthi	$24;                             \
		lw	$12, PT_R12(sp);                 \
		lw	$13, PT_R13(sp);                 \
		lw	$14, PT_R14(sp);                 \
		lw	$15, PT_R15(sp);                 \
		lw	$24, PT_R24(sp)

#define RESTORE_STATIC                                   \
		lw	$16, PT_R16(sp);                 \
		lw	$17, PT_R17(sp);                 \
		lw	$18, PT_R18(sp);                 \
		lw	$19, PT_R19(sp);                 \
		lw	$20, PT_R20(sp);                 \
		lw	$21, PT_R21(sp);                 \
		lw	$22, PT_R22(sp);                 \
		lw	$23, PT_R23(sp);                 \
		lw	$30, PT_R30(sp)

#define RESTORE_SOME                                     \
		.set	push;                            \
		.set	reorder;                         \
		mfc0	t0, C0_STATUS;                  \
		.set	pop;                             \
		ori	t0, 0x1f;                        \
		xori	t0, 0x1f;                        \
		mtc0	t0, C0_STATUS;                  \
		li	v1, 0xff00;                      \
		and	t0, v1;				 \
		lw	v0, PT_STATUS(sp);               \
		nor	v1, $0, v1;			 \
		and	v0, v1;				 \
		or	v0, t0;				 \
		mtc0	v0, C0_STATUS;                  \
		lw	v1, PT_EPC(sp);                  \
		mtc0	v1, C0_EPC;                     \
		lw	$31, PT_R31(sp);                 \
		lw	$28, PT_R28(sp);                 \
		lw	$25, PT_R25(sp);                 \
		lw	$7,  PT_R7(sp);                  \
		lw	$6,  PT_R6(sp);                  \
		lw	$5,  PT_R5(sp);                  \
		lw	$4,  PT_R4(sp);                  \
		lw	$3,  PT_R3(sp);                  \
		lw	$2,  PT_R2(sp)

#define RESTORE_ALL                                      \
		RESTORE_SOME;                            \
		RESTORE_AT;                              \
		RESTORE_TEMP;                            \
		RESTORE_STATIC;                          \
		RESTORE_SP

/*
 * Move to kernel mode and disable interrupts.
 * Set cp0 enable bit as sign that we're running on the kernel stack
 */
#define CLI                                             \
		mfc0	t0,C0_STATUS;                  \
		li	t1,ST0_CU0|0x1f;                \
		or	t0,t1;                          \
		xori	t0,0x1f;                        \
		mtc0	t0,CP0_STATUS

/*
 * Move to kernel mode and enable interrupts.
 * Set cp0 enable bit as sign that we're running on the kernel stack
 */
#define STI                                             \
		mfc0	t0,C0_STATUS;                  \
		li	t1,ST0_CU0|0x1f;                \
		or	t0,t1;                          \
		xori	t0,0x1e;                        \
		mtc0	t0,C0_STATUS

/*
 * Just move to kernel mode and leave interrupts as they are.
 * Set cp0 enable bit as sign that we're running on the kernel stack
 */
#define KMODE                                           \
		mfc0	t0,C0_STATUS;                  \
		li	t1,ST0_CU0|0x1e;                \
		or	t0,t1;                          \
		xori	t0,0x1e;                        \
		mtc0	t0,C0_STATUS

#endif	/* __LX_REG_H__  */