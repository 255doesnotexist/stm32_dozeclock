/*
************************************************
* �ļ�: led.h
* ����: LEDͷ�ļ�
* ���ߣ�Lijh
************************************************
*/
//��ֹ�ظ�����
#ifndef __LED_H
#define __LED_H
#endif

//����ͷ�ļ�
#include "stm32f4xx.h"

//����LEDö������
typedef enum
{
	LED1 = 1,
	LED2 = 2,
	LED3 = 3,
	LED4 = 4,
}Led_t;


//LED ���ƶ˿ں궨��
#define LED2_RCC			RCC_AHB1Periph_GPIOF  //����ʱ��
#define LED2_Port		  GPIOF        //�˿ڶ���
#define LED2_Pin			GPIO_Pin_7   //���Ŷ���

#define LED4_RCC			RCC_AHB1Periph_GPIOC  //����ʱ��
#define LED4_Port		  GPIOC        //�˿ڶ���
#define LED4_Pin			GPIO_Pin_2   //���Ŷ���


//LED ���ƺ�������
void LedInit(void);     //��ʼ������
void LedOn(Led_t);      //���
void LedOff(Led_t);     //���
void LedToggle(Led_t);  //�����л�
