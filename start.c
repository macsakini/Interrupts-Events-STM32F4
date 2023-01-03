#include "start.h"

//Function is called once
void Init_Start(void){
	NVIC_EnableIRQ(EXTI3_IRQn);
}	

void EXTI3_IRQHandler(void){
//If sensor goes off we should start decelerating
//Since we have only IR sensor we will go to complete halt
//Addition of ditance sensor will make deceleration continous.
	if((GPIOA->IDR & (1<<3)) & (EXTI->PR & (0<<3))){
		//Call the distance function
		Measure_Distance();
		//Reset the pending register.
		EXTI->PR |= (1<<3);
	}	
}

void Measure_Distance(void){
	
}

