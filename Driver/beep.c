/*
************************************************
* �ļ�: beep.c
* ����: beepԴ�ļ�
* ���ߣ�jcy
************************************************
*/
//����ͷ�ļ�
#include "beep.h"
//��ʼ�������˿�
void BeepInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* ��GPIOʱ�� */
	RCC_AHB1PeriphClockCmd(BEEP_RCC, ENABLE);
	
	/* ����GPIOΪ�������ģʽ */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		    /* ��Ϊ����� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		  /* ��Ϊ����ģʽ */
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	  /* ���������費ʹ�� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  /* IO������ٶ� */
  /* ��ɶ˿ڳ�ʼ��*/
	GPIO_InitStructure.GPIO_Pin = BEEP_Pin;
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);
}


// ���������� - ռλ��
void BeepOn() {
    GPIO_ResetBits(BEEP_PORT , BEEP_Pin);
}


// ���������� - ռλ��
void BeepOff() {
    GPIO_SetBits(BEEP_PORT , BEEP_Pin);
}



// ���������� - ռλ��
void BeepToggle() {
    GPIO_ToggleBits(BEEP_PORT , BEEP_Pin);
}


