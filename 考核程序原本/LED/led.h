#ifndef __LED_H
#define __LED_H
#include "sys.h"
#define LED1 PBout(5)
#define LED0 PEout(5)

//=========LED-GPIO的配置==========

#define ADVANCE_LED1_GPIOB GPIOB
#define ADVANCE_LED1_GPIOB_Pinx GPIO_Pin_5
#define ADVANCE_LED1_RCC_APBxPeriph_CLK RCC_APB2Periph_GPIOB
#define ADVANCE_LED0_GPIOE GPIOE
#define ADVANCE_LED0_GPIOE_Pinx GPIO_Pin_5
#define ADVANCE_LED0_RCC_APBxPeriph_CLK RCC_APB2Periph_GPIOE
//#define ADVAMCE_LED1_GPIOE GPIOE

void LED_Init(void);

//================================
#endif

