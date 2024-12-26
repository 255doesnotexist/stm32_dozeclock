/*
************************************************
* �ļ�: uart.h
* ����: ���ڲ���ͷ�ļ�
* ���ߣ�Lijh
************************************************
*/
//��ֹ�ظ�����
#ifndef __UART_H
#define __UART_H
#endif

//����ͷ�ļ�
#include "stm32f4xx.h"

//��������

void UartInit(void); 	                                  /*���ڳ�ʼ�� */
void UartSendByte(USART_TypeDef *USARTx, uint8_t ch);	  /*�ֽڷ��ͺ��� */
void UartSendString(USART_TypeDef *USARTx, char *str);  /*�ַ������ͺ��� */
uint8_t UartReceiveByte(USART_TypeDef *USARTx);         /*�ֽڽ��պ��� */




