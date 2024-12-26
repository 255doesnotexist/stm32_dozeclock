/*
************************************************
* 文件: oled.h
* 功能: oled驱动头文件
* 规格：分辨率128*64，驱动芯片SSD1306，SPI接口
* 作者：Lijh
************************************************
*/
//防止重复引用
#ifndef __OLED_H
#define __OLED_H
#endif

//引用头文件
#include "stm32f4xx.h"

//端口引脚声明
#define OLED_RCC    			   RCC_AHB1Periph_GPIOB  //设备时钟
#define OLED_Port					   GPIOB

#define OLED_SCK_Pin			 	 GPIO_Pin_3	 //PB3 时钟
#define OLED_SDA_Pin				 GPIO_Pin_5	 //PB5 数据输入端-DIN-MOSI
#define OLED_RES_Pin				 GPIO_Pin_6	 //PB6 复位端-RESET
#define OLED_DC_Pin					 GPIO_Pin_9  //PB9 数据/命令选择
#define OLED_CS_Pin					 GND       	 //片选始终接地

/*全局函数声明*/
 //OLED初始化函数
void OledInit(void);
 //OLED清屏函数
void OledClear(void); 
 //在起始位置x,y处显示一个1×16的字符 - 宽1，高16
void OledShowFont1X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //在起始位置x,y处显示一个8×16的字符 - 宽8，高16
void OledShowFont8X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //在起始位置x,y处显示一个16×16的字符 - 宽16，高16
void OledShowFont16X16(uint8_t x, uint8_t y, const uint8_t *pixel);
 //在起始位置x,y处显示一个8×16的字符 - 宽8，高16
void OledShowFont8X16R(uint8_t x, uint8_t y, const uint8_t *pixel);
 //在起始位置x,y处显示一个16×16的字符 - 宽16，高16
void OledShowFont16X16R(uint8_t x, uint8_t y, const uint8_t *pixel);
 //满屏显示一个128*64的图片 - 宽128，高64
void OledShowPic128X64(const uint8_t *pic);
 //可自行增加函数
 //......
 