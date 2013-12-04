#ifndef _EMIF_H_
#define _EMIF_H_

//Define EMIF Registers
#define  EMIF_GBLCTL    0x1800000	// Address of EMIF global control
#define  EMIF_CE0CTL	0x1800008	// Address of EMIF CE0 control
#define  EMIF_CE1CTL	0x1800004	// Address of EMIF CE1 control
#define  EMIF_CE2CTL	0x1800010	// Address of EMIF CE2 control
#define  EMIF_CE3CTL	0x1800014	// Address of EMIF CE3 control
#define  EMIF_SDCTL	    0x1800018	// Address of EMIF SDRAM control
#define  EMIF_SDTIM	    0x180001c	// Address of EMIF SDRAM refresh control
#define  EMIF_SDEXT	    0x1800020	// Address of EMIF SDRAM extension

//Define the Device Register
#define	 DEVCFG		    0x19c0200	//Device Configuration register

//define flash sector SA_x
#define  FLASH_SA0      0x00000
#define  FLASH_SA1      0x08000
#define  FLASH_SA2      0x10000
#define  FLASH_SA3      0x18000
#define  FLASH_SA4      0x20000
#define  FLASH_SA5      0x28000
#define  FLASH_SA6      0x30000
#define  FLASH_SA7      0x38000
#define  FLASH_SA8      0x40000
#define  FLASH_SA9      0x48000
#define  FLASH_SA10     0x50000
#define  FLASH_SA11     0x58000
#define  FLASH_SA12     0x60000
#define  FLASH_SA13     0x68000
#define  FLASH_SA14     0x70000
#define  FLASH_SA15     0x78000
#define  FLASH_SA16     0x7c000
#define  FLASH_SA17     0x7d000
#define  FLASH_SA18     0x7e000

void          emif_ini(void);
void          emif_decvfg_int(void);
void          emif_sdram_setup(void);
unsigned char emif_sdram_test_fill(unsigned int sdram_address,unsigned int length);
unsigned char emif_sdram_test_clear(unsigned int sdram_address,unsigned int length);
unsigned char emif_flash_program_test(unsigned int flash_address,unsigned int length);
unsigned char emif_flash_sector_erase_toggle(unsigned int flash_address,unsigned int SA_n);
unsigned char emif_flash_sector_erase(unsigned int flash_address,unsigned int SA_n);
void          emif_flash_programing_poll(unsigned short *flash_address_l,unsigned short ori_data);
void          emif_write_flash_in_16bits(unsigned int flash_address,unsigned short *target_address,unsigned short content);
void 			emif_unlock_flash_erase();
void 			emif_lock_flash_erase();
void 			emif_unlock_flash_program();
void 			emif_lock_flash_program();

#endif

