#pragma once 

#include "stm32f4xx.h"

//CLOCK INIT
#define GPIOA_CLOCK_RCC_ENABLE			(RCC->AHB1ENR |= (1<<0));
#define GPIOB_CLOCK_RCC_ENABLE			(RCC->AHB1ENR |= (1<<1));
#define GPIOC_CLOCK_RCC_ENABLE			(RCC->AHB1ENR |= (1<<2));
#define GPIOD_CLOCK_RCC_ENABLE			(RCC->AHB1ENR |= (1<<3));

#define TIMER10_CLOCK_RCC_ENABLE				(RCC->APB2ENR |= (1<<17));
#define TIMER11_CLOCK_RCC_ENABLE				(RCC->APB2ENR |= (1<<18));
#define TIMER4_CLOCK_RCC_ENABLE					(RCC->APB1ENR |= (1<<2));
