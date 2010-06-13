/*
 * hello.c
 * just a function used to output "helloworld" to uart 
 * 
 * author: SU Hang
 * date:   2004-08-28	
 */
void hello(void)
{	
	int i;
	char * hellostr="helloworld";
	long* paddr=(long*)0xfffd001c;
	
	for(i=0;i<10;i++)
	{
		* paddr=hellostr[i];
	}
	putc('d');
	while(1)
	;
	return;	
}

void putc(char c){
 long* paddr=(long*)0xfffd001c;
	* paddr= c;
}
