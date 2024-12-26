/*
************************************************
* 文件: led.c
* 功能: LED源文件
* 作者：Lijh
************************************************
*/

//引用头文件
#include "led.h"

//初始化LED端口
void LedInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* 打开GPIO时钟 */
	RCC_AHB1PeriphClockCmd(LED2_RCC | LED4_RCC , ENABLE);  
	
	/* 配置GPIO为推挽输出模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		    /* 设为输出口 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		  /* 设为推挽模式 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	  /* 上下拉电阻不使能 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  /* IO口最大速度 */
	
  /* 完成LED初始化 */
 	GPIO_InitStructure.GPIO_Pin = LED2_Pin;
	GPIO_Init(LED2_Port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LED4_Pin;
	GPIO_Init(LED4_Port, &GPIO_InitStructure);
}

//点亮一个LED
void LedOn(Led_t led)   /*形参led为枚举型变量， 其值指明具体的LED*/
{
	if(led == LED2)
		GPIO_ResetBits(LED2_Port , LED2_Pin);
	if(led == LED4)
		GPIO_ResetBits(LED4_Port , LED4_Pin);
}

//熄灭一个LED
void LedOff(Led_t led)   /*形参led为枚举型变量， 其值指明具体的LED*/
{
	if(led == LED2)
		GPIO_SetBits(LED2_Port , LED2_Pin);
	if(led == LED4)
		GPIO_SetBits(LED4_Port , LED4_Pin);
}

//亮灭切换LED
void LedToggle(Led_t led)   /*形参led为枚举型变量， 其值指明具体的LED*/
{
	if(led == LED2)
		GPIO_ToggleBits(LED2_Port , LED2_Pin);
	if(led == LED4)
		GPIO_ToggleBits(LED4_Port , LED4_Pin);
}

