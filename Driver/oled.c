/*
************************************************
* �ļ�: oled.c
* ����: OLED����������
* ��񣺷ֱ���128*64������оƬSSD1306��SPI�ӿ�
* ���ߣ�Lijh
************************************************
*/
//ͷ�ļ�����
#include "oled.h"

//�궨�� - ��������
#define OLED_RESET_L() 	GPIO_ResetBits(OLED_Port, OLED_RES_Pin)   //��λ�� - L
#define OLED_RESET_H()	GPIO_SetBits(OLED_Port, OLED_RES_Pin)     //��λ�� - H

#define OLED_DC_L()		GPIO_ResetBits(OLED_Port, OLED_DC_Pin)      //����ģʽ
#define OLED_DC_H()		GPIO_SetBits(OLED_Port, OLED_DC_Pin)	      //����ģʽ

//OLED������Ϣ
#define OLED_X		0x128 //����-��128����
#define OLED_Y		0x64  //����-��64����

/***�ֲ���������***/
void OLED_SPI1_Init(void);    //SPI1��ʼ
void OLED_WR_Cmd(uint8_t cw); //д������
void OLED_WR_Dat(uint8_t dw); //д������
void OLED_SetXY(uint8_t x, uint8_t y); //��Ļ��λx,y
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

//OLED��ʼ��
void OledInit(void)
{
	//SPI�˿ڳ�ʼ��
	OLED_SPI1_Init();
	//��λһ��OLED
	OLED_RESET_L();
	delayus(10); //DatasheetҪ������ > 3��s
	OLED_RESET_H();  	
	//�ο��ֲ���̼�����
  OLED_WR_Cmd(0xae);//--turn off oled panel
  OLED_WR_Cmd(0x00);//---set low column address
  OLED_WR_Cmd(0x10);//---set high column address
  OLED_WR_Cmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_WR_Cmd(0x81);//--set contrast control register
  OLED_WR_Cmd(0xcf);// Set SEG Output Current Brightness
  OLED_WR_Cmd(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
  OLED_WR_Cmd(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
  OLED_WR_Cmd(0xa6);//--set normal display
  OLED_WR_Cmd(0xa8);//--set multiplex ratio(1 to 64)
  OLED_WR_Cmd(0x3f);//--1/64 duty
  OLED_WR_Cmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  OLED_WR_Cmd(0x00);//-not offset
  OLED_WR_Cmd(0xd5);//--set display clock divide ratio/oscillator frequency
  OLED_WR_Cmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  OLED_WR_Cmd(0xd9);//--set pre-charge period
  OLED_WR_Cmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_WR_Cmd(0xda);//--set com pins hardware configuration
  OLED_WR_Cmd(0x12);
  OLED_WR_Cmd(0xdb);//--set vcomh
  OLED_WR_Cmd(0x40);//Set VCOM Deselect Level
  OLED_WR_Cmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  OLED_WR_Cmd(0x02);//
  OLED_WR_Cmd(0x8d);//--set Charge Pump enable/disable
  OLED_WR_Cmd(0x14);//--set(0x10) disable
  OLED_WR_Cmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
  OLED_WR_Cmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
  OLED_WR_Cmd(0xaf);//--turn on oled panel
}

//SPI��ʼ��
void OLED_SPI1_Init(void)
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

//��OLEDд������
void OLED_WR_Cmd(uint8_t cw)
{
	OLED_DC_L(); //����ģʽ
	SPI_I2S_SendData(SPI1, cw);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0); /* �ȴ����� */	
	delayus(2);
}

//��OLEDд������
void OLED_WR_Dat(uint8_t dat)
{
	OLED_DC_H(); //����ģʽ
	SPI_I2S_SendData(SPI1, dat);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0); /* �ȴ����� */	
	delayus(2);
}

//��λ��OLED��x,y��, x��0~127��y��0~63 - ����ϵͳ����
void OLED_SetXY(uint8_t x, uint8_t y)
{
	OLED_WR_Cmd(0xb0+(y>>3));
  OLED_WR_Cmd(((x&0xf0)>>4)|0x10);
  OLED_WR_Cmd((x&0x0f)|0x01); 
}

/*****����Ϊȫ�ֺ�������������.c�ļ��е���****/
//OLED����-����ϵͳ����
void OledClear(void)
{
	uint8_t i,j;
	for(i=0; i<8; i++)
	{
		OLED_WR_Cmd(0xb0+i);
		OLED_WR_Cmd(0x01);
		OLED_WR_Cmd(0x10);
		for(j=0; j<128; j++)
			OLED_WR_Dat(0x00);
	}
}

//����ʼλ��x,y����ʾһ��1��16���ַ� - ��1����16
void OledShowFont1X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,������8���㣬��ΪOLED Y�����Ե㶨λ 
		 for(j = 0 ; j < 1; j++)
			 OLED_WR_Dat(pixel[i * 8 + j]);
	 }
}

//����ʼλ��x,y����ʾһ��8��16���ַ� - ��8����16
void OledShowFont8X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,������8���㣬��ΪOLED Y�����Ե㶨λ 
		 for(j = 0 ; j < 8; j++)
			 OLED_WR_Dat(pixel[i * 8 + j]);
	 }
}

//����ʼλ��x,y����ʾһ��16��16���ַ� - ��16����16
void OledShowFont16X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,������8���㣬��ΪOLED Y�����Ե㶨λ 
		 for(j = 0 ; j < 16; j++)
			 OLED_WR_Dat(pixel[i * 16 + j]);
	 }	
}
//����ʼλ��x,y����ʾһ��8��16���ַ� - ��8����16
void OledShowFont8X16R(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,������8���㣬��ΪOLED Y�����Ե㶨λ 
		 for(j = 0 ; j < 8; j++)
			 OLED_WR_Dat(~pixel[i * 8 + j]);
	 }
}

//����ʼλ��x,y����ʾһ��16��16���ַ� - ��16����16
void OledShowFont16X16R(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,������8���㣬��ΪOLED Y�����Ե㶨λ 
		 for(j = 0 ; j < 16; j++)
			 OLED_WR_Dat(~pixel[i * 16 + j]);
	 }	
}

//������ʾһ��128��64��ͼƬ - ��128����64
void OledShowPic128X64(const uint8_t *pic)
{
  uint8_t i, j ;
	for(i = 0; i < 8; i++)
	 {
		 OLED_SetXY(0 , i*8);      //*8,������8���㣬��ΪY�����Ե㶨λ 
		 for(j = 0 ; j < 128; j++) //�����ԣ���ΧΪ0~126����127���ƻص���0��
			OLED_WR_Dat(pic[i * 128 + j]);
	 }	
}

