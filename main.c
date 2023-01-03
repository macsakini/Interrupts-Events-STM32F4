#include "stm32f4xx.h"
#include "HAL.h"
#include "start.h"

void Init_GPIO_RCC(void);
void Init_TIM_RCC(void);
void GPIO_Func(void);
void TIM_Func(void);

int main(void){	
	//Initialize clocks for components N/B THIS IS NECESSARY
	Init_GPIO_RCC();
	
	Init_TIM_RCC();
	
	//Initialize clock for the SYSCFG for 14th bit
	RCC->APB2ENR |= (1<<14);
	
	//Configurations using SYSCFG
	SYSCFG->EXTICR[0] |= ( (0<<15) | (0<<14) | (0<<13) |( 0<<12) );
	
	//Initialize IRQs
	Init_Start();
	
	//Interrupt mask
	EXTI->IMR |= (1<<3);
	
	//Rising Trigger
	EXTI->RTSR |= (1<<3);
	
	//Falling Trigger
	EXTI->FTSR |= (1<<3);
	
	//GPIO
	GPIO_Func();
	
	//TIMERS
	TIM_Func();
	
	TIM10->CCR1 |= 0;
	TIM11->CCR1 |= 0;
	
	while(1){
		
	}
}

void Init_GPIO_RCC(void){
	GPIOA_CLOCK_RCC_ENABLE
	GPIOB_CLOCK_RCC_ENABLE
	GPIOC_CLOCK_RCC_ENABLE
}

void Init_TIM_RCC(void){
	TIMER10_CLOCK_RCC_ENABLE
	TIMER11_CLOCK_RCC_ENABLE
}

void GPIO_Func(void){
	//GPIO PINS
	//PA3
	GPIOA->MODER |= ( (0<<7) | (0<<6) ); //Input Function
	GPIOA->OTYPER |= (0<<3); // Output push pull
	GPIOA->OSPEEDR |= ( (0<<7) | (1<<6) ); // Medium Speed
	GPIOA->PUPDR |= ( (0<<7) | (1<<6) ); // Pull up
	
	//PB8
	GPIOB->MODER |= ( (1<<17) | (0<<16)); //Alternate function for timer
	GPIOB->OTYPER |= (0<<8); // Output push pull
	GPIOB->OSPEEDR |= ( (1<<17) | (1<<16)); // Very High Speed
	GPIOB->PUPDR |= ( (0<<17) | (0<<16) ); // Pull up
	GPIOB->AFR[1] |= ( (0<<3) | (0<<2) | (1<<1) | (1<<0) ); // Alternate function to be used Timer 10. Reference datasheet.
	
	//PB9
	GPIOB->MODER |= ( (1<<19) | (0<<18) ); // Alternate function for timer
	GPIOB->OTYPER |= (0<<9); // Output push pull
	GPIOB->OSPEEDR |=( (1<<19) | (1<<18) ); // Very High Speed
	GPIOB->PUPDR |= ( (0<<19) | (0<<18) ); // Pull Up
	GPIOB->AFR[1] |= ( (0<<7) | (0<<6) | (1<<5) | (1<<4) ); // Alternate function to be used Timer 11. Reference datasheet

	//PC13 // Led PIN
	GPIOC->MODER |= ( (0<<27) | (1<<26) ); //Output Function
	GPIOC->OTYPER |= (0<<13); // Output push pull
	GPIOC->OSPEEDR |= ( (0<<27) | (0<<26) ); // Low Speed
	GPIOC->PUPDR |= ( (0<<27) | (1<<26) ); // Pull up
	
}

void TIM_Func(void){
	//Timers and Calculations
	//Sysclock speed is 16MHz or or 16000KHz, 16000000Hz
	//Timer 10 Channel 1
	
	//PWM MODE 
	TIM10->CCMR1 |= ( (1<<6) | (1<<5) | (0<<4) ); //PWM MODE 1
	TIM10->CCMR1 |= (1<<3); //Preload Enable 
	TIM10->CR1 |= (1<<7); // ARPE
	
	TIM10->PSC = 16;
	TIM10->ARR = 1000;
	//TIM10->CCR1 = 300;
	 
	TIM10->EGR |= (1<<0); // Event generation
	TIM10->CCER |= ( (0<<1) | (1<<0) ); //Output polarity | Output enable
	TIM10->CR1 |= (1<<0); // Enable Counter
	
	//Timer 11 Channel 1
	//PWM MODE
	TIM11->CCMR1 |=  ( (1<<6) | (1<<5) | (0<<4) ); //PWM MODE 1
	TIM11->CCMR1 |= (1<<3); //Preload Enable
	TIM11->CCMR1 |= (1<<2);
	TIM11->CR1 |= (1<<7); //ARPE
	
	TIM11->PSC = 16;
	TIM11->ARR = 1000;
	//TIM11->CCR1 = 700;
	
	TIM11->EGR |= (1<<0); //Event generation
	TIM11->CCER |= ( (0<<1) | (1<<0) );//Output polarity | Output enable
	TIM11->CR1 |= (1<<0); // Enable Counter	
}