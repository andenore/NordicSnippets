DEVICE ?= NRF52
MDK_TOP=../..

CC ?= arm-none-eabi-gcc

# CPU related flags
ifeq ($(DEVICE),NRF51)
CFLAGS += -mthumb -mcpu=cortex-m0 -march=armv6-m
endif

ifeq ($(DEVICE),NRF52)
CFLAGS +=  -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfpu=fpv4-sp-d16 -mfloat-abi=hard
endif

ifeq ($(DEBUG),yes)
CFLAGS += -O -ggdb
else
CFLAGS += -O3
endif

# General C compiler flags


CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums
CFLAGS += -std=gnu99 -c $(CPUFLAGS) -Wall -D$(DEVICE)

all:


debug:
	make -C . DEBUG=yes
