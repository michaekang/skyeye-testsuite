/*
 * hello.c
 * just a function used to output "helloworld" to uart 
 * 
 * author: SU Hang
 * date:   2004-08-28	
 */
void hello(void)
{	
	char * hellostr="helloworld";
	unsigned long * paddr=( unsigned long *)0xffc00400;
	int i;
	for(i=0;i<10;i++)
	{
		* paddr=hellostr[i];
	}

	while(1);
	return;	
}

