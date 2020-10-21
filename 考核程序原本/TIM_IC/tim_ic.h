#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define ADVANCE_TIM  TIM5
#define ADVANCE_TIM_CLK RCC_APB1Periph_TIM5
#define ADVANCE_TIM_ARR 0XFFFF
#define ADVANCE_TIM_PSC (72-1)

#define ADVANCE_TIM_IC_GPIOx GPIOA
#define ADVANCE_TIM_IC_GPIOx_CLK RCC_APB2Periph_GPIOA
#define ADVANCE_TIM_IC_Pin GPIO_Pin_0
#define ADVANCE_TIM_Channelx TIM_Channel_1

#define ADVANCE_TIM_IT_CCx TIM_IT_CC1
#define ADVANCE_TIM_IRQ TIM5_IRQn
#define ADVANCE_TIM_IRQHand TIM5_IRQHandler

#define ADVANCE_TIM_GetCapturex TIM_GetCapture1
#define ADVANCE_TIM_OCxPolarity TIM_OC1PolarityConfig
#define ADVANCE_TIM_IC_Star  TIM_ICPolarity_Rising
#define ADVANCE_TIM_IC_End   TIM_ICPolarity_Falling

int GetAValue(void);
void TIM_CapInit(void);

#endif
