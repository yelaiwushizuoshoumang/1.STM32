#include "dma.h"
#include "delay.h"
#include <stdio.h>
#include "timerx.h"
#include "key.h"
#include "led.h"
#include "tim_ic.h"
#include "usart1.h"
#include "can.h"
u8 flag_pwm=1;//工作一标志
u32 tim_ic_value;
u32 a=0;
u8 can_buf[4]={201,202,203};
u8 res;
u8 cant;
int main(void)
{

    Usart1_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    USART_IT_IdleDMA();
    delay_init();
// GPIOx_Init_Pwm();  
	KEY_Init();
     LED_Init();
//  TIM_CapInit(); 
	Can_Init();
	
	while(1)
	{

	if(receive_data[0]==0x11)
		{
			if(KEY_Scan(ADVANCE_KEY_GPIOx,ADVANCE_GPIOx_KEY0_Pinx)==KEY_ON)
			{
			if(flag_pwm==1)
				{
				printf("收到\r\n");
				GPIOx_Init_Pwm(); 
				TIM_SetCompare2(TIM3,25);
				flag_pwm=2;
				}	
			else if(flag_pwm==2)	
			{
			     GPIOx_Init_Pwm(); 
				TIM_SetCompare2(TIM3,150);
				flag_pwm=3;
			}
			else if(flag_pwm==3)	
			{
			     GPIOx_Init_Pwm(); 
				TIM_SetCompare2(ADVANCE_TIMx_PWM,600);
				flag_pwm=1;
			}
			}
		}
//	if(USART_ReceiveData(ADVANCE_USARTx)==0x22)
//	     {
//		
//		}
//	if(receive_data[0]==0x33)
//	{
//	    if ((TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  )
//		{
//		tim_ic_value=GetAValue();
//		printf("%d us\r\n", tim_ic_value);
//		LED0=~LED0;
//		delay_us(tim_ic_value);
//		LED0=~LED0;
//		}
//	}
		if(receive_data[0]==0x22)
		{
		if(KEY_Scan(ADVANCE_KEY_GPIOx,ADVANCE_GPIOx_KEY0_Pinx)==KEY_ON)
		{
		cant=CAN_TX_Msg(can_buf,4);
		if(cant==201)//判断是否接受到数据
		{
		LED0=0;
		}
		else if(cant==202)//判断是否接受到数据
		{
		TIM_SetCompare2(TIM3,900);
		}
		}
		if(receive_data[0]==0x33)
		{
		    TIM_CapInit();

		}
}
}
}
