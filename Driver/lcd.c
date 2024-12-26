/*
************************************************
* �ļ�: lcd.c
* ����: LCD����������
* �ͺţ�NOKIA5110���ֱ���84*48��SPI�ӿ�
* ���ߣ�Lijh
************************************************
*/
//ͷ�ļ�����
#include "lcd.h"

//�궨�� - ��������
#define LCD_RESET_L() 	GPIO_ResetBits(LCD_Port, LCD_RST_Pin)   //��λ�� - L
#define LCD_RESET_H() 	GPIO_SetBits(LCD_Port, LCD_RST_Pin)     //��λ�� - H

#define LCD_DC_L()		  GPIO_ResetBits(LCD_Port, LCD_DC_Pin)    //����ģʽ
#define LCD_DC_H()		  GPIO_SetBits(LCD_Port, LCD_DC_Pin)	    //����ģʽ

//LCD������Ϣ
#define LCD_X		0x84  //����-��84����
#define LCD_Y		0x48  //����-��48����

/***�ֲ���������***/
void LCD_SPI1_Init(void);    //SPI1��ʼ
void LCD_WR_Cmd(uint8_t cw); //д������
void LCD_WR_Dat(uint8_t dw); //д������
void LCD_SetXY(uint8_t x, uint8_t y); //��Ļ��λx,y
void delayus(uint8_t nus);    //��ʱ����

//΢�뼶��ʱ����
void delayus(uint8_t nus)
{        
   uint8_t i;
   while(nus--) 
   { 
     for(i = 0 ; i < 25 ; i++);
   } 
}

//LCD��ʼ��
void LcdInit(void)
{
	//SPI�˿ڳ�ʼ��
	LCD_SPI1_Init();
	//��λһ��LCD
	LCD_RESET_L();
	delayus(10);
	LCD_RESET_H();  	
	//�ο��ֲ���̼�����
	LCD_WR_Cmd(0x21);
	LCD_WR_Cmd(0xBF);
	LCD_WR_Cmd(0x13);
	LCD_WR_Cmd(0x20); //V=0 
	LCD_WR_Cmd(0x0C);
}

//SPI��ʼ��
void LCD_SPI1_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStructure;

  //��ʱ��	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,  ENABLE);
	
	//����PB3-SCK, PB5-DINΪSPI���ù���
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	
	//��ʼ��GPIO PB3-SCK, PB5-DIN, ��������ģʽ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  /*����Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//��ʼ��GPIO PB6-RESET, PPB9-DC,������ͨ�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		  /* ��Ϊ����� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* ��Ϊ����ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//����SPI1����
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  /* ȫ˫�� */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;       /*����ģʽ*/
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   /* ����֡8bits */
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;  /*ʱ�Ӽ���CPOL������(��ʼ)��ƽΪ1 */
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; /*ʱ����λCPHA��ż���ز��� */
	  /*SPI1 locates in APB2, BaudRate = fAPB2/16 = 84M/16 = 5.25M*/
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; /* �����ʷ�Ƶϵ��16*/
  SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB; /*�ȷ����λMSB*/
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;  /*NSSλ���������*/
	SPI_Init(SPI1, &SPI_InitStructure);  /*�������*/
	SPI_Cmd (SPI1, ENABLE);	             /*��SPI1*/
}

//��LCDд������
void LCD_WR_Cmd(uint8_t cw)
{
	LCD_DC_L(); //����ģʽ
	SPI_I2S_SendData(SPI1, cw);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0); /* �ȴ����� */	
	delayus(2);
}

//��LCDд������
void LCD_WR_Dat(uint8_t dat)
{
	LCD_DC_H(); //����ģʽ
	SPI_I2S_SendData(SPI1, dat);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0); /* �ȴ����� */	
	delayus(2);
}

//��λ��LCD��x,y��, x��0~83��y��0~5 - ����ϵͳ����
void LCD_SetXY(uint8_t x, uint8_t y)
{
	//this LCD have only 84*48 pixel, 48/8=6,thats 0~5.
	if(x > 83)
		x= 0;
	if(y > 5)
		y = 0;
	LCD_WR_Cmd(0x40 | y);  //reference to the 5110 user manual, table 1.
	LCD_WR_Cmd(0x80 | x);
}

/*****����Ϊȫ�ֺ�������������.c�ļ��е���****/
//LCD����-д0��
void LcdClear(void)
{
	uint8_t i,j;
	LCD_SetXY(0,0);
	//84*48 pixels.
	for(i = 0; i < 84; i++)
		{
			for(j = 0; j < 6; j++)
				LCD_WR_Dat(0);
		}
}

//����ʼλ��x,y����ʾһ��8��16���ַ� - ��8����16
void LcdShowFont8X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)              //ҳ����
	 {
		 LCD_SetXY(x , y + i);  
		 for(j = 0 ; j < 8; j++)          //����д��
			 LCD_WR_Dat(pixel[i * 8 + j]);
	 }
}

//����ʼλ��x,y����ʾһ��16��16���ַ� - ��16����16
void LcdShowFont16X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)              //ҳ����
	 {
		 LCD_SetXY(x , y + i); 
		 for(j = 0 ; j < 16; j++)
			 LCD_WR_Dat(pixel[i * 16 + j]); //����д��
	 }	
}

//������ʾһ��84��48��ͼƬ - ��84����48
void LcdShowPic84X48(const uint8_t *pic)
{
  uint8_t i, j ;
	for(i = 0; i < 6; i++)               //ҳ����
	 {
		 LCD_SetXY(0 , i);      
		 for(j = 0 ; j < 84; j++) 
			LCD_WR_Dat(pic[i * 84 + j]);     //����д��
	 }	
}

