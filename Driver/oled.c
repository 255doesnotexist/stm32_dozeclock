/*
************************************************
* 文件: oled.c
* 功能: OLED驱动函数库
* 规格：分辨率128*64，驱动芯片SSD1306，SPI接口
* 作者：Lijh
************************************************
*/
//头文件引用
#include "oled.h"

//宏定义 - 基础操作
#define OLED_RESET_L() 	GPIO_ResetBits(OLED_Port, OLED_RES_Pin)   //复位端 - L
#define OLED_RESET_H()	GPIO_SetBits(OLED_Port, OLED_RES_Pin)     //复位端 - H

#define OLED_DC_L()		GPIO_ResetBits(OLED_Port, OLED_DC_Pin)      //命令模式
#define OLED_DC_H()		GPIO_SetBits(OLED_Port, OLED_DC_Pin)	      //数据模式

//OLED像素信息
#define OLED_X		0x128 //横向-宽128像素
#define OLED_Y		0x64  //纵向-高64像素

/***局部函数声明***/
void OLED_SPI1_Init(void);    //SPI1初始
void OLED_WR_Cmd(uint8_t cw); //写入命令
void OLED_WR_Dat(uint8_t dw); //写入数据
void OLED_SetXY(uint8_t x, uint8_t y); //屏幕定位x,y
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

//OLED初始化
void OledInit(void)
{
	//SPI端口初始化
	OLED_SPI1_Init();
	//复位一次OLED
	OLED_RESET_L();
	delayus(10); //Datasheet要求拉低 > 3μs
	OLED_RESET_H();  	
	//参考手册或商家例程
  OLED_WR_Cmd(0xae);//--turn off oled panel
  OLED_WR_Cmd(0x00);//---set low column address
  OLED_WR_Cmd(0x10);//---set high column address
  OLED_WR_Cmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_WR_Cmd(0x81);//--set contrast control register
  OLED_WR_Cmd(0xcf);// Set SEG Output Current Brightness
  OLED_WR_Cmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  OLED_WR_Cmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
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

//SPI初始化
void OLED_SPI1_Init(void)
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

//向OLED写入命令
void OLED_WR_Cmd(uint8_t cw)
{
	OLED_DC_L(); //命令模式
	SPI_I2S_SendData(SPI1, cw);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0); /* 等待发完 */	
	delayus(2);
}

//向OLED写入数据
void OLED_WR_Dat(uint8_t dat)
{
	OLED_DC_H(); //数据模式
	SPI_I2S_SendData(SPI1, dat);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0); /* 等待发完 */	
	delayus(2);
}

//定位到OLED的x,y点, x轴0~127，y轴0~63 - 调用系统命令
void OLED_SetXY(uint8_t x, uint8_t y)
{
	OLED_WR_Cmd(0xb0+(y>>3));
  OLED_WR_Cmd(((x&0xf0)>>4)|0x10);
  OLED_WR_Cmd((x&0x0f)|0x01); 
}

/*****以下为全局函数，可在其他.c文件中调用****/
//OLED清屏-调用系统命令
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

//在起始位置x,y处显示一个1×16的字符 - 宽1，高16
void OledShowFont1X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,纵向跨过8个点，因为OLED Y轴是以点定位 
		 for(j = 0 ; j < 1; j++)
			 OLED_WR_Dat(pixel[i * 8 + j]);
	 }
}

//在起始位置x,y处显示一个8×16的字符 - 宽8，高16
void OledShowFont8X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,纵向跨过8个点，因为OLED Y轴是以点定位 
		 for(j = 0 ; j < 8; j++)
			 OLED_WR_Dat(pixel[i * 8 + j]);
	 }
}

//在起始位置x,y处显示一个16×16的字符 - 宽16，高16
void OledShowFont16X16(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,纵向跨过8个点，因为OLED Y轴是以点定位 
		 for(j = 0 ; j < 16; j++)
			 OLED_WR_Dat(pixel[i * 16 + j]);
	 }	
}
//在起始位置x,y处显示一个8×16的字符 - 宽8，高16
void OledShowFont8X16R(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,纵向跨过8个点，因为OLED Y轴是以点定位 
		 for(j = 0 ; j < 8; j++)
			 OLED_WR_Dat(~pixel[i * 8 + j]);
	 }
}

//在起始位置x,y处显示一个16×16的字符 - 宽16，高16
void OledShowFont16X16R(uint8_t x, uint8_t y, const uint8_t *pixel)
{
  uint8_t i, j ;
	for(i = 0; i < 2; i++)
	 {
		 OLED_SetXY(x , y + i*8); //*8,纵向跨过8个点，因为OLED Y轴是以点定位 
		 for(j = 0 ; j < 16; j++)
			 OLED_WR_Dat(~pixel[i * 16 + j]);
	 }	
}

//满屏显示一个128×64的图片 - 宽128，高64
void OledShowPic128X64(const uint8_t *pic)
{
  uint8_t i, j ;
	for(i = 0; i < 8; i++)
	 {
		 OLED_SetXY(0 , i*8);      //*8,纵向跨过8个点，因为Y轴是以点定位 
		 for(j = 0 ; j < 128; j++) //经测试，范围为0~126，第127会绕回到第0列
			OLED_WR_Dat(pic[i * 128 + j]);
	 }	
}

