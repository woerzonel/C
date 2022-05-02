/*
 * main.c
 *
 *  Created on: DEC 12, 2016
 *      Author: Woerishofer
 *
 *      Reads and wrotes memory from uart
 *
 */
#include <stdio.h>
#include <stdlib.h>

//#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_gpio.h"
//#include "stm32f4xx.h"
#include <inttypes.h>

#include "uart_driver.h"
#include <SYSTCK.h>

// ***System config registers*** (sections 8.2.3 thru 8.2.6 of the STM32F466 reference manual)
#define SYSCFG_BASE 	(volatile uint32_t *)0x40013800
#define SYSCFG_EXTICR4 	(volatile uint32_t *)0x40013814
#define SYSCFGEN 1<<14  // 14th bit in RCC_APB2ENR

// ***EXTI registers*** (section 10.3 of the STM32F466 reference manual)
#define EXTI_BASE 	(volatile uint32_t *)0x40013c00
#define EXTI_IMR   	(volatile uint32_t *)0x40013c00  // Interrupt mask register
#define EXTI_RTSR 	(volatile uint32_t *)0x40013c08  // Rising trigger select register
#define EXTI_FTSR   	(volatile uint32_t *)0x40013c0c	 // Falling trigger select register
#define EXTI_PR     	(volatile uint32_t *)0x40013c14	 // Interrupt pending register

// ***NVIC registers***
#define NVIC_BASE 	(volatile uint32_t*)0xE000E000
#define NVIC_ISER1 	(volatile uint32_t*)0xE000E104


#define F_CPU 16000000UL



uint32_t test;


//The main loop that moves the curos writes and clears
int main(void){
	//inialization
	uint32_t *addr1, *addr2;

	init_usart2(USART2,9600,F_CPU,&tx_buffer,&rx_buffer);

	char op[3];

	*(NVIC_ISER1) |= 1<<(38-32);

	asm ( "CPSIE i\n\t" );  // Global interrupt enable


while(1){
	// ***Enable EXTI15_10 interrupt***

	char command[80];
	// prints enter a command
		printf("\nEnter a command \n");

		//gets a string from the standard IO then removes the new line character
		  if (fgets(command, sizeof command, stdin) != NULL)
		  {
			  char * newline = strchr(command, '\n');
			  if(newline != NULL)
			  {
				  *newline = '\0';
			  }
		  }

		  // a list of loops to replace broken values
		  //Finds evert accurance of a character and replaces it. When all accurances are found it breaks from the loop
		  char  test = "a";
		  while(test != NULL){
			  char* zero = strchr(command, 0xb0);
				if(zero != NULL)
			  {
			    *zero = 0x30;
			  }
			    test = *zero;
		  }

		// a list of loops to replace broken values
		//Finds evert accurance of a character and replaces it. When all accurances are found it breaks from the loop
		  test = "a";
		  while(test != NULL){
		     char * three = strchr(command, 0xb3);
			     if(three != NULL)
	 		  {
			    *three = 0x33;
		      }
			     test = *three;
		  }
		// a list of loops to replace broken values
		//Finds evert accurance of a character and replaces it. When all accurances are found it breaks from the loop
		  test = "a";
		  while(test != NULL){
			 char *five = strchr(command, 0xb5);
			     if(five != NULL)
			  {
			     *five = 0x35;
			  }
			     test = *five;
		  }
		// a list of loops to replace broken values
		//Finds evert accurance of a character and replaces it. When all accurances are found it breaks from the loop
		   test = "a";
		  while(test != NULL){
			char * six = strchr(command, 0xb6);
			     if(six != NULL)
			  {
			      *six = 0x36;
			  }
			     test = *six;
		  }
		// a list of loops to replace broken values
		//Finds evert accurance of a character and replaces it. When all accurances are found it breaks from the loop
		  test = "a";
		  while(test != NULL){
		  char * dee = strchr(command, 0xc4);
		        if(dee != NULL)
		      {
		  	      *dee = 0x44;
		      }
		  	     test = *dee;
		  }
			// sets addr2 to 0
		  addr2 = 0;
			// breaks apart the string int a string and 2 numeric values
		  sscanf(command, "%s%x%x",op, &addr1,&addr2);
			// checks to see if it is a write
		  if(strcmp(op,"WR") == 0){
				//writes the second values at the location of first value
			  *(addr1) = (uint32_t)addr2;
				//prints what it wrote so the user can confirm
			  printf("%08x: %08x",addr1,*(addr1));

			//checkts to see if it is a read
		  }else if(strcmp(op,"RD")==0){
				//checks to see if single read
			  if(addr2 == 0){
					// does a single read from the first value entered
				  printf("%08x: %08x",addr1,*(addr1));
				// checks to see if it a a multple read
			  }else if(addr2 != 0){

					//Loops through tell addr1 is greater then or requal addr2
				  while(addr1 <= addr2){

						// when it is equal does 1 more write
					  if(addr1 == addr2){
							//the last write then a addr1 increment
						  printf("%08x: %08x",addr1,*(addr1));
						  addr1++;
					  }else{
							// Prints the address it is currently reading from
						  printf("%08x: ",addr1);
						  //A loop that prints 4 chunks of8 bits data at the location that address 1 is currently at
						  for(int i = 0; i < 4; i++){
							  printf("%08x ",*(addr1));
						  addr1++;
						  }
						  //Ends with a new line character
						  printf("\n");
					  }

				  }

			  }
		  }else{
				// error catch to handle not proper formatting
			  printf("\nError Try again\n");

		  }
	}

}
