/*
************************************************
* �ļ�: key.c
* ����: KeyԴ�ļ�
* ���ߣ�Lijh
************************************************
*/
//����ͷ�ļ�
#include "key.h"

//��ʼ���������ж�
void KeyExtiCfg(void)
{	
	EXTI_InitTypeDef  EXTI_InitStructure;
	/* ʹ�ܿ���EXTI���ӵ�SYSCFGʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	
	/* ����Key1(PI8)�˿ڵ�EXTI���ù���*/
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOI, EXTI_PinSource8); 
	
	/*����Key1(PI8)��EXTI�ж�*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;               //���ж���
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;      //�жϷ�ʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd=  ENABLE;                //ʹ��
	EXTI_Init(&EXTI_InitStructure);
}

//��ʼ�������˿�
void KeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* ��GPIOʱ�� */
	RCC_AHB1PeriphClockCmd(KEY1_RCC | KEY2_RCC | KEY3_RCC, ENABLE);
	
	/* ���ö˿�Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		  /* ��Ϊ����� */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* �������������� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* IO������ٶ� */
  /* ��ɶ˿ڳ�ʼ��*/
	GPIO_InitStructure.GPIO_Pin = KEY1_Pin;
	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY2_Pin;
	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY3_Pin;
	GPIO_Init(KEY3_PORT, &GPIO_InitStructure);
}

//��ȡ�������������øú��������ذ����ļ�ֵ(�ĸ�����)
Key_t GetKey(void)
{
	uint8_t temp1,temp2,temp3;
	Key_t key = KEY_NO; //Ĭ���޼�����
	/*��ȡ��������*/
	temp1 = GPIO_ReadInputDataBit(KEY1_PORT, KEY1_Pin); 
	temp2 = GPIO_ReadInputDataBit(KEY2_PORT, KEY2_Pin);
	temp3 = GPIO_ReadInputDataBit(KEY3_PORT, KEY3_Pin); 
	/*�жϰ���״̬*/
  if(temp1 == 0x00)
		key = KEY1;
	if(temp2 == 0x00)
		key = KEY2;
	if(temp3 == 0x00)
		key = KEY3;
	return key; //���ؼ�ֵ
}
