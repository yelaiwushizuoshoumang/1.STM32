/*
TIM3_CH2,输出pwm控制PB,5
*/
#include "timerx.h" 

void GPIOx_Init_Pwm()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructer;
	TIM_OCInitTypeDef TIM_OCStructer;
	GPIO_InitTypeDef GPIO_InitStructer;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//部分重映射
		
	//==============GPIO的初始化========================
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructer.GPIO_Pin=GPIO_Pin_5;	
	GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructer);
	//==================================================	
	//==============TIM的初始化==========================
	TIM_TimeBaseStructer.TIM_Period=ADVANCE_TIMx_Arr;
	TIM_TimeBaseStructer.TIM_Prescaler=ADVANCE_TIMx_Psc;	
	TIM_TimeBaseStructer.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructer.TIM_CounterMode=TIM_CounterMode_Up;//向上计数	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructer);
	//==================================================	
	//=============TIM的外设============================
	TIM_OCStructer.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCStructer.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCStructer.TIM_Pulse=100;
	TIM_OCStructer.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC2Init(TIM3,&TIM_OCStructer);
	TIM_OC2PreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);//使能外设
}
