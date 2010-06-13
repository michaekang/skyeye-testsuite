#!/bin/sh

TOP_DIR=`pwd`
SKYEYE_DIR_NAME="skyeye_dir"
SKYEYE_BRANCH_NAME="../source"
SKYEYE_DIR=${TOP_DIR}/${SKYEYE_DIR_NAME}
TIMESTAMP=`date +%F_%k_%M`
test_report="${TOP_DIR}/test_report_${TIMESTAMP}"

# if here exists skyeye branch, we will use skyeye branch to test our testsuite
if test -e $SKYEYE_BRANCH_NAME ; then
	rm -f -r $SKYEYE_DIR 
	ln -s $SKYEYE_BRANCH_NAME $SKYEYE_DIR
fi

if test -e $SKYEYE_DIR ; then
	if test -e $SKYEYE_DIR/skyeye ; then
		echo "We will use $SKYEYE_DIR/skyeye to run testsuite."
	else
		cd $SKYEYE_DIR && ./configure;make lib;make;sudo make install_lib;sudo make install
		cd $TOP_DIR
	fi
else
	echo "ERROR: can not find skyeye executable.You should put your skyeye distribution on $SKYEYE_DIR"
	exit -1
fi
if test -e linux ; then 
	cd linux 
	expect  ./auto_test $SKYEYE_DIR $test_report
	cd $TOP_DIR
fi
if test -e uClinux ; then
        cd uClinux && expect ./auto_test $SKYEYE_DIR $test_report
	cd $TOP_DIR
else
	echo "can not find uClinux directory for test."
fi
if test -e rtems ; then
        cd rtems && expect ./auto_test $SKYEYE_DIR $test_report
	cd $TOP_DIR
fi
