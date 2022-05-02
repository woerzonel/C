/*
 *  SYSTCK.h
 *
 * 	Created on: Dec 7, 2016
 * 		Author: Gabe Woishofer
 *
 *
 */
#ifndef SYSTCK_H_
#define SYSTCK_H_

#include <inttypes.h>
//The basic addresses  for System Tick
#define	SYSTICK_BASE 	(volatile uint32_t *)0xE000E010
#define	STK_CTRL 	(volatile uint32_t *)0xE000E010
#define	STK_LOAD 	(volatile uint32_t *)0xE000E014
#define	STK_VAL 	(volatile uint32_t *)0xE000E018
#define	STK_CALIB 	(volatile uint32_t *)0xE000E01C
// STK_CTRL control bits
#define	COUNTFLAG 1<<16
#define	CLKSOURCE 1<<2	// Use processor clock (16 Mhz)
#define	TICKINT 1<<1
#define	ENABLE 1<<0

// ***RCC registers*** (section 6.3 page 124 of the STM32F466 reference manual)
#define RCC_BASE 	(volatile uint32_t *)0x40023800
#define RCC_APB2ENR 	(volatile uint32_t *)0x40023844

#endif /* SYSTCK_H_ */
