/* --------------------------------------------------------------------------
 * Simple bootloader for running uClinux
 *
 * Written by Anthony Lee <don.anthony.lee@gmail.com> at 2007
 *
 * This program is free software; it may be used and distributed according to
 * the terms of The MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * File: bootloader.S
 *
 * --------------------------------------------------------------------------*/

#define UCLINUX_ZLOADADDR	0x00001000
#define UCLINUX_VECTORS_BASE	0x0c000000

.section .text
	.align 4
	.global boot_code
	.type boot_code, function

boot_code:
	ldr	pc, = UCLINUX_ZLOADADDR			/* 0x00000000: jump to load address of uClinux */
	ldr	pc, = UCLINUX_VECTORS_BASE + 0x4	/* 0x00000004: jump to Undefined Instruction Handler of uClinux */
	ldr	pc, = UCLINUX_VECTORS_BASE + 0x8	/* 0x00000008: jump to Software Interrupt Handler of uClinux */
	ldr	pc, = UCLINUX_VECTORS_BASE + 0xc	/* 0x0000000c: jump to Prefetch Abort Handler of uClinux */
	ldr	pc, = UCLINUX_VECTORS_BASE + 0x10	/* 0x00000010: jump to Data Abort Handler of uClinux */
	b	.					/* 0x00000014: */
	ldr	pc, = UCLINUX_VECTORS_BASE + 0x18	/* 0x00000018: jump to IRQ Handler of uClinux */
	ldr	pc, = UCLINUX_VECTORS_BASE + 0x1c	/* 0x0000001c: jump to FIQ Handler of uClinux */

