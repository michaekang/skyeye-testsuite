#/bin/bash
cd $1
skyeye_path=$2
test -e linux &&	${skyeye_path}/skyeye_main.py -n -e linux -c skyeye.conf
test -e vmlinux &&	${skyeye_path}/skyeye_main.py -n -e vmlinux -c skyeye.conf
test -e vmlinux.large &&  ${skyeye_path}/skyeye_main.py -n -e  vmlinux.large -c skyeye.conf 
test -e vmlinux-8-332 &&  ${skyeye_path}/skyeye_main.py -n -e  vmlinux-8-332 -c skyeye.conf
