/*
************************************************
* �ļ�: oled.h
* ����: oled����ͷ�ļ�
* ��񣺷ֱ���128*64������оƬSSD1306��SPI�ӿ�
* ���ߣ�Lijh
************************************************
*/
//��ֹ�ظ�����
#ifndef __OLED_H
#define __OLED_H
#endif

//����ͷ�ļ�
#include "stm32f4xx.h"

//�˿���������
#define OLED_RCC    			   RCC_AHB1Periph_GPIOB  //�豸ʱ��
#define OLED_Port					   GPIOB

#define OLED_SCK_Pin			 	 GPIO_Pin_3	 //PB3 ʱ��
#define OLED_SDA_Pin				 GPIO_Pin_5	 //PB5 ���������-DIN-MOSI
#define OLED_RES_Pin				 GPIO_Pin_6	 //PB6 ��λ��-RESET
#define OLED_DC_Pin					 GPIO_Pin_9  //PB9 ����/����ѡ��
#define OLED_CS_Pin					 GND       	 //Ƭѡʼ�սӵ�

/*ȫ�ֺ�������*/
 //OLED��ʼ������
void OledInit(void);
 //OLED��������
void OledClear(void); 
 //����ʼλ��x,y����ʾһ��1��16���ַ� - ��1����16
void OledShowFont1X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //����ʼλ��x,y����ʾһ��8��16���ַ� - ��8����16
void OledShowFont8X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //����ʼλ��x,y����ʾһ��16��16���ַ� - ��16����16
void OledShowFont16X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //����ʼλ��x,y����ʾһ��8��16���ַ� - ��8����16
void OledShowFont8X16R(uint8_t x, uint8_t y, const uint8_t *pixel);
 //����ʼλ��x,y����ʾһ��16��16���ַ� - ��16����16
void OledShowFont16X16R(uint8_t x, uint8_t y, const uint8_t *pixel);
 //������ʾһ��128*64��ͼƬ - ��128����64
void OledShowPic128X64(const uint8_t *pic);
 //���������Ӻ���
 //......
 