#/bin/bash
cd $1
skyeye_path=$2
test -e hello.exe &&	${skyeye_path}/skyeye -e hello.exe -c skyeye.conf
