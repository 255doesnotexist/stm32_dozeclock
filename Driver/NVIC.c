/*
************************************************
* �ļ�: NVIC.c
* ����: NVIC�ж�����
* ���ߣ�Lijh
************************************************
*/
//����ͷ�ļ�
#include "NVIC.h"

//NVIC��ʼ��
void NvicCfg(void)
{ 
		NVIC_InitTypeDef  NVIC_InitStructure;
	  /* Configure the NVIC Group */  
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	  //���� Key1(PI8)��NVIC����
    //NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;         //�ж�ͨ��
	  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //�����ȼ�
	  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //�����ȼ�
		//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //�ж�ʹ�� 
	  //NVIC_Init(&NVIC_InitStructure);                            //��ɳ�ʼ��
	
	  //TIM2��NVIC����
	  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;          
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;     
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
    NVIC_Init(&NVIC_InitStructure);  
	
		//TIM3��NVIC����
	  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;          
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
    NVIC_Init(&NVIC_InitStructure);  
	
}


