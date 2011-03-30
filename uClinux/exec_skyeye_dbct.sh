#/bin/bash
cd $1
skyeye_path=$2
test -e linux &&	${skyeye_path}/skyeye_main.py -e linux -c skyeye_dbct.conf
test -e vmlinux &&	${skyeye_path}/skyeye_main.py -e vmlinux -c skyeye_dbct.conf
test -e vmlinux.large &&  ${skyeye_path}/skyeye_main.py -e  vmlinux.large -c skyeye_dbct.conf 
test -e vmlinux-8-332 &&  ${skyeye_path}/skyeye_main.py -e  vmlinux-8-332 -c skyeye_dbct.conf
