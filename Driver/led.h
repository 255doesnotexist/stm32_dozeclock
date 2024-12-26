/*
************************************************
* 文件: led.h
* 功能: LED头文件
* 作者：Lijh
************************************************
*/
//防止重复引用
#ifndef __LED_H
#define __LED_H
#endif

//引用头文件
#include "stm32f4xx.h"

//定义LED枚举类型
typedef enum
{
	LED1 = 1,
	LED2 = 2,
	LED3 = 3,
	LED4 = 4,
}Led_t;


//LED 控制端口宏定义
#define LED2_RCC			RCC_AHB1Periph_GPIOF  //外设时钟
#define LED2_Port		  GPIOF        //端口定义
#define LED2_Pin			GPIO_Pin_7   //引脚定义

#define LED4_RCC			RCC_AHB1Periph_GPIOC  //外设时钟
#define LED4_Port		  GPIOC        //端口定义
#define LED4_Pin			GPIO_Pin_2   //引脚定义


//LED 控制函数声明
void LedInit(void);     //初始化配置
void LedOn(Led_t);      //点灯
void LedOff(Led_t);     //灭灯
void LedToggle(Led_t);  //亮灭切换
