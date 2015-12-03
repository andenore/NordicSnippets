https://travis-ci.org/rbarzic/NordicSnippets.svg?branch=master
# NordicSnippets

NordicSnippets is a collection of bare-metal example code that runs on the nRF51 and nRF52 series of Nordic Semiconductor SoCs.

The idea is that the examples are as simple as possible to showcase how easy it is to use the various peripherals. Therefore all examples are limited to one main.c file, and typically use a minimum set of the features of a given peripheral.

A developer can then use the examples as a basis to create an abstraction layer that fits to his or hers use-case.

Note that some peripherals and features of peripherals may not exist for your device.

## Tools
The header files and tools that are needed can be downloaded from the Nordic web-pages listed below.

Header files are located in the MDK downloads, available for GCC, IAR and Keil.
The nrfjprog utility can be used for programming and is available in the nRF5x-Tools-* download.

nRF52: http://www.nordicsemi.com/eng/Products/Bluetooth-Smart-Bluetooth-low-energy/nRF52832

nRF51: http://www.nordicsemi.com/eng/Products/Bluetooth-Smart-Bluetooth-low-energy/nRF51822
