/*
************************************************
* �ļ�: font.h
* ����: �ַ�����ͼ�α���
* ���ߣ�Lijh
************************************************
*/
//��ֹ�ظ�����
#ifndef __FONT_H
#define __FONT_H
#endif

//����0~9���룬��8����16
const uint8_t Decimal[] = {
 0x00,0xE0,0xF0,0x18,0x08,0x18,0xF0,0xE0,
 0x00,0x0F,0x1F,0x30,0x20,0x30,0x1F,0x0F, /*"0",0*/

 0x00,0x10,0x10,0xF8,0xF8,0x00,0x00,0x00,
 0x00,0x20,0x20,0x3F,0x3F,0x20,0x20,0x00, /*"1",1*/

 0x00,0x70,0x78,0x08,0x08,0x88,0xF8,0x70,
 0x00,0x30,0x38,0x2C,0x26,0x23,0x31,0x30, /*"2",2*/

 0x00,0x30,0x38,0x88,0x88,0xC8,0x78,0x30,
 0x00,0x18,0x38,0x20,0x20,0x31,0x1F,0x0E, /*"3",3*/

 0x00,0x00,0xC0,0xE0,0x30,0xF8,0xF8,0x00,
 0x00,0x07,0x07,0x24,0x24,0x3F,0x3F,0x24, /*"4",4*/

 0x00,0xF8,0xF8,0x88,0x88,0x88,0x08,0x08,
 0x00,0x19,0x39,0x21,0x20,0x31,0x1F,0x0E, /*"5",5*/

 0x00,0xE0,0xF0,0x98,0x88,0x98,0x18,0x00,
 0x00,0x0F,0x1F,0x31,0x20,0x31,0x1F,0x0E, /*"6",6*/

 0x00,0x38,0x38,0x08,0xC8,0xF8,0x38,0x08,
 0x00,0x00,0x00,0x3F,0x3F,0x00,0x00,0x00, /*"7",7*/

 0x00,0x70,0xF8,0x88,0x08,0x88,0xF8,0x70,
 0x00,0x1C,0x3E,0x23,0x21,0x23,0x3E,0x1C, /*"8",8*/

 0x00,0xE0,0xF0,0x18,0x08,0x18,0xF0,0xE0,
 0x00,0x00,0x31,0x33,0x22,0x33,0x1F,0x0F};/*"9",9*/

//Ӣ����ĸ���룬��8����16
const uint8_t LetterI[]= {
 0x00,0x08,0x08,0xF8,0xF8,0x08,0x08,0x00,0x00,0x20,0x20,0x3F,0x3F,0x20,0x20,0x00}; /*"I",0*/

//���ֱ��룬��16����16
/* ��ɽ��ѧ */
const uint8_t Ysu[] = {
 0x42,0x42,0x42,0xF2,0xF2,0x9F,0x9F,0x92,0x92,0x9F,0x9F,0xF2,0xF2,0x42,0x62,0x22,
 0x84,0xE4,0x66,0x0F,0x2F,0xE7,0xC7,0x04,0x24,0xE7,0xC7,0x07,0x2F,0xE8,0xCE,0x0E, /*"��",0*/
 
 0x00,0x00,0xF0,0xF0,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0xF0,0xF0,0x00,0x00,
 0x00,0x00,0x3F,0x3F,0x20,0x20,0x20,0x3F,0x3F,0x20,0x20,0x20,0x7F,0x7F,0x00,0x00, /*"ɽ",1*/

 0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xFF,0xFF,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
 0x80,0x80,0xC0,0x60,0x30,0x1C,0x0F,0x03,0x03,0x0F,0x1C,0x30,0x60,0xC0,0x80,0x80, /*"��",2*/

 0x40,0x70,0x31,0x97,0x96,0x90,0x91,0x97,0x96,0x90,0x98,0x9C,0x17,0x53,0x70,0x30,
 0x04,0x04,0x04,0x04,0x04,0x44,0xC4,0xFE,0x7E,0x07,0x05,0x04,0x04,0x04,0x04,0x04};/*"ѧ",3*/
 

/************************************************************************************
*ͼ�α��� 
*���ڵ��Ի�ͼ��������ƺ�λͼ����������ģ�����е����ͼƬ�������ɶ�Ӧ��ͼ�α��롣
*��ģ�����ɴ������޸�ͼƬ��ע����Ч��Χ0~126�У���127����Ч��
************************************************************************************/
//����ͼ������16����16
const uint8_t PicHeart[] ={
0xFC,0xFE,0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFE,0xFC,
0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03};
 

