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
	void Tim3Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_Cmd(TIM3, DISABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
 	TIM_TimeBaseStructure.TIM_Period = 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1;
 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //�������
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);		
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_Cmd(TIM3, ENABLE);
}	

/*
1/(1*(time/10000))=freq
10000/freq=(time)
*/


/*
void SetFreq(uint16_t freq) {	
	Tim3Init();
}*/
