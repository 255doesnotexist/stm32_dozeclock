/*
************************************************
* �ļ�: timer.h
* ����: ��ʱ���豸ͷ�ļ�
* ���ߣ�Lijh
************************************************
*/
//��ֹ�ظ�����
#ifndef __TIMER_H
#define __TIMER_H
#endif

//����ͷ�ļ�
#include "stm32f4xx.h"

//��������
void Tim2Init(void); /*��ʼ������*/
void Tim3Init(void);  /*��ʼ������*/
extern uint16_t otime;
extern uint16_t frqcount;
#define SetFreq(freq) frqcount=0;otime=(10000.0/(0.0874676873*(freq)))
