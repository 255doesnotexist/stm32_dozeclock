/*
************************************************
* �ļ�: lcd.h
* ����: LCD����ͷ�ļ�
* �ͺţ�NOKIA5110���ֱ���84*48��SPI�ӿ�
* ���ߣ�Lijh
************************************************
*/
//��ֹ�ظ�����
#ifndef __LCD_H
#define __LCD_H
#endif

//����ͷ�ļ�
#include "stm32f4xx.h"

//�˿���������
#define LCD_RCC    			   RCC_AHB1Periph_GPIOB  //�豸ʱ��
#define LCD_Port					 GPIOB

#define LCD_CLK_Pin			 	 GPIO_Pin_3	      //PB3 ʱ��
#define LCD_DIN_Pin				 GPIO_Pin_5	      //PB5 ���������-DIN-MOSI
#define LCD_RST_Pin				 GPIO_Pin_6	      //PB6 ��λ��-RESET
#define LCD_DC_Pin				 GPIO_Pin_9       //PB9 ����/����ѡ��
#define LCD_CE_Pin				 GND       	      //Ƭѡʼ�սӵ�
#define LCD_BL_Pin         VCC/3.3V/NULL    //����ֱ��Vcc��3.3V��ս�

/*ȫ�ֺ�������*/
 //LCD��ʼ������
void LcdInit(void);
 //LCD��������
void LcdClear(void); 
 //����ʼλ��x,y����ʾһ��8��16���ַ� - ��8����16
void LcdShowFont8X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //����ʼλ��x,y����ʾһ��16��16���ַ� - ��16����16
void LcdShowFont16X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //������ʾһ��84*48��ͼƬ - ��84����48
void LcdShowPic84X48(const uint8_t *pic);
 //���������Ӻ���
 //......
 
