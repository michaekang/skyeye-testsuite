#/bin/bash
cd $1
skyeye_path=$2
test -e linux &&	${skyeye_path}/skyeye -e linux -c skyeye.conf
test -e vmlinux &&	${skyeye_path}/skyeye -e vmlinux -c skyeye.conf
test -e image.elf &&  ${skyeye_path}/skyeye -e image.elf -c skyeye.conf 
test -e image.rom &&  ${skyeye_path}/skyeye -c skyeye.conf

