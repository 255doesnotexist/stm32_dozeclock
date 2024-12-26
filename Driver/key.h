/*
************************************************
* 文件: key.h
* 功能: KEY头文件
* 作者：Lijh
************************************************
*/
//防止重复引用
#ifndef __KEY_H
#define __KEY_H
#endif

//引用头文件
#include "stm32f4xx.h"

//定义KEY枚举类型
typedef enum
{
	KEY_NO = 0,  
	KEY1   = 1,      
	KEY2   = 2,      
	KEY3   = 3
}Key_t;

//KEY 控制端口宏定义
#define KEY1_RCC			RCC_AHB1Periph_GPIOI  //外设时钟
#define KEY1_PORT		  GPIOI                 //端口定义
#define KEY1_Pin			GPIO_Pin_8            //引脚定义

#define KEY2_RCC			RCC_AHB1Periph_GPIOC  //外设时钟
#define KEY2_PORT		  GPIOC                 //端口定义
#define KEY2_Pin			GPIO_Pin_13           //引脚定义

#define KEY3_RCC			RCC_AHB1Periph_GPIOI  //外设时钟
#define KEY3_PORT		  GPIOI                 //端口定义
#define KEY3_Pin			GPIO_Pin_11           //引脚定义

//KEY 控制函数声明
void  KeyInit(void);     //初始化配置
Key_t GetKey(void);      //捕获按键
void KeyExtiCfg(void);   //外中断初始化

