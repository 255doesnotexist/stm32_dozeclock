/*
************************************************
* 文件: uart.c
* 功能: 串口操作函数
* 作者：Lijh
************************************************
*/
//头文件引用
#include "uart.h"

/*串口初始化 */
void UartInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/****************************USART1: TX = PA9, RX = PA10 *****************************/
	/* 打开设备时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,  ENABLE);  //GPIOA 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  //USART1 时钟

	/* 开启GPIO复用USART功能 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  // PA9复用
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //PA10复用

	/* 配置GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;            //工作在复用模式
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	        //使用内部上拉电阻
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 配置USART */
	USART_InitStructure.USART_BaudRate = 9600;	                    //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b  ;   //8bit数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;          //1bit停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //无校验位
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
	USART_Init(USART1, &USART_InitStructure);                       //完成初始化
	USART_Cmd(USART1, ENABLE);		                                  //使能串口
	USART1->SR &= ~0x0040;                                          //SR寄存器的TC位清零
}
		
/*字节发送函数 */
void UartSendByte(USART_TypeDef *USARTx, uint8_t ch)
{
	 USART_SendData(USARTx, ch);
	 /* 等待发送结束 */
	 while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == 0){ };  // 若FLAG=0,则等待至发完
}

/*字符串发送函数 */
void UartSendString(USART_TypeDef *USARTx, char *str)
{
	 uint16_t k =0; 
	 while (*(str+k) != '\0') //未到结尾则持续发送
	 {
		  USART_SendData(USARTx, *(str+k));
		  k++;
		  while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == 0){ }; // 若FLAG=0,则等待至发完	 

	 }
}

/*字节接收函数 */
uint8_t UartReceiveByte(USART_TypeDef *USARTx)
{
	uint8_t ch;
  while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == 0) {}; // 若FLAG=0, 则等待至收完
	ch = USART_ReceiveData(USARTx);
	return ch;
}


