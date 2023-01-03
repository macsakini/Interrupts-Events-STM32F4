#pragma once

#include "stm32f4xx.h"

void Init_Start(void);

//interrupt for PA3 EXTI3
void EXTI3_IRQHandler(void);

//Use ultrasonic sensor to measure distance
void Measure_Distance(void);
