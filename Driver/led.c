/*
************************************************
* �ļ�: led.c
* ����: LEDԴ�ļ�
* ���ߣ�Lijh
************************************************
*/

//����ͷ�ļ�
#include "led.h"

//��ʼ��LED�˿�
void LedInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* ��GPIOʱ�� */
	RCC_AHB1PeriphClockCmd(LED2_RCC | LED4_RCC , ENABLE);  
	
	/* ����GPIOΪ�������ģʽ */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		    /* ��Ϊ����� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		  /* ��Ϊ����ģʽ */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	  /* ���������費ʹ�� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  /* IO������ٶ� */
	
  /* ���LED��ʼ�� */
 	GPIO_InitStructure.GPIO_Pin = LED2_Pin;
	GPIO_Init(LED2_Port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LED4_Pin;
	GPIO_Init(LED4_Port, &GPIO_InitStructure);
}

//����һ��LED
void LedOn(Led_t led)   /*�β�ledΪö���ͱ����� ��ֵָ�������LED*/
{
	if(led == LED2)
		GPIO_ResetBits(LED2_Port , LED2_Pin);
	if(led == LED4)
		GPIO_ResetBits(LED4_Port , LED4_Pin);
}

//Ϩ��һ��LED
void LedOff(Led_t led)   /*�β�ledΪö���ͱ����� ��ֵָ�������LED*/
{
	if(led == LED2)
		GPIO_SetBits(LED2_Port , LED2_Pin);
	if(led == LED4)
		GPIO_SetBits(LED4_Port , LED4_Pin);
}

//�����л�LED
void LedToggle(Led_t led)   /*�β�ledΪö���ͱ����� ��ֵָ�������LED*/
{
	if(led == LED2)
		GPIO_ToggleBits(LED2_Port , LED2_Pin);
	if(led == LED4)
		GPIO_ToggleBits(LED4_Port , LED4_Pin);
}