//����ͼ������128����64�����롪ͼ������������Χ��
const uint8_t PicStarNeg[] ={
                              /* y = 0 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //x = 0~15
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,  //x = 16~31
0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0xF0,0xF0,0xF8,0xF8,0xF8,0xF8,0xFC,0x7C,0x7C,0x7C,  //......
0x7C,0x7C,0x7C,0x3E,0x3E,0x3E,0x3E,0xBE,0xFE,0xFE,0xBE,0x3E,0x3E,0x3E,0x3E,0x3C,
0x7C,0x7C,0x7C,0x7C,0x7C,0xFC,0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,
0xC0,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //......
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //x = 112~127
	                            /* y = 1 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0xC0,0xC0,0xE0,0xF0,0xF8,0xFC,0xFC,0x7E,0x3F,0x3F,0x1F,0x0F,
0x0F,0x07,0x07,0x03,0x03,0x03,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x03,0x07,
0x07,0x0F,0x0F,0x1F,0x3F,0x3F,0x7E,0xFC,0xFC,0xF8,0xF0,0xE0,0xE0,0xC0,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	                            /* y = 2 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,
0xF8,0xFC,0xFE,0xFF,0x3F,0x1F,0x0F,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xE0,0xFC,0xFF,0xFF,0xFF,0x3F,0x07,0x07,0x3F,0xFF,0xFF,0xFF,0xFC,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x0F,0x1F,0x3F,0xFF,0xFE,
0xFC,0xF8,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                              /* y = 3 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFE,0xFF,0xFF,
0xFF,0x1F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0E,0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0xDF,0x9F,0x1F,0x1F,0x1F,
0x1F,0x1F,0x1F,0x1F,0x0F,0x07,0x01,0x00,0x00,0x00,0x00,0x01,0x07,0x0F,0x1F,0x1F,
0x1F,0x1F,0x1F,0x1F,0x1F,0x9F,0xDF,0xDF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x3F,
0x1F,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0x1F,0xFF,0xFF,0xFF,0xFE,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                               /* y = 4 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,
0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x08,0x00,0x01,0x03,0x03,0x07,0x0F,0x1F,0x1F,0xFF,0xFE,0xFE,
0xFC,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xF8,0xFC,0xFE,0xFE,0xFF,0x1F,0x1F,0x0F,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xE0,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                              /* y = 5 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x1F,
0x7F,0xFF,0xFF,0xFC,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xF0,0xFF,0xFF,0xFF,0xFF,
0x1F,0x81,0xC0,0xE0,0xE0,0xF0,0xF8,0xFC,0xFC,0xFC,0xFC,0xF8,0xF0,0xE0,0xE0,0xC0,
0x81,0x8F,0xFF,0xFF,0xFF,0xFF,0xF0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF0,0xFC,0xFF,
0xFF,0x7F,0x3F,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                              /* y = 6 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x07,0x0F,0x1F,0x1F,0x3F,0x7E,0xFE,0xFC,0xF8,0xF0,0xF0,0xE0,0xC0,
0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,
0x3F,0x1F,0x0F,0x0F,0x07,0x03,0x01,0x01,0x00,0x00,0x01,0x01,0x03,0x07,0x07,0x0F,
0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0xF8,0xFC,0xFE,0x7E,0x3F,0x1F,0x1F,0x0F,0x07,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                             /* y = 7 */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x07,
0x0F,0x0F,0x1F,0x1F,0x1F,0x3F,0x3E,0x7E,0x7C,0x7C,0x7D,0x7D,0xF9,0xF8,0xF8,0xF8,
0xF8,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
0xF8,0xF8,0xF8,0xF8,0xF8,0xF9,0x7D,0x7D,0x7C,0x7C,0x7E,0x3E,0x3F,0x1F,0x1F,0x1F,
0x0F,0x0F,0x07,0x07,0x03,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

//����ͼ������128����64�����롪��ͼ������������Χ��
const uint8_t PicStarPos[]={
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,
0x3F,0x3F,0x1F,0x1F,0x1F,0x0F,0x0F,0x0F,0x07,0x07,0x07,0x07,0x03,0x83,0x83,0x83,
0x83,0x83,0x83,0xC1,0xC1,0xC1,0xC1,0x41,0x01,0x01,0x41,0xC1,0xC1,0xC1,0xC1,0xC3,
0x83,0x83,0x83,0x83,0x83,0x03,0x07,0x07,0x07,0x07,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,
0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0x7F,0x3F,0x3F,0x1F,0x0F,0x07,0x03,0x03,0x81,0xC0,0xC0,0xE0,0xF0,
0xF0,0xF8,0xF8,0xFC,0xFC,0xFC,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x7F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x7F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC,0xFC,0xF8,
0xF8,0xF0,0xF0,0xE0,0xC0,0xC0,0x81,0x03,0x03,0x07,0x0F,0x1F,0x1F,0x3F,0x7F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x1F,
0x07,0x03,0x01,0x00,0xC0,0xE0,0xF0,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x1F,0x03,0x00,0x00,0x00,0xC0,0xF8,0xF8,0xC0,0x00,0x00,0x00,0x03,0x1F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xF0,0xE0,0xC0,0x00,0x01,
0x03,0x07,0x1F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x01,0x00,0x00,
0x00,0xE0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF1,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x60,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xF0,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFE,0xF8,0xF0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xE0,0x60,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,
0xE0,0xF1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,
0xE0,0x00,0x00,0x00,0x01,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,
0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xFC,0xF8,0xF0,0xE0,0xE0,0x00,0x01,0x01,
0x03,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x07,0x03,0x01,0x01,0x00,0xE0,0xE0,0xF0,0xF8,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x1F,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF8,0xE0,
0x80,0x00,0x00,0x03,0x0F,0x1F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x0F,0x00,0x00,0x00,0x00,
0xE0,0x7E,0x3F,0x1F,0x1F,0x0F,0x07,0x03,0x03,0x03,0x03,0x07,0x0F,0x1F,0x1F,0x3F,
0x7E,0x70,0x00,0x00,0x00,0x00,0x0F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x0F,0x03,0x00,
0x00,0x80,0xC0,0xF0,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFE,0xF8,0xF0,0xE0,0xE0,0xC0,0x81,0x01,0x03,0x07,0x0F,0x0F,0x1F,0x3F,
0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x80,0xC0,
0xC0,0xE0,0xF0,0xF0,0xF8,0xFC,0xFE,0xFE,0xFF,0xFF,0xFE,0xFE,0xFC,0xF8,0xF8,0xF0,
0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,
0x7F,0x3F,0x3F,0x1F,0x1F,0x0F,0x07,0x03,0x01,0x81,0xC0,0xE0,0xE0,0xF0,0xF8,0xFE,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xFC,0xF8,0xF8,
0xF0,0xF0,0xE0,0xE0,0xE0,0xC0,0xC1,0x81,0x83,0x83,0x82,0x82,0x06,0x07,0x07,0x07,
0x07,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,
0x07,0x07,0x07,0x07,0x07,0x06,0x82,0x82,0x83,0x83,0x81,0xC1,0xC0,0xE0,0xE0,0xE0,
0xF0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

//����ͼ������84����48��LCD����
const uint8_t PicStar8448[] ={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xE0,
0xF0,0xF0,0xF0,0xF0,0xF8,0xF8,0xF8,0xF8,0x7C,0x7C,0x7C,0x7C,0xF8,0xF8,0xF8,0xF8,
0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0xC0,0x80,0x80,0x80,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xE0,0xF0,0xF0,0xF8,0xF8,0xF8,0xF8,0xFC,0x7C,0x7C,0x7C,
0x7E,0x3E,0x3E,0x3E,0x3F,0x1F,0x1F,0x1F,0x1F,0x0F,0x0F,0x0F,0x0F,0x07,0x07,0x07,
0x07,0x03,0x03,0x03,0x03,0x01,0x01,0x01,0x00,0x00,0x00,0xF0,0xFE,0xFF,0xFF,0xFF,
0xFE,0xF0,0x80,0x00,0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x03,0x07,0x07,0x07,0x0F,
0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x1F,0x3F,0x3E,0x3E,0x3E,0x7E,0x7C,0x7C,0x7C,0xFC,
0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xE0,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,0xE0,0xF0,0xF0,0xF0,0xF8,0xF8,0xFF,0x7F,
0x7F,0x3F,0x0F,0x3F,0x7F,0x7F,0xFF,0xF8,0xF8,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xC0,
0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x07,0x07,0x0F,0x0F,0x0F,
0x1F,0x1F,0xFF,0xFE,0xFE,0xFC,0xF0,0xFC,0xFE,0xFE,0xFF,0x1F,0x1F,0x0F,0x0F,0x0F,
0x07,0x07,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
0x00,0x07,0x0F,0x0F,0x1F,0x1F,0x1F,0x1F,0x3F,0x3E,0x3E,0x3E,0x7E,0x7C,0x7C,0x7C,
0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0xC0,
0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x0F,0x7F,0xFF,0xFF,0xFF,0x7F,0x0F,0x01,0x00,
0x80,0x80,0x80,0x80,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xE0,0xF0,0xF0,0xF0,0xF0,
0xF8,0xF8,0xF8,0xF8,0x7C,0x7C,0x7C,0x7C,0x3E,0x3E,0x3E,0x3F,0x1F,0x1F,0x1F,0x1F,
0x0F,0x0F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x03,
0x07,0x07,0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,0x1F,0x3E,0x3E,0x3E,0x3E,
0x1F,0x1F,0x1F,0x1F,0x0F,0x0F,0x0F,0x0F,0x07,0x07,0x07,0x07,0x03,0x03,0x03,0x03,
0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
