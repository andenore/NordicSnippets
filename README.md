# NordicSnippets
[![Build Status](https://travis-ci.org/andenore/NordicSnippets.svg)](https://travis-ci.org/andenore/NordicSnippets)

NordicSnippets is a collection of bare-metal example code that runs on the nRF51 or nRF52 series of Nordic Semiconductor SoCs.

The idea is that the examples are as simple as possible to showcase how easy it is to use the various peripherals. Therefore all examples are limited to one main.c file, and typically use a minimum set of the features of a given peripheral.

A developer can then use the examples as a basis to create an abstraction layer that fits to his or hers use-case.

Note that some peripherals and features of peripherals may not exist for your device.

## Tools
The header files and tools that are needed can be downloaded from the Nordic web-pages listed below.

Header files are located in the MDK downloads, available for GCC, IAR and Keil.

nRF52: http://www.nordicsemi.com/eng/Products/Bluetooth-Smart-Bluetooth-low-energy/nRF52832

nRF51: http://www.nordicsemi.com/eng/Products/Bluetooth-Smart-Bluetooth-low-energy/nRF51822

## Using nrfjprog
The nrfjprog utility can be used for programming target devices and reading/writing device memory among other things. It is available in the nRF5x-Tools-* download.

Windows:
	Download nRF5x-Tools_Win32 and add the full path of nrfjprog.exe to your system PATH.

Linux:
	Download nRF5x-Tools_Linux and run 'sudo ln -s <path to nrfjprog.exe> /usr/local/bin/nrfjprog' from your command line.

Run 'nrfjprog' from your command line. The help menu should print and this indicates its path has been properly set.

Now you can use nrfjprog! After building any of the examples just run 'make flash' from your command line to completly erase the chip, program & verify the hex file, and reset and run the application!
