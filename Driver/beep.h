/*
************************************************
* 文件: key.h
* 功能: KEY头文件
* 作者：jcy
************************************************
*/
//防止重复引用
#ifndef __BEEP_H
#define __BEEP_H
#endif

//引用头文件
#include "stm32f4xx.h"

//KEY 控制端口宏定义
#define BEEP_RCC			RCC_AHB1Periph_GPIOA  //外设时钟
#define BEEP_PORT		  GPIOA                 //端口定义
#define BEEP_Pin			GPIO_Pin_8            //引脚定义


//KEY 控制函数声明
void  BeepInit(void);     //初始化配置
void  BeepOn(void);
void  BeepOff(void);
void  BeepToggle(void);