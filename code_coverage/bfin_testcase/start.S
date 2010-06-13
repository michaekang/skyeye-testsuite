/*
 *  start.S 
 *  very simple code for blackfin 
 *  import from Su Hang
 *
 *  author: Michael.Kang 
 *  date:   2006-12-29 
 */
.global begin 	

begin:
	r2.l = 0x0010;
        r2.h = 0x0000;
	sp = r2;
	call	_hello
	JUMP 	begin
			
