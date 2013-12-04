-c
-x
-heap  0x2000
-stack 0x2000
-m	link.map 



MEMORY
{

    boot_load:	o = 00000000h   l = 00000400h
	ARAM:       o = 00000400h   l = 00000400h
    IRAM:       o = 00000800h   l = 0003F000h
 	ORAM:		o = 80000000h   l = 007fFFFFh
 }

SECTIONS
{
    .boot_load  > 		boot_load
	.vectors	>       ARAM
	.bss        >       ARAM
	.text       >       IRAM
    .stack      >       IRAM
    .cinit      >       ORAM
    .const      >       ORAM
    .data       >       ORAM
    .switch     >       ORAM
	.far        >       ORAM
	.cio        >       ORAM
    .sysmem     >       ORAM
    .tables     >       ORAM

}
