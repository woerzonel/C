/*
 * uart_driver.c
 *
 *  Created on: Febuary 9, 2017
 *      Author: Gabe Woerishofer
 */
#include "uart_driver.h"
#include <inttypes.h>
#include <stdio.h>
#include "SYSTCK.h"

char *(rdptr) = 0;
char *(wrptr);
char RD_BUFF[80];
int buffsize = 64;

void SysTick_DelaymilS(){
		*(STK_VAL)	= 0;
		*(STK_LOAD) = 16*800;  
		*(STK_CTRL) = CLKSOURCE|ENABLE;  // System clock is clock source, enable counter, allow interrupt
		while((*(STK_CTRL)&(COUNTFLAG))!=(COUNTFLAG));
		*(STK_VAL)	= 0;
		*(STK_CTRL) = (~ENABLE);  // System clock is clock source, enable counter, allow interrupt
}

// removes a char from the buffer and returns them
char buffer_remove(struct circularbuffer *cirbuff){
	char c;
	//makes sure the buffer isnt empty
	if(cirbuff->empty != 0){
		//removes the the value at the end of the buffer
		c = cirbuff->buff[cirbuff->tail];
		//changes what value the tail is point at
		cirbuff->tail++;
		//decreases the count of stored values
		cirbuff->empty--;
		//when the tail is at the max size of the buffer set it to 0 (to create a loop)
		if(cirbuff->tail == buffsize){
			cirbuff->tail = 0;
		}

	}else{
		//else returns null
		c = '\0';
	}
return c;
}

/**
 * @brief A method to add values to a circular array. (It is missing checks to make sure it doesn't overwrite stored values)
 * 
 * @param cirbuff The circular buffer of characters
 * @param c The current value to be added
 */
void buffer_add(struct circularbuffer *cirbuff,char c){
	//makes sure the  buffer isnt full
	if(cirbuff->empty != buffsize){
		//Increases the front of the buffer
		cirbuff->buff[cirbuff->head] = c;
		//Increases the heads value in the buffer
		cirbuff->head++;
		//Increases the total count of values
		cirbuff->empty++;
		//loops the circular buffer back to the begining
		if(cirbuff->head == buffsize){
			cirbuff->head = 0;
		}

	}
}
/**
 * @brief This method is called by standard I/O whenever it wants to read 
 * 
 * @param uart2 The structure pointing at the usart base address location in memory
 * @param rx_buff Point at the base address of the circular buffer
 * @return char 
 */
char usart2_getch(struct uart *uart2, struct circularbuffer *rx_buff){
	// catchs if buffer is empty
	while(rx_buff->empty == 0);
	//removes a character from the read buffer
	char c = buffer_remove(&rx_buffer);
	
	usart2_putch(USART2,c,&rx_buffer);
	//Handles backspaces
	if(c == '\b' || c == '\177'){
		usart2_putch(USART2,' ',&rx_buffer);
		usart2_putch(USART2,'\b',&rx_buffer);
	}else if(c == '\r'){
		usart2_putch(USART2,'\n',&rx_buffer);
		c = '\n';
	}
	return c;
}
// gets the char from usart _read
void usart2_putch(struct uart *uart2, char c, struct circularbuffer *tx_buff){
	// catches if buffer is full
	while(tx_buff->empty == buffsize);
	//write the current value read in from usart into the buffer
	buffer_add(&tx_buffer,c);
	//Flag the interrupt
	*(USART_CR1) |= (1<<7);
}
// does a puffer remove but uses usart as the char
void usart2_rxirq(struct circularbuffer *cirbuff){

	if(cirbuff->empty != buffsize){
		cirbuff->buff[cirbuff->head] = ((char)*(USART_DR));
		cirbuff->head++;
		cirbuff->empty++;

		if(cirbuff->head == buffsize){
			cirbuff->head = 0;
		}
	}
}

// does a removes but writes to usart
void usart2_txirq(struct circularbuffer *cirbuff){
	if(cirbuff->empty != 0){
		*(USART_DR) = cirbuff->buff[cirbuff->tail];
		cirbuff->tail++;
		cirbuff->empty--;

		if(cirbuff->tail == buffsize){
			cirbuff->tail = 0;
		}
	}

}
// the interrupt handler
void USART2_IRQHandler(){
	if((*(USART_SR)&0x20)==0x20){
		usart2_rxirq(&rx_buffer);
	}else{
		usart2_txirq(&tx_buffer);
		SysTick_DelaymilS();
	}
	*(USART_CR1) &= (~(1<<7));

}


void init_usart2(struct uart *uart2, uint32_t baud, uint32_t sysclk, struct circularbuffer *tx_buffer, struct circularbuffer *rx_buffer){
	// Enable clocks for GPIOA and USART2
	*(RCC_AHB1ENR) |= (1<<GPIOAEN);
	*(RCC_APB1ENR) |= (1<<USART2EN);

	// Function 7 of PORTA pins is USART
	*(GPIOA_AFRL) &= (0xFFFF00FF); // Clear the bits associated with PA3 and PA2
	*(GPIOA_AFRL) |= (0b01110111<<8);  // Choose function 7 for both PA3 and PA2
	*(GPIOA_MODER) &= (0xFFFFFF0F);  // Clear mode bits for PA3 and PA2
	*(GPIOA_MODER) |= (0b1010<<4);  // Both PA3 and PA2 in alt function mode

	// Set up USART2
	//USART2_init();  //8n1 no flow control
	// over8 = 0..oversample by 16
	// M = 0..1 start bit, data size is 8, 1 stop bit
	// PCE= 0..Parity check not enabled
	// no interrupts... using polling
	uart2 -> uart_CR1 = (1<<UE)|(1<<TE)|(1<<RE)|(1<<5); // Enable UART, Tx and Rx
	uart2 -> uart_CR2 = 0;  // This is the default, but do it anyway
	uart2 -> uart_CR3 = 0;  // This is the default, but do it anyway
	uart2 -> uart_BRR = sysclk/baud;

	/* I'm not sure if this is needed for standard IO*/
	 //setvbuf(stderr, NULL, _IONBF, 0);
	 //setvbuf(stdin, NULL, _IONBF, 0);
	 setvbuf(stdout, NULL, _IONBF, 0);
	 int i = 0;
	 while(i<64){
		 tx_buffer->buff[i] = 0;
		 rx_buffer->buff[i] = 0;
		 i++;
	 }
	 tx_buffer->head = 0;
	 tx_buffer->tail = 0;
	 tx_buffer->empty = 0;

	 rx_buffer->head = 0;
	 rx_buffer->tail = 0;
	 rx_buffer->empty = 0;


}

