/*
************************************************
* �ļ�: key.h
* ����: KEYͷ�ļ�
* ���ߣ�Lijh
************************************************
*/
//��ֹ�ظ�����
#ifndef __KEY_H
#define __KEY_H
#endif

//����ͷ�ļ�
#include "stm32f4xx.h"

//����KEYö������
typedef enum
{
	KEY_NO = 0,  
	KEY1   = 1,      
	KEY2   = 2,      
	KEY3   = 3
}Key_t;

//KEY ���ƶ˿ں궨��
#define KEY1_RCC			RCC_AHB1Periph_GPIOI  //����ʱ��
#define KEY1_PORT		  GPIOI                 //�˿ڶ���
#define KEY1_Pin			GPIO_Pin_8            //���Ŷ���

#define KEY2_RCC			RCC_AHB1Periph_GPIOC  //����ʱ��
#define KEY2_PORT		  GPIOC                 //�˿ڶ���
#define KEY2_Pin			GPIO_Pin_13           //���Ŷ���

#define KEY3_RCC			RCC_AHB1Periph_GPIOI  //����ʱ��
#define KEY3_PORT		  GPIOI                 //�˿ڶ���
#define KEY3_Pin			GPIO_Pin_11           //���Ŷ���

//KEY ���ƺ�������
void  KeyInit(void);     //��ʼ������
Key_t GetKey(void);      //���񰴼�
void KeyExtiCfg(void);   //���жϳ�ʼ��

