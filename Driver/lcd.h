/*
************************************************
* 文件: lcd.h
* 功能: LCD驱动头文件
* 型号：NOKIA5110，分辨率84*48，SPI接口
* 作者：Lijh
************************************************
*/
//防止重复引用
#ifndef __LCD_H
#define __LCD_H
#endif

//引用头文件
#include "stm32f4xx.h"

//端口引脚声明
#define LCD_RCC    			   RCC_AHB1Periph_GPIOB  //设备时钟
#define LCD_Port					 GPIOB

#define LCD_CLK_Pin			 	 GPIO_Pin_3	      //PB3 时钟
#define LCD_DIN_Pin				 GPIO_Pin_5	      //PB5 数据输入端-DIN-MOSI
#define LCD_RST_Pin				 GPIO_Pin_6	      //PB6 复位端-RESET
#define LCD_DC_Pin				 GPIO_Pin_9       //PB9 数据/命令选择
#define LCD_CE_Pin				 GND       	      //片选始终接地
#define LCD_BL_Pin         VCC/3.3V/NULL    //背光直连Vcc或3.3V或空接

/*全局函数声明*/
 //LCD初始化函数
void LcdInit(void);
 //LCD清屏函数
void LcdClear(void); 
 //在起始位置x,y处显示一个8×16的字符 - 宽8，高16
void LcdShowFont8X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //在起始位置x,y处显示一个16×16的字符 - 宽16，高16
void LcdShowFont16X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //满屏显示一个84*48的图片 - 宽84，高48
void LcdShowPic84X48(const uint8_t *pic);
 //可自行增加函数
 //......
 
