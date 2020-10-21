#include "usart1.h"
#include "dma.h"
#include <stdio.h>
#include "string.h"


u8 receive_data[BufferSize]= {0};

void Usart1_Init()
{

    USART_InitTypeDef UASRT_InitStructer;
    GPIO_InitTypeDef GPIO_InitStructer;
    NVIC_InitTypeDef  NVIC_InitStructer;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

//======配置GPIO=========
    GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;

    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入，usar_tx
    GPIO_InitStructer.GPIO_Pin=ADVANCE_GPIOx_TX;
    GPIO_Init(ADVANCE_GPIOx,&GPIO_InitStructer);

    GPIO_InitStructer.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出，usart_rx
    GPIO_InitStructer.GPIO_Pin=ADVANCE_GPIOx_RX;
    GPIO_Init(ADVANCE_GPIOx,&GPIO_InitStructer);
//========================
//=========配置usart======
    UASRT_InitStructer.USART_BaudRate=ADVANCE_Bound;
    UASRT_InitStructer.USART_WordLength=USART_WordLength_8b;//8位数据
    UASRT_InitStructer.USART_StopBits=USART_StopBits_1;//一个停止位
    UASRT_InitStructer.USART_Parity=USART_Parity_No;//奇偶使能
    UASRT_InitStructer.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流控制失能
    UASRT_InitStructer.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//收发一起
    USART_Init(ADVANCE_USARTx, &UASRT_InitStructer);
    USART_ITConfig(ADVANCE_USARTx,USART_IT_IDLE,ENABLE);//失能接收中断
//    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//接受DMA请求
    USART_DMACmd(ADVANCE_USARTx, USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);// 使能DMA串口发送和接受请求
    USART_Cmd(ADVANCE_USARTx,ENABLE);//使能外设
//========================
//======配置优先级=========
    NVIC_InitStructer.NVIC_IRQChannel=ADVANCE_USARTx_IRQ;
    NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
    NVIC_InitStructer.NVIC_IRQChannelSubPriority = 3;		//子优先级3
    NVIC_InitStructer.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructer);	//根据指定的参数初始化VIC寄存器
//========================
}
void USART_IT_IdleDMA(void)
{
        
    Dma_Init(ADVANCE_DMA_CH,(s32)&USART1->DR,(s32)receive_data,BufferSize);   
    USART_DMACmd(ADVANCE_USARTx,USART_DMAReq_Rx,ENABLE);
}

void USART1_IRQHandler(void)
{

      u8 num=0;
//    static u8 last_num=0;
//    s8 i=0;
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {
        num=USART1->SR;
        num=USART1->DR; //清除USART_IT_IDLE标志位

        DMA_Cmd(ADVANCE_DMA_CH,DISABLE);//关闭DMA

 
        DMA_SetCurrDataCounter(ADVANCE_DMA_CH,32);
        DMA_Cmd(ADVANCE_DMA_CH,ENABLE);  
        
        
    }
//     printf("%s",receive_data);       
}

int fputcc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口 */
    USART_SendData(ADVANCE_USARTx, (uint8_t) ch);

    /* 等待发送完毕 */
    while (USART_GetFlagStatus(ADVANCE_USARTx, USART_FLAG_TXE) == RESET);

    return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
    /* 等待串口输入数据 */
    while (USART_GetFlagStatus(ADVANCE_USARTx, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(ADVANCE_USARTx);
}

