DEVICE = NRF52
DEVICE_VARIANT = xxaa

CMSIS ?= ../../../common/arm
MDK   ?= ../../../common/nRF5x_MDK_8_1_0_GCC

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
LINKER_SCRIPT = $(MDK)/nrf51_$(DEVICE_VARIANT).ld
endif

ifeq ($(DEVICE),NRF52)
CFLAGS +=  -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfpu=fpv4-sp-d16 -mfloat-abi=hard
LINKER_SCRIPT = $(MDK)/nrf52_$(DEVICE_VARIANT).ld
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
CFLAGS += -L $(MDK)

# Include search path
CFLAGS += -I$(CMSIS)
CFLAGS += -I$(MDK)

SOURCES += $(MDK)/system_$(DEVICE_LC).c
SOURCES += $(MDK)/gcc_startup_$(DEVICE_LC).S

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
	@echo "MDK       = " $(MDK)
	@echo "CMSIS     = " $(CMSIS)
	@echo "SOURCES   = " $(SOURCES)
	@echo "PROG_NAME = " $(PROG_NAME)
