################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/ti/ccsv5/tools/compiler/c6000_7.4.2

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"D:/qingniao/forQinghua/test/Debug/timer.obj" \
"D:/qingniao/forQinghua/test/Debug/pll.obj" \
"D:/qingniao/forQinghua/test/Debug/myboot.obj" \
"D:/qingniao/forQinghua/test/Debug/interrupt.obj" \
"D:/qingniao/forQinghua/test/Debug/emif.obj" \
"D:/qingniao/forQinghua/test/Debug/common.obj" \
"D:/qingniao/forQinghua/test/Debug/VECTORS.obj" \
"D:/qingniao/forQinghua/test/Debug/SJA1000.obj" \
"D:/qingniao/forQinghua/test/Debug/CAN.obj" \
"D:/qingniao/forQinghua/test/Debug/C67SPIM.obj" \
"C:/Users/ksh/Downloads/test/test_LNK.CMD" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: C:/Users/ksh/Downloads/test/test/test/../../test/Debug/test.out

# Tool invocations
C:/Users/ksh/Downloads/test/test/test/../../test/Debug/test.out: $(OBJS) $(CMD_UPPER_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"E:/ti/ccsv5/tools/compiler/c6000_7.4.2/bin/cl6x" -mv6710 --abi=coffabi -g --define="_DEBUG" --display_error_number --diag_wrap=off --obj_directory="D:/qingniao/forQinghua/test/Debug" -z -m"C:/Users/ksh/Downloads/test/test/Debug/test.map" -i"E:/ti/ccsv5/tools/compiler/c6000_7.4.2/lib" -i"E:/ti/ccsv5/tools/compiler/c6000_7.4.2/include" -i"C:/Users/ksh/Downloads/test/test/test" -i"C:/Users/ksh/Downloads/test/test" -i"/lib" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="test_linkInfo.xml" --rom_model -o "C:/Users/ksh/Downloads/test/test/test/../../test/Debug/test.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C6000_EXECUTABLE_OUTPUTS__QUOTED) "C:\Users\ksh\Downloads\test\test\Debug\test.out"
	-$(RM) "VECTORS.pp" 
	-$(RM) "C67SPIM.pp" "CAN.pp" "SJA1000.pp" "emif.pp" "interrupt.pp" "pll.pp" "timer.pp" 
	-$(RM) "common.pp" 
	-$(RM) "D:\qingniao\forQinghua\test\Debug\C67SPIM.obj" "D:\qingniao\forQinghua\test\Debug\CAN.obj" "D:\qingniao\forQinghua\test\Debug\SJA1000.obj" "D:\qingniao\forQinghua\test\Debug\VECTORS.obj" "D:\qingniao\forQinghua\test\Debug\common.obj" "D:\qingniao\forQinghua\test\Debug\emif.obj" "D:\qingniao\forQinghua\test\Debug\interrupt.obj" "D:\qingniao\forQinghua\test\Debug\myboot.obj" "D:\qingniao\forQinghua\test\Debug\pll.obj" "D:\qingniao\forQinghua\test\Debug\timer.obj" 
	-$(RM) "myboot.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
