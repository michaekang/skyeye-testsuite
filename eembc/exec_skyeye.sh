#/bin/bash
cd $1
skyeye_path=$2
test -e cjpeg.bin && time ${skyeye_path}/skyeye -u -n -e cjpeg.bin -c skyeye.conf
