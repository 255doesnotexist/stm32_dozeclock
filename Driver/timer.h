/*
************************************************
* 文件: timer.h
* 功能: 定时器设备头文件
* 作者：Lijh
************************************************
*/
//防止重复引用
#ifndef __TIMER_H
#define __TIMER_H
#endif

//引用头文件
#include "stm32f4xx.h"

//函数声明
void Tim2Init(void); /*初始化函数*/
void Tim3Init(void);  /*初始化函数*/
extern uint16_t otime;
extern uint16_t frqcount;
#define SetFreq(freq) frqcount=0;otime=(10000.0/(0.0874676873*(freq)))
