#/bin/bash
cd $1
skyeye_path=$2
test -e linux &&	${skyeye_path}/skyeye -n -e linux -c skyeye.conf
test -e vmlinux &&	${skyeye_path}/skyeye -n -e vmlinux -c skyeye.conf
test -e image.elf &&  ${skyeye_path}/skyeye -n -e image.elf -c skyeye.conf 
test -e image.rom &&  ${skyeye_path}/skyeye -n -c skyeye.conf

