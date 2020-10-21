#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
//=====GPIOE的配置========
#define ADVANCE_KEY_GPIOx GPIOE
#define ADVANCE_GPIOx_KEY0_Pinx GPIO_Pin_4
#define ADVANCE_GPIOx_KEY1_Pinx GPIO_Pin_3
#define ADVANCE_KEY_APBxPeriph_CLK RCC_APB2Periph_GPIOE
//========================
//=====GPIOA的配置========
#define ADVANCE_KEY_UP_GPIOx GPIOA
#define ADVANCE_GPIOx_KEY_UP_Pinx GPIO_Pin_0
#define ADVANCE_KEY_UP_APBxPeriph_CLK RCC_APB2Periph_GPIOA
//========================
#define KEY_ON 1
#define KEY_UP 0

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 

void KEY_Init(void);
u8 KEY_Scan(GPIO_TypeDef *GPIOx,u16 GPIO_Pin);
u8 KEY_UP_Scan(GPIO_TypeDef *GPIOx,u16 GPIO_Pin);
#endif
