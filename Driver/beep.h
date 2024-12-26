/*
************************************************
* �ļ�: key.h
* ����: KEYͷ�ļ�
* ���ߣ�jcy
************************************************
*/
//��ֹ�ظ�����
#ifndef __BEEP_H
#define __BEEP_H
#endif

//����ͷ�ļ�
#include "stm32f4xx.h"

//KEY ���ƶ˿ں궨��
#define BEEP_RCC			RCC_AHB1Periph_GPIOA  //����ʱ��
#define BEEP_PORT		  GPIOA                 //�˿ڶ���
#define BEEP_Pin			GPIO_Pin_8            //���Ŷ���


//KEY ���ƺ�������
void  BeepInit(void);     //��ʼ������
void  BeepOn(void);
void  BeepOff(void);
void  BeepToggle(void);