/*
************************************************
* 文件: key.c
* 功能: Key源文件
* 作者：Lijh
************************************************
*/
//引用头文件
#include "key.h"

//初始化按键外中断
void KeyExtiCfg(void)
{	
	EXTI_InitTypeDef  EXTI_InitStructure;
	/* 使能控制EXTI连接的SYSCFG时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	/* 配置Key1(PI8)端口的EXTI复用功能*/
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOI, EXTI_PinSource8); 
	
	/*配置Key1(PI8)的EXTI中断*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;               //外中断线
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;      //中断方式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd=  ENABLE;                //使能
	EXTI_Init(&EXTI_InitStructure);
}

//初始化按键端口
void KeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 打开GPIO时钟 */
	RCC_AHB1PeriphClockCmd(KEY1_RCC | KEY2_RCC | KEY3_RCC, ENABLE);
	
	/* 配置端口为输入模式*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		  /* 设为输入口 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* 无需上下拉电阻 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* IO口最大速度 */
  /* 完成端口初始化*/
	GPIO_InitStructure.GPIO_Pin = KEY1_Pin;
	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY2_Pin;
	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY3_Pin;
	GPIO_Init(KEY3_PORT, &GPIO_InitStructure);
}

//获取按键函数，调用该函数将返回按键的键值(哪个按下)
Key_t GetKey(void)
{
	uint8_t temp1,temp2,temp3;
	Key_t key = KEY_NO; //默认无键按下
	/*读取按键引脚*/
	temp1 = GPIO_ReadInputDataBit(KEY1_PORT, KEY1_Pin); 
	temp2 = GPIO_ReadInputDataBit(KEY2_PORT, KEY2_Pin);
	temp3 = GPIO_ReadInputDataBit(KEY3_PORT, KEY3_Pin); 
	/*判断按键状态*/
  if(temp1 == 0x00)
		key = KEY1;
	if(temp2 == 0x00)
		key = KEY2;
	if(temp3 == 0x00)
		key = KEY3;
	return key; //返回键值
}
