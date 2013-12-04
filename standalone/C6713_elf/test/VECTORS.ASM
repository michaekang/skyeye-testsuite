     .ref      _c_int00
     

 
     .global   _istp
     .global   _RESET,_NMI,_RESV1,_RESV2
     .global   _INT4,_INT5,_INT6,_INT7
     .global   _INT8,_INT9,_INT10,_INT11
     .global   _INT12,_INT13,_INT14,_INT15
     .global   _unexp_int04,_unexp_int05
     .global   _unexp_int06,_unexp_int07
     .global   _unexp_int08,_unexp_int09
     .global   _unexp_int10,_unexp_int11
     .global   _unexp_int12,_unexp_int13
     .global   _unexp_int14,_unexp_int15

vector_entry .macro addr
    stw    .d2 b0,*--b15
 || mvkl   .S2 addr, b0
    mvkh   .S2 addr, b0
    ldw    .d2 *b0, b0
    nop    4
    b      .s2 b0
 || ldw    .d2 *b15++, b0
    nop    5
   .endm

 	 .sect ".vectors"
     .align 1024
_istp:
_RESET:
    mvkl   .s2 _c_int00, b0
    mvkh   .s2 _c_int00, b0
    b      .s2 b0
	nop    5
	nop
	nop
	nop
    nop
