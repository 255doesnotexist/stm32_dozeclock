/*
************************************************
* �ļ�: uart.c
* ����: ���ڲ�������
* ���ߣ�Lijh
************************************************
*/
//ͷ�ļ�����
#include "uart.h"

/*���ڳ�ʼ�� */
void UartInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/****************************USART1: TX = PA9, RX = PA10 *****************************/
	/* ���豸ʱ�� */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,  ENABLE);  //GPIOA ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  //USART1 ʱ��

	/* ����GPIO����USART���� */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  // PA9����
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //PA10����

	/* ����GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;            //�����ڸ���ģʽ
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	        //ʹ���ڲ���������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ����USART */
	USART_InitStructure.USART_BaudRate = 9600;	                    //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b  ;   //8bit����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;          //1bitֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;            //��У��λ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure);                       //��ɳ�ʼ��
	USART_Cmd(USART1, ENABLE);		                                  //ʹ�ܴ���
	USART1->SR &= ~0x0040;                                          //SR�Ĵ�����TCλ����
}
		
/*�ֽڷ��ͺ��� */
void UartSendByte(USART_TypeDef *USARTx, uint8_t ch)
{
	 USART_SendData(USARTx, ch);
	 /* �ȴ����ͽ��� */
	 while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == 0){ };  // ��FLAG=0,��ȴ�������
}

/*�ַ������ͺ��� */
void UartSendString(USART_TypeDef *USARTx, char *str)
{
	 uint16_t k =0; 
	 while (*(str+k) != '\0') //δ����β���������
	 {
		  USART_SendData(USARTx, *(str+k));
		  k++;
		  while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == 0){ }; // ��FLAG=0,��ȴ�������	 

	 }
}

/*�ֽڽ��պ��� */
uint8_t UartReceiveByte(USART_TypeDef *USARTx)
{
	uint8_t ch;
  while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == 0) {}; // ��FLAG=0, ��ȴ�������
	ch = USART_ReceiveData(USARTx);
	return ch;
}


