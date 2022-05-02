/*
 *  GPIO.h
 *
 * 	Created on: Dec 7, 2016
 * 		Author: Gabe Woishofer
 *
 */
#ifndef GPIO_H_
#define GPIO_H_

#include <inttypes.h>


// RCC_AHB1ENR bit 0 is GPIOAEN and bit 2 is GPIOCEN
#define GPIOAEN 1<<0
#define GPIOBEN 1<<1
#define GPIOCEN 1<<2

// ***GPIO registers***
//The basic addresses for GPIOA
#define GPIOA_BASE	v0x40020000
#define GPIOA_OTYPER 	(volatile uint32_t*)0x40020004
#define GPIOA_OSPEEDR	(volatile uint32_t*)0x40020008
#define GPIOA_PUPDR	(volatile uint32_t*)0x4002000C
#define GPIOA_ODR	(volatile uint32_t*)0x40020014
//The basic addresses for GPIOB
#define GPIOB_BASE	(volatile uint32_t*)0x40020400
#define GPIOB_MODER 	(volatile uint32_t*)0x40020400
#define GPIOB_OTYPER 	(volatile uint32_t*)0x40020404
#define GPIOB_OSPEEDR	(volatile uint32_t*)0x40020408
#define GPIOB_PUPDR	(volatile uint32_t*)0x4002040C
#define GPIOB_ODR	(volatile uint32_t*)0x40020414
//The basic addresses for GPIOC
#define GPIOC_BASE	(volatile uint32_t*)0x40020800
#define GPIOC_IDR	(volatile uint32_t*)0x40020810
#define GPIOC_MODER 	(volatile uint32_t*)0x40020800
#define GPIOC_OSPEEDR	(volatile uint32_t*)0x40020804
//The speeds of the GPIO's
#define GPIO_Speed_25MHz     	0x00  // Low speed GPIO
#define GPIO_OType_PP 		0x00  // push-pull output
#define GPIO_PuPd_NOPULL  	0x00  // No pull up resister

#define GPIOA7			0x80  // PORTA7 is connected to LED
#define GPIOA8			0x100  // PORTA8 is connected to LED
#define GPIOA9			0x200  // PORTA9 is connected to LED
#define GPIOA10			0x400  // PORTA10 is connected to LED
#define GPIOA11			0x800  // PORTA11 is connected to LED
#define GPIOA_ALL		0xf80  // PORTB8 is connected to LED

#define GPIOA6_MODER_analog	0x3000
//All of the initialization codes for GPIOA
#define GPIOA7_MODER	0x4000
#define GPIOA8_MODER	0x10000
#define GPIOA9_MODER	0x40000
#define GPIOA10_MODER	0x100000
#define GPIOA11_MODER	0x400000
#define GPIOA_All_MODER	0x554000

#define GPIOB8			0x100  // PORTB8 is connected to LED
#define GPIOB9			0x200  // PORTB9 is connected to LED
#define GPIOB10			0x400  // PORTB10 is connected to LED
#define GPIOB12			0x1000  // PORTB12 is connected to LED
#define GPIOB13			0x2000  // PORTB13 is connected to LED
#define GPIOB_ALL		0x3700  // PORTB8 is connected to LED
//All of the initialization codes for GPIOB
#define GPIOB8_MODER	0x10000
#define GPIOB9_MODER	0x40000
#define GPIOB10_MODER	0x100000
#define GPIOB12_MODER	0x1000000
#define GPIOB13_MODER	0x4000000
#define GPIOB_All_MODER	0x5150000

#endif /* GPIO_H_ */
