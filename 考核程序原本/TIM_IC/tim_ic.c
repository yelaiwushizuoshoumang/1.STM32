#include "tim_ic.h"
#include "led.h"
#include "stdio.h"
#include "delay.h"
u8 overload=0;
u8 capture_val = 0;
u8 capture_status=0;
u32 high_time;
u8 i;
//u32 A;
//int GetAValue(void) { return A; }
void TIM_CapInit()
{

GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_ICInitTypeDef TIM5_ICInitStructure;
NVIC_InitTypeDef NVIC_InitStructure;


RCC_APB1PeriphClockCmd(ADVANCE_TIM_CLK, ENABLE); 
RCC_APB2PeriphClockCmd(ADVANCE_TIM_IC_GPIOx_CLK, ENABLE); 

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
GPIO_InitStructure.GPIO_Pin = ADVANCE_TIM_IC_Pin;
GPIO_Init(ADVANCE_TIM_IC_GPIOx, &GPIO_InitStructure); 
GPIO_ResetBits(ADVANCE_TIM_IC_GPIOx, GPIO_Pin_0); 

//初始化定时器5 TIM5
TIM_TimeBaseStructure.TIM_Period = ADVANCE_TIM_ARR;                 
TIM_TimeBaseStructure.TIM_Prescaler = ADVANCE_TIM_PSC;                 
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure);         

//初始化TIM5输入捕获参数
TIM5_ICInitStructure.TIM_Channel = ADVANCE_TIM_Channelx;               
TIM5_ICInitStructure.TIM_ICPolarity = ADVANCE_TIM_IC_Star;   
TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;           
TIM5_ICInitStructure.TIM_ICFilter = 0x00;                      
TIM_ICInit(TIM5, &TIM5_ICInitStructure);

//中断分组初始化
NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQ;           
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           
NVIC_Init(&NVIC_InitStructure);                          

TIM_ITConfig(ADVANCE_TIM, TIM_IT_Update | ADVANCE_TIM_IT_CCx, ENABLE);

TIM_Cmd(ADVANCE_TIM, ENABLE); 
}

void TIM5_IRQHandler(void)
{
if ((TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) & capture_status)//测量高电平期间产生的中断
{
   overload++;
}
if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) //触发捕获
{

   switch (capture_status)
   {
   case 0://捕获到高电平
	  TIM_SetCounter(TIM5, 0);//将当前计数器CNT的值清0 
	  TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);//设置成下降沿捕获
	  capture_status = 1;
	  break;
   case 1:
	  capture_val = TIM_GetCapture1(TIM5); //获取高电平的时间

	  high_time = capture_val + 65536 * overload;
       printf("%d us", high_time);
	  printf("\r\n");
	  LED0=0;
	  delay_us(high_time);
	  LED0=0XFF;
	  overload = 0;  
	  capture_val = 0;
	  high_time = 0;
	  capture_status = 0;

	  TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);
	  break;
   }
}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update); //清除中断
}
