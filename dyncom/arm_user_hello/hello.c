/*
 * hello.c
 * just a function used to output "helloworld" to uart 
 * 
 * author: SU Hang
 * date:   2004-08-28	
 */
#include<stdio.h>

#define BOGO_MIPS 100
int main()
{
	int i = 0;
	while(1){
		for( i = 0; i < BOGO_MIPS; i ++)
			;		
		printf("hello\n");	
	}
}

