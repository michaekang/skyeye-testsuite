#!/bin/sh
# This shell is for testing skyeye-testsuite automatically.

#If you have not compile skyeye, you should set SKYEYE_SOURCE.
SKYEYE_SOURCE="Delete me and fill your absolute path of skeye source here if you need."

#If you configure skyeye with "--prefix" option,you should execute the script with the absolute "prefix" path as the first parameter. For example,if you execute command "./configure --prefix=$HOME/skyeye" then you should execute command "./test_all.sh $HOME/skyeye".
PREFIX_DIR=$1
ARG2=$2

#Initialize some variables
TOP_DIR=`pwd`
SKYEYE_DIR_NAME="skyeye_dir"
SKYEYE_OPT="/opt/skyeye"
SKYEYE_DIR="${TOP_DIR}/${SKYEYE_DIR_NAME}/bin"
TIMESTAMP=`date +%F_%0k_%0M`
test_report="${TOP_DIR}/test_report_${TIMESTAMP}"
OS=linux

if [ $ARG2 ]
then
	if [ $ARG2 = "windows" ]
	then
		OS=windows
	else
		echo "args2 is wrong format"
	fi
fi

#If skyeye has installed with by defult, we will use the installed skyeye to test 
#testsuite. If not, we need compile and install skyeye in skyeye source path at first.
if test -e ${PREFIX_DIR}/bin/skyeye ; then
	SKYEYE_DIR=${PREFIX_DIR}/bin
	echo "We will use ${SKYEYE_DIR}/skyeye to run testsuite."
elif test -e ${SKYEYE_OPT}/bin/skyeye ; then
	SKYEYE_DIR=${SKYEYE_OPT}/bin
	echo "We will use ${SKYEYE_DIR}/skyeye to run testsuite."
elif test -e $SKYEYE_SOURCE ; then
	cd $SKYEYE_SOURCE && ./configure --prefix=$SKYEYE_DIR;make lib;make; make install_lib; make install
	echo "We will use ${SKYEYE_DIR}/skyeye to run testsuite."
else	
	echo "ERROR: can not find skyeye executable or source."
	echo "Tips: Please confirm you have downloaded skyeye or installed \n      skyeye correctly. If so, read the README please."
	exit -1
fi

if test -e linux ; then 
	cd linux 
	expect  ./auto_test $SKYEYE_DIR $test_report $OS
	cd $TOP_DIR
fi
if test -e uClinux ; then
        cd uClinux && expect ./auto_test $SKYEYE_DIR $test_report $OS
	cd $TOP_DIR
else
	echo "can not find uClinux directory for test."
fi
if test -e rtems ; then
        cd rtems && expect ./auto_test $SKYEYE_DIR $test_report $OS
	cd $TOP_DIR
fi
