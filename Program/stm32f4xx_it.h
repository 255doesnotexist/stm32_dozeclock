/*
*********************************************************************************************************
*
*	模块名称 : 中断服务程序
*	文件名称 : stm32f4xx_it.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*********************************************************************************************************
*/

#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void); 
	 
//中断服务程序声明
void EXTI9_5_IRQHandler(void);
	

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */


