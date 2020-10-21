#include "dma.h"
void Dma_Init(DMA_Channel_TypeDef*DMA_CHx,u32 peripheral_addr,u32 memory_addr,u16 size)//定义DMA通道，外设地址，内存地址
{
    DMA_InitTypeDef DMA_InitStructer;

    RCC_AHBPeriphClockCmd(ADVANCE_DMA_CLK,ENABLE);//打开外设时钟

    DMA_DeInit(ADVANCE_DMA_CH);//设置缺省值
    DMA_InitStructer.DMA_PeripheralBaseAddr =  peripheral_addr;//定义外设基地址
    DMA_InitStructer.DMA_MemoryBaseAddr = memory_addr;//定义DMA内存基础地址
    DMA_InitStructer.DMA_DIR=DMA_DIR_PeripheralSRC ;//外设做为数据来源
    DMA_InitStructer.DMA_BufferSize=size;//缓存大小，通道数据量
    DMA_InitStructer.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//外设寄存器不变
//    DMA_InitStructer.DMA_MemoryInc=DMA_PeripheralInc_Enable;//内存地址寄存器递增
    DMA_InitStructer.DMA_MemoryInc=DMA_MemoryInc_Enable;
    DMA_InitStructer.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//外设数据宽度，8位

    //    DMA_InitStructer.DMA_MemoryDataSize=DMA_PeripheralDataSize_Byte;//内存数据宽度
	DMA_InitStructer.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;

    DMA_InitStructer.DMA_Mode=DMA_Mode_Normal;//工作正常缓存
    DMA_InitStructer.DMA_Priority=DMA_Priority_High;//通道最高优先级
    DMA_InitStructer.DMA_M2M=DMA_M2M_Disable;//不是内存到内存
    DMA_Init(ADVANCE_DMA_CH,&DMA_InitStructer);
    DMA_Cmd(ADVANCE_DMA_CH,ENABLE);


    USART_DMACmd(ADVANCE_DMA_USARTx,USART_DMAReq_Rx,ENABLE);//接受DMA请求
}

