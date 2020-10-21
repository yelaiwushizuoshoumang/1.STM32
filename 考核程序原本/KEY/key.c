#include "key.h"
#include "stm32f10x.h"                  // Device header
#include "delay.h"
void KEY_Init()
{
	GPIO_InitTypeDef GPIO_InitStructer;
	RCC_APB2PeriphClockCmd(ADVANCE_KEY_APBxPeriph_CLK|ADVANCE_KEY_UP_APBxPeriph_CLK,ENABLE);
	
	GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructer.GPIO_Pin=ADVANCE_GPIOx_KEY1_Pinx|ADVANCE_GPIOx_KEY0_Pinx;
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(ADVANCE_KEY_GPIOx,&GPIO_InitStructer);
	
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructer.GPIO_Pin=ADVANCE_GPIOx_KEY_UP_Pinx;
	GPIO_Init(ADVANCE_KEY_UP_GPIOx,&GPIO_InitStructer);
}

u8 KEY_Scan(GPIO_TypeDef *GPIOx,vu16 GPIO_Pin)
{
		delay_init();
	
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
		{	 
				delay_ms(20);	
				/*等待按键释放 */
				if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
				
					while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
						return KEY_ON;	 	
		}				
		else
			return KEY_UP;
		
}
u8 KEY_UP_Scan(GPIO_TypeDef *GPIOx,u16 GPIO_Pin)
{

		delay_init();
	
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_UP )  
		{	 
				delay_ms(20);	
				/*等待按键释放 */
				if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_UP )  
				
					while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_UP);   
						return KEY_UP;	 	
		}				
		else
			return KEY_ON;

}





	