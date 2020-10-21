#include "can.h"
#include "stdio.h"
void GPIOx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructer;
	RCC_APB2PeriphClockCmd(ADVANCE_GPIOx_CLK,ENABLE);
	
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IPU;	
	GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructer.GPIO_Pin=ADVANCE_CAN_RX;//上拉输入
	
	GPIO_Init(ADVANCE_GPIOx,&GPIO_InitStructer);
	
	GPIO_InitStructer.GPIO_Pin=ADVANCE_CAN_TX;
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(ADVANCE_GPIOx,&GPIO_InitStructer);
	
}
void Can_Init_Mode(void)
{
	CAN_InitTypeDef CAN_InitStructer;
	RCC_APB1PeriphClockCmd(ADVANCE_CAN_CLK,ENABLE);
	
	CAN_InitStructer.CAN_ABOM=DISABLE;//自动离线管理
	CAN_InitStructer.CAN_AWUM=DISABLE;//自动唤醒模式
	CAN_InitStructer.CAN_NART=ENABLE;//禁止非自动重传输模式
	CAN_InitStructer.CAN_RFLM=DISABLE;//报文不锁定，新的覆盖
	CAN_InitStructer.CAN_TTCM=DISABLE;//非时间触发通讯模式
	CAN_InitStructer.CAN_TXFP=DISABLE;//FIFO发送优先级
	CAN_InitStructer.CAN_Mode=ADVANCE_CAN_Mode;
	CAN_InitStructer.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructer.CAN_BS1=ADVANCE_CAN_BS1;
	CAN_InitStructer.CAN_BS2=ADVANCE_CAN_BS2;
	CAN_InitStructer.CAN_Prescaler=ADVANCE_CAN_Fdiv;//分频
	
	CAN_Init(CAN1,&CAN_InitStructer);
}
void Can_FilterInit(void)
{
	CAN_FilterInitTypeDef CAN_FilterStructer;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	CAN_FilterStructer.CAN_FilterNumber=0;//指定待初始化的过滤器
	CAN_FilterStructer.CAN_FilterMode=CAN_FilterMode_IdMask;//屏蔽位模式
	CAN_FilterStructer.CAN_FilterScale=CAN_FilterScale_32bit;//一个32位过滤器
	CAN_FilterStructer.CAN_FilterIdHigh=0X0000;//设定标识符，32位高段位、
	CAN_FilterStructer.CAN_FilterIdLow=0X0000;//32位低段位
	
	CAN_FilterStructer.CAN_FilterMaskIdHigh=0X0000;//屏蔽器设置，掩码
	CAN_FilterStructer.CAN_FilterMaskIdLow=0X0000;
	CAN_FilterStructer.CAN_FilterFIFOAssignment=CAN_FilterFIFO0;//过滤器0
	CAN_FilterStructer.CAN_FilterActivation=ENABLE;
	
	CAN_FilterInit(&CAN_FilterStructer);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}
void Can_Init()
{
	GPIOx_Init();
	Can_Init_Mode();
	Can_FilterInit();
}
u8 CAN_TX_Msg(u8* Tx_BuFF,u8 len)
{
	u16 i=0;
	u8  Mbox;
	CanTxMsg CanTxMsgStructer;
	
	CanTxMsgStructer.StdId=0xff;//设定标准标识符
	CanTxMsgStructer.ExtId=0xff;//设定扩展标识符
	CanTxMsgStructer.IDE=CAN_ID_STD;//设定消息标识符类型，标准帧
	CanTxMsgStructer.RTR=CAN_RTR_DATA;//数据帧
	CanTxMsgStructer.DLC=len;
//	CAN_Transmit(CAN1,&CanTxMsgStructer);
	for(i=0;i<len;i++)
	{
	CanTxMsgStructer.Data[i]=Tx_BuFF[i];//待传输的数据
	}i=0;
	Mbox=CAN_Transmit(CAN1,&CanTxMsgStructer);
	while((CAN_TransmitStatus(CAN1, Mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;//等待发送结束
	if(i>=0XFFF)
	return 1;
	else
	return 0;	//发送成功
	//CAN_TransmitStatus是检查消息传输的状态函数
}
u8 CAN_RX_Msg(u8* Rx_BuFF)
{
	u32 i;
	CanRxMsg CanRxMsgStructer;
//	if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//没有接收到数据,直接退出 
    CAN_Receive(CAN1, CAN_FIFO0, &CanRxMsgStructer);//读取数据	
    for(i=0;i<8;i++)
    Rx_BuFF[i]=CanRxMsgStructer.Data[i];  
	return CanRxMsgStructer.DLC;	
}
CanRxMsg CanRxMessage;
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	ITStatus Status;
//	(改)1.0 Status= CAN_GetFlagStatus(CAN1,CAN_IT_FMP0);//被设置与否
	Status=CAN_GetITStatus(CAN1,CAN_IT_FMP0);//指定中断发生与否
		if(SET == !RESET)
	{
		CAN_Receive(CAN1,CAN_FIFO0,&CanRxMessage);
		CAN_ClearFlag(CAN1,CAN_IT_FMP0);
	}
}

