/*
 * robot/serial.c -- Uart driver for gs32eb1
 * copyright(c) 2005-05-20
 * Author: 		Tian Na (tiana_blx@163.com)
 * Revison: 	1.0 
 */

#define SERIAL_BASE   0xB4000100
#define SER_CMD       0x05
#define SER_DATA      0x00
#define SER_STAT	  0x04
#define TX_BUSY       0x20

#define TIMEOUT       0x3fff

static volatile unsigned char *const com1 = (unsigned char *) SERIAL_BASE;

void putch(const char c)
{
	unsigned char ch;
	int i = 0;

	do {
		ch = com1[SER_STAT];
		i++;

        if (i > TIMEOUT) {
			break;
		}
	} while (ch & 0x1);

	com1[SER_DATA] = c;
}

void puts(const char *cp)
{
    int i;
    i = 0;

    while (1) {
        if (cp[i] == '\n'){
            putch ('\r');
		}

        putch (cp[i]);

        i++;

        if (cp[i] == '\0'){
            break;
		}
    }

	putch('\r');
	putch('\n');
}
