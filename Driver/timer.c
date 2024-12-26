/*
************************************************
* �ļ�: timer.c
* ����: ��ʱ���Ĳ�������
* ���ߣ�Lijh
************************************************
*/
/*---------------------------------------------------------------------------------
APB1 ����Ƶ��84MHz, ��ʱ���� TIM2, TIM3 ,TIM4, TIM5, TIM6, TIM7, TIM12, TIM13,TIM14
APB2 ����Ƶ��168MHz,��ʱ���� TIM1, TIM8 ,TIM9, TIM10, TIM11
--------------------------------------------------------------------------------- */
//����ͷ�ļ�
#include "timer.h"

 /*��ʱ��2�ĳ�ʼ�� */
	void Tim2Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_Cmd(TIM2, DISABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
 	TIM_TimeBaseStructure.TIM_Period =    100;
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;
 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //�������
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);		  
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_Cmd(TIM2, ENABLE);
}	

 /*��ʱ��3�ĳ�ʼ�� */
	void Tim3Init(uint16_t time)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_Cmd(TIM3, DISABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
 	TIM_TimeBaseStructure.TIM_Period = time * 1000;
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;
 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //�������
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);		
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_Cmd(TIM3, ENABLE);
}	


