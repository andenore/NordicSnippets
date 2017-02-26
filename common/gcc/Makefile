DEVICE = NRF52
DEVICE_VARIANT =xxaa

# We have to use SDK, not MDK because core_cm4.h is not provided in MDK
xDK_TOP ?=../../../../nRF5_SDK_12.2.0_f012efa

SOURCES = ../main.c

GNU_PREFIX ?= arm-none-eabi

CC       		:= "$(GNU_PREFIX)-gcc"
OBJDUMP  		:= "$(GNU_PREFIX)-objdump"
OBJCOPY  		:= "$(GNU_PREFIX)-objcopy"


QUIET=@

PROG_NAME ?= example

# CPU related flags
ifeq ($(DEVICE),NRF51)
CFLAGS += -mthumb -mcpu=cortex-m0 -march=armv6-m
LINKER_SCRIPT = $(xDK_TOP)/components/toolchain/gcc/nrf51_$(DEVICE_VARIANT).ld
endif

ifeq ($(DEVICE),NRF52)
CFLAGS +=  -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfpu=fpv4-sp-d16 -mfloat-abi=hard
LINKER_SCRIPT = $(xDK_TOP)/components/toolchain/gcc/nrf52_$(DEVICE_VARIANT).ld
endif

ifeq ($(DEBUG),yes)
CFLAGS += -O -ggdb
else
CFLAGS += -O3
endif

DEVICE_LC = $(shell echo $(DEVICE) | tr A-Z a-z)

# General C compiler flags
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums
CFLAGS += -std=gnu99   -Wall -D$(DEVICE)

# Linker flags (passed to gcc)
CFLAGS += -T $(LINKER_SCRIPT)
CFLAGS += -L $(xDK_TOP)/components/toolchain/gcc

# Include search path
CFLAGS += -I$(xDK_TOP)/components/device
CFLAGS += -I$(xDK_TOP)/components/toolchain
CFLAGS += -I$(xDK_TOP)/components/toolchain/gcc
CFLAGS += -I$(xDK_TOP)/components/toolchain/cmsis/include

SOURCES += $(xDK_TOP)/components/toolchain/system_$(DEVICE_LC).c
SOURCES += $(xDK_TOP)/components/toolchain/gcc/gcc_startup_$(DEVICE_LC).S

all:
	@echo "Program : $(PROG_NAME)"
	@echo "Compiling  $(SOURCES)"
	$(QUIET)$(CC) $(CFLAGS) $(SOURCES) -o $(PROG_NAME).elf
	@echo "Creating  $(PROG_NAME).hex"
	$(QUIET)$(OBJCOPY) -Oihex $(PROG_NAME).elf   $(PROG_NAME).hex
	@echo "Creating  $(PROG_NAME).bin"
	$(QUIET)$(OBJCOPY) -Obinary $(PROG_NAME).elf $(PROG_NAME).bin
	@echo "Done"

flash:
	@echo Flashing: $(PROG_NAME).hex
	nrfjprog -f NRF52 --program $(PROG_NAME).hex --chiperase --verify
	nrfjprog -f NRF52 --reset

debug:
	make -C . DEBUG=yes

clean:
	@rm -f  $(PROG_NAME).elf  $(PROG_NAME).o $(PROG_NAME).hex $(PROG_NAME).bin
	@rm -f system_$(DEVICE_LC).o
	@rm -f gcc_startup_$(DEVICE_LC).o

check_setup:
	@echo "xDK_TOP   = " $(xDK_TOP)
	@echo "SOURCES   = " $(SOURCES)
	@echo "PROG_NAME = " $(PROG_NAME)
