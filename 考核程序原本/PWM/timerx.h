#ifndef __TIMERX_H
#define __TIMERX_H
#include "sys.h"
//=========GPIOB配置========
#define ADVANCE_TIMx_PWM_GPIOx GPIOB
#define ADVANCE_TIMx_PWM_GPIOx_CLK RCC_APB2Periph_GPIOB
#define ADVANCE_TIMx_PWM_GPIOx_Pin GPIO_Pin_5
//=========================
//=========TIM3初始化======
#define ADVANCE_TIMx_PWM TIM3
#define ADVANCE_TIMx_PWM_CLK RCC_APB1Periph_TIM3
#define ADVANCE_TIMx_Arr   999
#define ADVANCE_TIMx_Psc   71//50Hz,20ms
#define ADVANCE_TIMx_PLus  900
//=========================
//========PWM初始化========
#define ADVANCE_TIMx_Oc_Mode TIM_OCMode_PWM2
//=========================
void GPIOx_Init_Pwm(void);

#endif
