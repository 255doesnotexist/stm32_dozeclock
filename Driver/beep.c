/*
************************************************
* 文件: beep.c
* 功能: beep源文件
* 作者：jcy
************************************************
*/
//引用头文件
#include "beep.h"
//初始化按键端口
void BeepInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 打开GPIO时钟 */
	RCC_AHB1PeriphClockCmd(BEEP_RCC, ENABLE);
	
	/* 配置GPIO为推挽输出模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		    /* 设为输出口 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		  /* 设为推挽模式 */
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	  /* 上下拉电阻不使能 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  /* IO口最大速度 */
  /* 完成端口初始化*/
	GPIO_InitStructure.GPIO_Pin = BEEP_Pin;
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);
}


// 蜂鸣器发声 - 占位符
void BeepOn() {
    GPIO_ResetBits(BEEP_PORT , BEEP_Pin);
}


// 蜂鸣器发声 - 占位符
void BeepOff() {
    GPIO_SetBits(BEEP_PORT , BEEP_Pin);
}



// 蜂鸣器发声 - 占位符
void BeepToggle() {
    GPIO_ToggleBits(BEEP_PORT , BEEP_Pin);
}


