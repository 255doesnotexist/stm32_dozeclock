/*
************************************************
* 文件: lcd.c
* 功能: LCD驱动函数库
* 型号：NOKIA5110，分辨率84*48，SPI接口
* 作者：Lijh
************************************************
*/
//头文件引用
#include "lcd.h"

//宏定义 - 基础操作
#define LCD_RESET_L() 	GPIO_ResetBits(LCD_Port, LCD_RST_Pin)   //复位端 - L
#define LCD_RESET_H() 	GPIO_SetBits(LCD_Port, LCD_RST_Pin)     //复位端 - H

#define LCD_DC_L()		  GPIO_ResetBits(LCD_Port, LCD_DC_Pin)    //命令模式
#define LCD_DC_H()		  GPIO_SetBits(LCD_Port, LCD_DC_Pin)	    //数据模式

//LCD像素信息
#define LCD_X		0x84  //横向-宽84像素
#define LCD_Y		0x48  //纵向-高48像素

/***局部函数声明***/
void LCD_SPI1_Init(void);    //SPI1初始
void LCD_WR_Cmd(uint8_t cw); //写入命令
void LCD_WR_Dat(uint8_t dw); //写入数据
void LCD_SetXY(uint8_t x, uint8_t y); //屏幕定位x,y
void delayus(uint8_t nus);    //延时函数

//微秒级延时函数
void delayus(uint8_t nus)
{        
   uint8_t i;
   while(nus--) 
   { 
     for(i = 0 ; i < 25 ; i++);
   } 
}

//LCD初始化
void LcdInit(void)
{
	//SPI端口初始化
	LCD_SPI1_Init();
	//复位一次LCD
	LCD_RESET_L();
	delayus(10);
	LCD_RESET_H();  	
	//参考手册或商家例程
	LCD_WR_Cmd(0x21);
	LCD_WR_Cmd(0xBF);
	LCD_WR_Cmd(0x13);
	LCD_WR_Cmd(0x20); //V=0 
	LCD_WR_Cmd(0x0C);
}

//SPI初始化
void LCD_SPI1_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStructure;

  //打开时钟	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,  ENABLE);
	
	//开启PB3-SCK, PB5-DIN为SPI复用功能
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	
	//初始化GPIO PB3-SCK, PB5-DIN, 两个复用模式端
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  /*设置为复用模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//初始化GPIO PB6-RESET, PPB9-DC,两个普通输出端
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		  /* 设为输出口 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* 设为推挽模式 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//配置SPI1参数
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  /* 全双工 */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;       /*主机模式*/
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   /* 数据帧8bits */
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;  /*时钟极性CPOL，空闲(初始)电平为1 */
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; /*时钟相位CPHA，偶数沿采样 */
	  /*SPI1 locates in APB2, BaudRate = fAPB2/16 = 84M/16 = 5.25M*/
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; /* 波特率分频系数16*/
  SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB; /*先发最高位MSB*/
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;  /*NSS位由软件控制*/
	SPI_Init(SPI1, &SPI_InitStructure);  /*完成配置*/
	SPI_Cmd (SPI1, ENABLE);	             /*打开SPI1*/
}

//向LCD写入命令
void LCD_WR_Cmd(uint8_t cw)
{
	LCD_DC_L(); //命令模式
	SPI_I2S_SendData(SPI1, cw);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0); /* 等待发完 */	
	delayus(2);
}

//向LCD写入数据
void LCD_WR_Dat(uint8_t dat)
{
	LCD_DC_H(); //数据模式
	SPI_I2S_SendData(SPI1, dat);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0); /* 等待发完 */	
	delayus(2);
}

//定位到LCD的x,y点, x轴0~83，y轴0~5 - 调用系统命令
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

/*****以下为全局函数，可在其他.c文件中调用****/
//LCD清屏-写0法
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

//在起始位置x,y处显示一个8×16的字符 - 宽8，高16
void LcdShowFont8X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)              //页控制
	 {
		 LCD_SetXY(x , y + i);  
		 for(j = 0 ; j < 8; j++)          //逐列写入
			 LCD_WR_Dat(pixel[i * 8 + j]);
	 }
}

//在起始位置x,y处显示一个16×16的字符 - 宽16，高16
void LcdShowFont16X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)              //页控制
	 {
		 LCD_SetXY(x , y + i); 
		 for(j = 0 ; j < 16; j++)
			 LCD_WR_Dat(pixel[i * 16 + j]); //逐列写入
	 }	
}

//满屏显示一个84×48的图片 - 宽84，高48
void LcdShowPic84X48(const uint8_t *pic)
{
  uint8_t i, j ;
	for(i = 0; i < 6; i++)               //页控制
	 {
		 LCD_SetXY(0 , i);      
		 for(j = 0 ; j < 84; j++) 
			LCD_WR_Dat(pic[i * 84 + j]);     //逐列写入
	 }	
}

