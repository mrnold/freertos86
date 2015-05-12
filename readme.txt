FreeRTOS TI-86

This is a port of FreeRTOS to a TI-86 graphing calculator. This is not especially useful, but it is a fun exercise.

Currently, this repository builds the FreeRTOS kernel, a demo program, and a launcher program. The launcher copies the kernel to 0x8100, the application to 0xA000, and uses the TIOS-allocated space for the heap and interrupt table. A small syscall interface prevents the need to compile and transfer everything at once.

Building this project requires SDCC 3.4.0 and Python 2.7. So far it has only been built on Windows using a port of GNU Make, but it should build on other platforms without trouble.

The license for FreeRTOS and port code is GPL2.
