#ifndef __DMA_H
#define __DMA_H
#include "sys.h"
#define BufferSize 32

void Dma_Init(DMA_Channel_TypeDef*DMA_CHx,u32 peripheral_addr,u32 memory_addr,u16 size);//定义DMA通道，外设地址，内存地址
void USART_IT_IdleDMA(void);

#define ADVANCE_DMA_CH DMA1_Channel5
#define ADVANCE_DMA_CLK  RCC_AHBPeriph_DMA1
#define ADVANCE_DMA_USARTx USART1

extern u8 receive_data[BufferSize];


#endif
