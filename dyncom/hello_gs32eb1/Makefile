PRJ_PATH = 
PRJ_NAME = hello
PRJ_OBJS = crt0.o main.o serial.o

INCFLAGS = -Iinclude

FIND_PATH   =
CONFIG_PATH = $(PRJ_PATH)
LCF_NAME    = linker.lcf
SIZE_FILE   = size
MEM_MAP     = map

BUILD_SPEC = default

ifeq ($(BUILD_SPEC), default)
CPU  =GODSON-I
TOOL =GNU
DEFAULT_RULE = $(PRJ_NAME).elf
endif

CROSS_COMPILE = mipsel-linux-

ifeq ($(BUILD_SPEC),default)
AR      = $(CROSS_COMPILE)ar
AS      = $(CROSS_COMPILE)as
CC      = $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
LD    	= $(CROSS_COMPILE)ld
NM		= $(CROSS_COMPILE)nm
OBJDUMP	= $(CROSS_COMPILE)objdump
OBJCOPY	= $(CROSS_COMPILE)objcopy
RANLIB	= $(CROSS_COMPILE)ranlib
SIZE	= $(CROSS_COMPILE)size
STRIP	= $(CROSS_COMPILE)strip
RM		= rm
MAKE	= make
endif

export	TOPDIR CROSS_COMPILE AS LD CC CPP AR NM \
		STRIP OBJCOPY OBJDUMP MAKE MAKEFILES GENKSYMS MODFLAGS PERL

#
# GS_CFLAGS   : C/C++ compiler's flags for GS
# GS_ASFLAGS  : ASM compiler's flags for GS
# GS_LDFLAGS  : loader's flags for GS
# GS_ARFLAGS  : archiver's flags for GS
#


INCL_FLAGS = -I include
GS_CFLAGS = -O0 -gdwarf-2 -c -Wall -G 0 -mips2 -mlong-calls -mmemcpy -mno-abicalls -nostdinc -fno-pic -static \
             -fno-builtin -DNULL=0
GS_ASFLAGS = -gdwarf-2 -O0 -Wall  
GS_LDFLAGS = -n -EL -T $(LCF_NAME) -Map $(MEM_MAP) $(LIB_PATH) 
GS_ARFLAGS = -ruvs
CONVFLAGS  = -vp -f bin

##### Library used
GS_LIBS= -lc -lm 
ALL_LIBS= $(GS_LIBS) $(EX_LIBS)

#
# These are real flags for compiler
#

CFLAGS	= $(GS_CFLAGS) $(INCL_FLAGS)
ASFLAGS	= $(GS_ASFLAGS) $(INCL_FLAGS)
LDFLAGS = $(GS_LDFLAGS)
ARFLAGS = $(GS_ARFLAGS)

# set searching directories for dependencies
FIND_PATH += : $(PRJ_PATH)

vpath %.o $(CONFIG_PATH)
vpath %.c $(FIND_PATH)
vpath %.S $(FIND_PATH)
vpath %.s $(FIND_PATH)
vpath %.cc $(FIND_PATH)
vpath %.C $(FIND_PATH)
vpath %.cpp $(FIND_PATH)
vpath %.cxx $(FIND_PATH)

#
# Common rules
#

%.o:%.s
	$(AS) $(ASFLAGS) $< -o $(CONFIG_PATH)$@

%.o:%.S
	$(CC) $(CFLAGS) $< -o $(CONFIG_PATH)$@

%.o:%.c
	$(CC) $(CFLAGS) $< -o $(CONFIG_PATH)$@

%.o:%.cc
	$(CC) $(CFLAGS) $< -o $(CONFIG_PATH)$@

%.o:%.cpp
	$(CC) $(CFLAGS) $< -o $(CONFIG_PATH)$@

%.o:%.C
	$(CC) $(CFLAGS) $< -o $(CONFIG_PATH)$@

%.o:%.cxx
	$(CC) $(CFLAGS) $< -o $(CONFIG_PATH)$@

# 
# "make rebuild" :rebuild all
# "make build"   :build all
# "make obj.o"   :compile obj.c
# "make lib"     :make user's applications into one library
#

rebuild: clean build

build: $(DEFAULT_RULE)
	
ifeq (depend,$(wildcard depend))
#include depend
endif

ifeq (depend,$(wildcard depend))
#include depend
endif

prj_subdirs: $(patsubst %, _dir_%, $(SUBDIRS))
$(patsubst %, _dir_%, $(SUBDIRS)) : dummy
$(MAKE) CFLAGS="$(CFLAGS)" EXTRA_LDFLAGS="-EL" -C $(patsubst _dir_%, %, $@)

$(PRJ_NAME).elf: $(PRJ_OBJS) prj_subdirs 
	$(LD) $(LDFLAGS) \
    	$(CRT0) \
    	--start-group \
    	$(PRJ_OBJS) $(SUB_OBJS) \
    	$(ALL_LIBS) \
    	--end-group \
			-o $@
	@$(SIZE) -A -x $@ 1>$(SIZE_FILE)
	mipsel-linux-objdump -h $(PRJ_NAME).elf > section-headers
	mipsel-linux-objdump -D $(PRJ_NAME).elf > disassemble-all

clean: 
	find . \( -name '*.[oa]' -o -name core -o -name '.*.flags' -o -name '*~' \
	-o -name 'hello.elf' -o -name  'section-headers' -o -name 'disassemble-all' \
	-o -name 'map' -o -name 'size' \) -type f -print | xargs rm -f     

dummy:
