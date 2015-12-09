# NordicSnippets
[![Build Status](https://travis-ci.org/andenore/NordicSnippets.svg)](https://travis-ci.org/andenore/NordicSnippets)

NordicSnippets is a collection of bare-metal example code that runs on the nRF51 or nRF52 series of Nordic Semiconductor SoCs.

The idea is that the examples are as simple as possible to showcase how easy it is to use the various peripherals. Therefore all examples are limited to one main.c file, and typically use a minimum set of the features of a given peripheral.

A developer can then use the examples as a basis to create an abstraction layer that fits to his or hers use-case.

Some examples also contain a 'test.py' file. 'test.py' tests that the example program behaves as expected.

NordicSnippets is a great way to get started with nRF5x series devices. With such simple examples it is very easy to confidently get your toolchain setup and see how much more effecient the free tools Nordic provides can make you as a developer!

Note that some peripherals and features of peripherals may not exist for your device.

## Tools
The header files and tools that are needed can be downloaded from the Nordic web-pages listed below. The tools Nordic provides include nrfjprog, pynrfjprog and mergehex. Installing and using these tools with NordicSnippets is described in below sections.

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

## Using pynrfjprog
pynrfjprog is a python tool Nordic provides that makes setting up an automatic test suite for Nordic series devices very easy! It can be used with Python 2.7 and above and Python 3. To install pynrfjprog make sure you have 'pip' installed on your computer and run 'pip install pynrfjprog' from your command line.

Now you can automatically test all examples that contain the file 'test.py' in the same director as the example's 'main.c' file. After compiling the example, open a command line in the same directory as the example's 'test.py' and run 'python test.py' from your command line.

Note: The framework of 'test.py' can be easily used as a template to test other examples and custom applications.

## How to contribute
If you are missing some examples you think would be nice, or think something could be improved, feel free to send a pull request.
There are some rules that should be followed:
* All examples should consist of only one file (main.c)
* There should be a minimal amount of dependencies 
* The code needs to be compilable with ARM GCC (needed by integration server)

Examples should be placed under the examples directory, and include the main.c file and a armgcc directory with the Makefile for the project. A readme should be added to explain what peripherals are used and the intention of the code.
 

