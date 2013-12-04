#include"math.h"
#include"c6x.h"

#include "struct.h"
#include "can.h"
#include "common.h"
#include "emif.h"
#include "interrupt.h"
#include "SJA1000.h"
#include "pll.h"
#include "regs.h"


#include "timer.h"


unsigned char erase_sequence[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char program_sequence[3] = {0x00,0x00,0x00};
//----------------------------------------------------------------------------
//-- DSP EMIF initianization:Set the parametre of GLOBAL,CE0-CE3
//   CE0  -- SDRAM(128Mb) 32-bit-wide
//   CE1  -- Asyncronize Flash ROM 8-bit-wide
//   CE2  -- null
//   CE3  -- null
//   EMIF CLOCK source:SYSCLK3 = 100MHz
//   attention : in this system flash designed for AMD_29LV800T 512K X 16
//-----------------------------------------------------------------------------
void emif_ini(void)
{
	*(unsigned volatile int *)EMIF_GBLCTL = 0x37f8;
    *(unsigned volatile int *)EMIF_CE0CTL = 0xffffff33;
    *(unsigned volatile int *)EMIF_CE1CTL = 0x02208812;    //Used for FLASH ROM
}

//----------------------------------------------------------------------------
//-- DSP DEVICE initianization
//   EKSRC(BIT4)    :EMIF input clock source is SYSCLK3(100MHz)(default)
//   TOUT1SEL(BIT3) :Output pin(Tout1) as a Timer1 output(default)
//   TOUT0SEL(BIT2) :Output pin(Tout0) as a Timer0 output(default)
//-----------------------------------------------------------------------------
void emif_decvfg_int(void)
{
    *(unsigned volatile int *)DEVCFG  = 0x00;
}

//----------------------------------------------------------------------------
//-- SDRAM_SETUP SDRAM MT48LC4M32B2-TG6 devices (32-bit x 4 banks x 1024K) parts = 16MB Parameter
//   EMIF_SDCTL:EMIF SDRAM CONTROL REGISTER
//   EMIF_SDTIM:EMIF SDRAM TIMING REGISTER
//   EMIF_SDEXT:EMIF SDRAM EXTENSION REGISTER
//----------------------------------------------------------------------------
void emif_sdram_setup(void)
{
	*(unsigned volatile int *)EMIF_SDCTL = 0x57116000;	   //0x07227000
	*(unsigned volatile int *)EMIF_SDTIM = 0x61a;	       //0x200061a
	*(unsigned volatile int *)EMIF_SDEXT = 0x54529;
}

//----------------------------------------------------------------------------
//-- SDRAM test
//   fille SDRAM from 0x00 to 0xff in cycle
//   read back from SDRAM and verify , abnormal return 0x00,otherwrise return 0x01
//-----------------------------------------------------------------------------
unsigned char emif_sdram_test_fill(unsigned int sdram_address,unsigned int length)
{
    unsigned int    fill_char;
    unsigned char   *fill_address,read_back_char;

    fill_address = (unsigned char *)sdram_address;
    for(fill_char=0;fill_char<length;fill_char++)
    {
        *fill_address = (unsigned char)(fill_char&0xff);
        fill_address++;
    }

    fill_address = (unsigned char *)sdram_address;
    for(fill_char=0;fill_char<length;fill_char++)
    {
        read_back_char = *fill_address&0xff;
        if(((fill_char&0xff)&read_back_char) != read_back_char)
        {
            return 0x01;
        }
        fill_address++;
    }

    return 0x00;
}

//----------------------------------------------------------------------------
//-- SDRAM test
//   fille SDRAM all 0x00
//   read back from SDRAM and verify , abnormal return 0x00,otherwrise return 0x01
//-----------------------------------------------------------------------------
unsigned char emif_sdram_test_clear(unsigned int sdram_address,unsigned int length)
{
    unsigned int    fill_char;
    unsigned char   *fill_address,read_back_char;

    fill_address = (unsigned char *)sdram_address;
    for(fill_char=0;fill_char<length;fill_char++)
    {
        *fill_address = 0x00;
        fill_address++;
    }

    fill_address = (unsigned char *)sdram_address;
    for(fill_char=0;fill_char<length;fill_char++)
    {
        read_back_char = *fill_address&0xff;
        if(read_back_char != 0x00)
        {
            return 0x01;
        }
        fill_address++;
    }

    return 0x00;
}

//----------------------------------------------------------------------------
//-- FLASH and PROGRAM CRC test
//   read back from flash and calculate CRC
//   abnormal return 0x00,otherwrise return 0x01
//-----------------------------------------------------------------------------
extern unsigned short  CRC_TABLE[256];

unsigned char emif_flash_program_test(unsigned int flash_address,unsigned int length)
{
    unsigned short  CRC_inside,CRC,tmp;
    unsigned char   *content_address,read_back_char;
    int             i;

    CRC = 0;
    CRC_inside = *(unsigned short *)(flash_address + length - 32 - 2);

    content_address = (unsigned char *)flash_address;
    for(i=0;i<(length - 32 - 2);i++)
    {
        read_back_char = *content_address&0xff;
        content_address++;
        tmp = ((CRC>>8)&0xff)^read_back_char;
        CRC = ((CRC<<8)&0xff00)^CRC_TABLE[tmp];
    }

    if(CRC != CRC_inside)
    {
        return 0x01;
    }

    return 0x00;
}

//----------------------------------------------------------------------------
//-- FLASH sector erase toggle
//   if sector erase in progress,toggling
//   else toggle stop
//-----------------------------------------------------------------------------
unsigned char emif_flash_sector_erase_toggle(unsigned int flash_address,unsigned int SA_n)
{
    unsigned short   *flash_address_l;
    unsigned short   toggle[4];
    unsigned char    quit,res;
    int              index;
    unsigned int     start_t0;

    res = 0x00;
    flash_address_l = (unsigned short *)(flash_address + SA_n);
    quit = 0x00;
    for(index = 0;index < 4; index++)
    {
        toggle[index] = 0xff;
    }
    index = 0;

    start_t0 = timer_read_timer(TIMER1);
    for(;(!quit)&&(timer_counter_sub(TIMER1,(unsigned int *)&start_t0,5000000)<150000);)
    {
        toggle[index] = (*flash_address_l)&0x40;
        index++;
        if(index>=4)
        {
            index= 0;
        }
        if((toggle[0] == toggle[1]) && (toggle[1] == toggle[2]) && (toggle[2] == toggle[3]))
        {
            quit = 0x55;
            res = 0x01;
        }
    }

    return res;
}

//----------------------------------------------------------------------------
//-- FLASH sector erase
//   erase assume flash sector
//   pass return 0x01,fail return 0x00
//-----------------------------------------------------------------------------
unsigned char emif_flash_sector_erase(unsigned int flash_address,unsigned int SA_n)
{
    unsigned short   *flash_address_l;
	
    flash_address_l = (unsigned short *)(flash_address + (0x555<<1));
    *flash_address_l = (unsigned short)erase_sequence[0];
  
    flash_address_l = (unsigned short *)(flash_address + (0x2aa<<1));
    *flash_address_l = (unsigned short)erase_sequence[1]; 
      
    flash_address_l = (unsigned short *)(flash_address + (0x555<<1));
    *flash_address_l = (unsigned short)erase_sequence[2];
 
    flash_address_l = (unsigned short *)(flash_address + (0x555<<1));
    *flash_address_l = (unsigned short)erase_sequence[3];
     
   	flash_address_l = (unsigned short *)(flash_address + (0x2aa<<1));
   	*flash_address_l = (unsigned short)erase_sequence[4];

    flash_address_l = (unsigned short *)(flash_address + SA_n);
   	*flash_address_l = (unsigned short)erase_sequence[5];
  

    return(emif_flash_sector_erase_toggle(flash_address,SA_n));
}

//----------------------------------------------------------------------------
//-- FLASH program poll
//   DQ7 indicate true data
//-----------------------------------------------------------------------------
void  emif_flash_programing_poll(unsigned short *flash_address_l,unsigned short ori_data)
{
    unsigned int     start_t0;
    unsigned short   read_back;

    ori_data = ori_data & 0x80;
    start_t0 = timer_read_timer(TIMER1);
    read_back = (unsigned short)(*flash_address_l);
    for(;(((read_back&0x80) != ori_data) && (timer_counter_sub(TIMER1,(unsigned int *)&start_t0,5000000)<200));)
    {
        read_back = (unsigned short)(*flash_address_l);
    }
}

//----------------------------------------------------------------------------
//-- FLASH program by word
//-----------------------------------------------------------------------------
void emif_write_flash_in_16bits(unsigned int flash_address,unsigned short *target_address,unsigned short content)
{
    unsigned short   *flash_address_l;

   	flash_address_l = (unsigned short *)(flash_address + (0x555<<1));
    *flash_address_l = (unsigned short)program_sequence[0];

    flash_address_l = (unsigned short *)(flash_address + (0x2aa<<1));
    *flash_address_l = (unsigned short)program_sequence[1];
 
    flash_address_l = (unsigned short *)(flash_address + (0x555<<1));
    *flash_address_l = (unsigned short)program_sequence[2];
    
    *target_address = content;
    emif_flash_programing_poll(target_address,content);
}


void emif_unlock_flash_erase()
{
	erase_sequence[0] = 0xaa;
	erase_sequence[1] = 0x55;
	erase_sequence[2] = 0x80;
	erase_sequence[3] = 0xaa;
	erase_sequence[4] = 0x55;
	erase_sequence[5] = 0x30;
}
void emif_unlock_flash_program()
{
	program_sequence[0] = 0xaa;
	program_sequence[1] = 0x55;
	program_sequence[2] = 0xa0;
}

void emif_lock_flash_erase()
{
	erase_sequence[0] = 0x00;
	erase_sequence[1] = 0x00;
	erase_sequence[2] = 0x00;
	erase_sequence[3] = 0x00;
	erase_sequence[4] = 0x00;
	erase_sequence[5] = 0x00;
}
void emif_lock_flash_program()
{
	program_sequence[0] = 0x00;
	program_sequence[1] = 0x00;
	program_sequence[2] = 0x00;
}
