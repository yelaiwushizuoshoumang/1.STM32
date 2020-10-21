#ifndef __USART1_H
#define __USART1_H
#include "sys.h"
void Usart1_Init(void);
void USART_IT_IdleDMA(void);
//============串口GPIO的设置===============
#define ADVANCE_GPIOx GPIOA
#define ADVANCE_APBxPeriph_GPIOx_CLK  RCC_APB2Periph_GPIOA
#define ADVANCE_GPIOx_RX  GPIO_Pin_9
#define ADVANCE_GPIOx_TX  GPIO_Pin_10
//========================================
//============串口初始化的设置=============
#define ADVANCE_USARTx USART1
#define ADVANCE_APBxPeriph_USARTx_CLK RCC_APB2Periph_USART1
#define ADVANCE_Bound 115200
#define ADVANCE_USARTx_IRQ USART1_IRQn
#define ADVANCE_USARTx_IRQHandel USART1_IRQHandler
//========================================
#endif

