Lab 9: Memory Maniputalation Using UART

Part of the first class ever taken in C. This project involved using a program on our laptops that would send UART messages over a usb cable to a micro-controller. The professor supplied 1 file that replaced the standard I/O with UART communication. We used this with IR (itterupts) in this program. 

The program takes in a message with the format of RD ##### #####, WR ##### ####, or RD ##### this tell the program to read at a location, a range of locations or to write a value at a location. Interrupts are triggered by the program (this was just an introduction to interrupts) that read values into a created circular buffer or writes values out from the buffer. The standard I/O calls methods in this program that take the micro-controllers read and write buffers and stores the values in a circular buffer. This was done because it would be bad practice to edit a read or write buffer the micro-controller use. If the value is written to the circular buffer it is then passed to the the write buffer. Other wise the read buffer will be passed the circular buffer that will then write it to uart.

Files
Header:
*GPIO.h: Holds the address locations of the base GPIOs and the offsets for control of them. This is also where info for LEDs (attached to gpios) are stored. This was used in other programs primarly, not this one.
*SYSTICK.h: The header file for the syscalls.c file. Stored address locations of system information.
*uart_driver.h: For the uart_driver.c file it stored uart base address information and circular buffer structure information.

Files:
*main.c: The main program handled the logic for splitting up the read in messages and out going messages.
*syscalls.c: The program that replaces standard i/o with uart created by the professor of my class.
*uart_driver.c: The driver that preforms the reading and writing of the values to and from the read, write, and circular buffer. 
