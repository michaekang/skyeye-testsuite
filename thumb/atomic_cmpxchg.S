1:      ldrex   r3, [r2]
        subs    r3, r3, r0
        strexeq r3, r1, [r2]
        teqeq   r3, #1
        beq     1b
        rsbs    r0, r3, #0
	bx      lr

