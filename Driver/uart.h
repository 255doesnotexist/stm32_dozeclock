/*
************************************************
* 文件: uart.h
* 功能: 串口操作头文件
* 作者：Lijh
************************************************
*/
//防止重复引用
#ifndef __UART_H
#define __UART_H
#endif

//引用头文件
#include "stm32f4xx.h"

//函数声明

void UartInit(void); 	                                  /*串口初始化 */
void UartSendByte(USART_TypeDef *USARTx, uint8_t ch);	  /*字节发送函数 */
void UartSendString(USART_TypeDef *USARTx, char *str);  /*字符串发送函数 */
uint8_t UartReceiveByte(USART_TypeDef *USARTx);         /*字节接收函数 */




