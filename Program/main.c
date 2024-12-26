/*
************************************************
* 文件: main.c
* 功能: LCD & OLED 信息显示
* 作者：Lijh
************************************************
*/
#include "stm32f4xx.h"
#include "oled.h"
#include "timer.h"
#include "NVIC.h"
#include "key.h"
#include "led.h"
#include "font.h"
#include "global.h"
#include "beep.h"

// 全局变量
Page currentPage = MainMenu;
Selection currentSelection = MainMenu_EnterDozeCounting;
DozeCountingButtonState dozeButtonState = Button_StartDoze;
DozeCountingButtonState pauseButtonState = Button_PauseDoze;

uint32_t Global_Clock = 0;

uint8_t dozeMinutes = 0;
uint8_t dozeSeconds = 5; // 默认5分钟
uint8_t dozeMilliseconds = 0;

uint8_t countdownMinutes = 0;
uint8_t countdownSeconds = 0;
uint8_t countdownMilliseconds = 0;

uint8_t isCountingDown = 0;
uint8_t isPaused = 0;
uint8_t isDozeTimeSettingMode = 0;
uint8_t isPlaying = 0;
uint8_t isRinging = 0;
uint8_t dozeTimeSettingSelection = DozeTimeSetting_Minutes;
uint16_t NowSheetTick = 0;

// 宏定义音高（C2到C6）
#define C2  65
#define D2  73
#define E2  82
#define F2  87
#define G2  98
#define A2  110
#define B2  123
#define C3  131
#define D3  147
#define E3  165
#define F3  175
#define G3  196
#define A3  220
#define B3  247
#define C4  262
#define D4  294
#define E4  330
#define F4  349
#define G4  392
#define A4  440
#define B4  494
#define C5  523
#define D5  587
#define E5  659
#define F5  698
#define G5  784
#define A5  880
#define B5  988
#define C6  1047

// 宏定义拍子长度（单位：毫秒）
#define WHOLE_NOTE 1000
#define HALF_NOTE  500
#define QUARTER_NOTE 250
#define EIGHTH_NOTE 125

// 乐谱定义
int16_t RingSheet1[] = {C4, C4, G4, G4, A4, A4, G4, -1};  // 小星星
int16_t RingSheet1Time[] = {QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE, -1};

int16_t RingSheet2[] = {E4, E4, F4, G4, G4, F4, E4, D4, C4, C4, D4, E4, E4, D4, D4, -1};  // 欢乐颂
int16_t RingSheet2Time[] = {QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE, -1};

int16_t RingSheet3[] = {C4, G3, A3, E3, F3, C4, F3, G3, C4, G3, A3, E3, F3, C4, F3, G3, -1};  // 卡农片段
int16_t RingSheet3Time[] = {QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, HALF_NOTE, -1};

int16_t RingSheet4[] = {C5, C5, C5, C5, C5, -1};  // 闹钟声
int16_t RingSheet4Time[] = {EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, HALF_NOTE, -1};

int16_t RingSheet5[] = {
    G4, A4, C5, A4, E5, E5, D5, 0, G4, A4, C5, A4, D5, D5, C5, G4, F4, // Never gonna give you up Never gonna let you down
    -1
};

int16_t RingSheet5Time[] = {
    EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, 500, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE, QUARTER_NOTE, QUARTER_NOTE, // Never gonna give you up Never gonna let you down
    -1
};

// 可根据需要添加播放函数，用于播放各个乐谱

// 蜂鸣器相关
int16_t *CurrentRingSheet = RingSheet2; // 当前铃声
int16_t *CurrentRingSheetTime = RingSheet2Time; // 当前铃声
 

// 动画相关
int8_t aboutAnimationX[4] = {0, 30, 50, 80};
int8_t aboutAnimationDirection[4] = {1, 1, 1, 1};

// 懒清屏，防止闪烁
Page lastPage;
Selection lastSelection;

// 函数声明
void DisplayMainMenu(void);
void DisplayDozeCounting(void);
void DisplayDozeTimeSetting(void);
void DisplayCustomRing(void);
void DisplayAbout(void);
void HandleButtonPress(void);
void UpdateDisplay(void);
void TIM2_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void PlayRing(void);
void Beep(uint16_t freq, uint16_t t); // 假设的蜂鸣器驱动函数

//Delay program, unit: ms
void delayms(uint32_t msnum)
{        
   uint16_t i;
   while(msnum--)
   { 
     for(i = 0 ; i < 25*1000 ; i++);
   } 
}
			
//main program
int main(void) 
{  
	uint16_t Timelevel;
	//外设初始化	
	LedInit();
	KeyInit();
	Tim2Init();
	Tim3Init();
//	Tim3Init(5); //x*0.1秒
//	UartInit();
//	LcdInit();    //Lcd和Oled二选一
	OledInit();   //Lcd和Oled二选一
	BeepInit();
	//中断系统初始化
	NvicCfg();
	KeyExtiCfg();
	
	//LED控制
	LedOn(LED4);
	LedOff(LED2);

/*********************************************************************
*                             显示屏种类  		
*LCD 屏，规格：宽84×高48像素,  寻址范围：列号x = 0~83,  页号y = 0~5
*OLED屏，规格：宽128×高64像素，寻址范围：列号x = 0~127, 页号y = 0~7 
*********************************************************************/
		SetFreq(440);
  OledClear();//清屏
	isPlaying=0;
    // 主循环
    while (1) {
        UpdateDisplay();
			  PlayRing();
				if(GetKey() != KEY_NO) {
					delayms(20);
					if(GetKey() != KEY_NO) HandleButtonPress();
				}
        /*if(isCountingDown && !isPaused) {
             LedToggle(LED2);
        }*/
    }
}


// 更新显示
void UpdateDisplay(void) {
	if (lastPage != currentPage || lastSelection != currentSelection) {
		OledClear();
		lastPage = currentPage;
		lastSelection = currentSelection;
	}
	
    switch (currentPage) {
        case MainMenu:
            DisplayMainMenu();
            break;
        case DozeCounting:
            DisplayDozeCounting();
            break;
        case DozeTimeSetting:
            DisplayDozeTimeSetting();
            break;
        case CustomRing:
            DisplayCustomRing();
            break;
        case About:
            DisplayAbout();
            break;
    }
}

#define ConvertLineToPixel(line) ((line)*16)
#define ConvertRowToPixelCN(row) ((row)*16)

// 显示主菜单
void DisplayMainMenu(void) {
    const uint8_t FMainMenu_EnterDozeCounting[] = {
0x40,0x40,0x42,0xCC,0x00,0x80,0x88,0x88,0xFF,0x88,0x88,0xFF,0x88,0x88,0x80,0x00,
0x00,0x40,0x20,0x1F,0x20,0x40,0x50,0x4C,0x43,0x40,0x40,0x5F,0x40,0x40,0x40,0x00,// "进",0

0x00,0x00,0x00,0x00,0x00,0x01,0xE2,0x1C,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x03,0x0C,0x30,0x40,0x80,0x80,0x00,// "入",1

0x40,0x40,0x42,0xCC,0x00,0x40,0x40,0x40,0x40,0xFF,0x40,0x40,0x40,0x40,0x40,0x00,
0x00,0x00,0x00,0x7F,0x20,0x10,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,// "计",2

0x00,0xFC,0x84,0x84,0x84,0xFC,0x00,0x10,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0x00,
0x00,0x3F,0x10,0x10,0x10,0x3F,0x00,0x00,0x01,0x06,0x40,0x80,0x7F,0x00,0x00,0x00,// "时",3

0x00,0x00,0x00,0xFE,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,0x00,
0x08,0x08,0x04,0x84,0x62,0x1E,0x01,0x00,0x01,0xFE,0x02,0x04,0x04,0x08,0x08,0x00,// "界",4

0x02,0x02,0xE2,0x22,0x22,0xF2,0x2E,0x22,0x22,0xE2,0x22,0x22,0xE2,0x02,0x02,0x00,
0x00,0x00,0xFF,0x40,0x40,0x7F,0x49,0x49,0x49,0x7F,0x40,0x40,0xFF,0x00,0x00,0x00,// "面",5
		};
    const uint8_t FMainMenu_EnterDozeTimeSetting[] = {
0x10,0x10,0x10,0xFF,0x10,0x90,0x04,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x00,
0x04,0x44,0x82,0x7F,0x01,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,// "打",0

0x00,0xFC,0x24,0x24,0xFC,0x00,0x08,0xE8,0x08,0x08,0xFF,0x08,0x08,0xE8,0x08,0x00,
0x00,0x3F,0x11,0x11,0x3F,0x00,0x00,0x03,0x02,0x02,0x3F,0x42,0x42,0x47,0x70,0x00,// "盹",1

0x00,0xFC,0x84,0x84,0x84,0xFC,0x00,0x10,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0x00,
0x00,0x3F,0x10,0x10,0x10,0x3F,0x00,0x00,0x01,0x06,0x40,0x80,0x7F,0x00,0x00,0x00,// "时",2

0x00,0xF8,0x01,0x06,0x00,0xF0,0x12,0x12,0x12,0xF2,0x02,0x02,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x00,0x00,0x00,0x1F,0x11,0x11,0x11,0x1F,0x00,0x40,0x80,0x7F,0x00,0x00,// "间",3

0x40,0x40,0x42,0xCC,0x00,0x40,0xA0,0x9E,0x82,0x82,0x82,0x9E,0xA0,0x20,0x20,0x00,
0x00,0x00,0x00,0x3F,0x90,0x88,0x40,0x43,0x2C,0x10,0x28,0x46,0x41,0x80,0x80,0x00,// "设",4

0x00,0x17,0x15,0xD5,0x55,0x57,0x55,0x7D,0x55,0x57,0x55,0xD5,0x15,0x17,0x00,0x00,
0x40,0x40,0x40,0x7F,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x7F,0x40,0x40,0x40,0x00,// "置",5
		};
    const uint8_t FMainMenu_EnterCustomRing[] = {
0x80,0x80,0x40,0x20,0x10,0x08,0x04,0xC3,0x04,0x08,0x10,0x20,0x40,0x80,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// "个",0

0x00,0xE0,0x00,0xFF,0x10,0x20,0x40,0x3C,0x10,0x10,0xFF,0x10,0x10,0x10,0x00,0x00,
0x01,0x00,0x00,0xFF,0x00,0x00,0x40,0x42,0x42,0x42,0x7F,0x42,0x42,0x42,0x40,0x00,// "性",1

0x40,0x30,0xEF,0x24,0x24,0x40,0x20,0x10,0x0C,0x23,0xCC,0x10,0x20,0x40,0x40,0x00,
0x01,0x01,0x7F,0x21,0x11,0x00,0x01,0x09,0x11,0x21,0xD1,0x0D,0x03,0x00,0x00,0x00,// "铃",2

0x04,0x14,0xD4,0x54,0x54,0x54,0x54,0xDF,0x54,0x54,0x54,0x54,0xD4,0x14,0x04,0x00,
0x80,0x60,0x1F,0x02,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0x00,// "声",3

0x40,0x40,0x42,0xCC,0x00,0x50,0x4E,0xC8,0x48,0x7F,0xC8,0x48,0x48,0x40,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x50,0x4C,0x43,0x40,0x40,0x4F,0x50,0x50,0x5C,0x40,0x00,// "选",4

0x10,0x10,0xFF,0x10,0x00,0x82,0x86,0x4A,0x52,0xA2,0x52,0x4A,0x86,0x80,0x80,0x00,
0x42,0x82,0x7F,0x01,0x00,0x10,0x12,0x12,0x12,0xFF,0x12,0x12,0x12,0x10,0x00,0x00,// "择",5
		};
    const uint8_t FMainMenu_EnterAbout[] = {
0x00,0x00,0x10,0x11,0x16,0x10,0x10,0xF0,0x10,0x10,0x14,0x13,0x10,0x00,0x00,0x00,
0x81,0x81,0x41,0x41,0x21,0x11,0x0D,0x03,0x0D,0x11,0x21,0x41,0x41,0x81,0x81,0x00,// "关",0

0x40,0x40,0x42,0x42,0x42,0x42,0x42,0xFE,0x42,0x42,0x42,0x42,0x42,0x40,0x40,0x00,
0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// "于",1

0x00,0x80,0x60,0xF8,0x07,0x40,0x30,0x0F,0xF8,0x88,0x88,0x88,0x88,0x08,0x08,0x00,
0x01,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x08,0x08,0x08,0x08,0x08,0x00,0x00,// "作",2

0x20,0x20,0x24,0x24,0x24,0x24,0xBF,0x64,0x24,0x34,0x28,0x24,0x22,0x20,0x20,0x00,
0x10,0x08,0x04,0x02,0xFF,0x49,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,0x00,// "者",3
		};
		int i;
			
    //OledClear();
    
    if (currentSelection == MainMenu_EnterDozeCounting) {
        // 反色显示
        for(i = 0; i < 6; i++) {
            OledShowFont16X16R(ConvertRowToPixelCN(i), ConvertLineToPixel(0), FMainMenu_EnterDozeCounting + i*32);
        }
    } else {
        for(i = 0; i < 6; i++) {
            OledShowFont16X16(ConvertRowToPixelCN(i), ConvertLineToPixel(0), FMainMenu_EnterDozeCounting + i*32);
        }
    }

		
    if (currentSelection == MainMenu_EnterDozeTimeSetting) {
        // 反色显示
        for(i = 0; i < 6; i++) {
            OledShowFont16X16R(ConvertRowToPixelCN(i), ConvertLineToPixel(1), FMainMenu_EnterDozeTimeSetting + i*32);
        }
    } else {
        for(i = 0; i < 6; i++) {
            OledShowFont16X16(ConvertRowToPixelCN(i), ConvertLineToPixel(1), FMainMenu_EnterDozeTimeSetting + i*32);
        }
    }

     if (currentSelection == MainMenu_EnterCustomRing) {
        // 反色显示
        for(i = 0; i < 6; i++) {
            OledShowFont16X16R(ConvertRowToPixelCN(i), ConvertLineToPixel(2), FMainMenu_EnterCustomRing + i*32);
        }
    } else {
        for(i = 0; i < 6; i++) {
            OledShowFont16X16(ConvertRowToPixelCN(i), ConvertLineToPixel(2), FMainMenu_EnterCustomRing + i*32);
        }
    }

    if (currentSelection == MainMenu_EnterAbout) {
        // 反色显示
        for(i = 0; i < 4; i++) {
            OledShowFont16X16R(ConvertRowToPixelCN(i+1), ConvertLineToPixel(3), FMainMenu_EnterAbout + i*32);
        }
    } else {
        for(i = 0; i < 4; i++) {
            OledShowFont16X16(ConvertRowToPixelCN(i+1), ConvertLineToPixel(3), FMainMenu_EnterAbout + i*32);
        }
    }
}

// 显示打盹计时界面
void DisplayDozeCounting(void) {
    // 第二行显示时间
    uint8_t timeBuffer[16]; 
    
    const uint8_t colon[] = {0x00,0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00,0x00};
    const uint8_t dot[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0};
		
    // 第三行显示按钮
    const uint8_t FCounting_StartDoze[] = {
0x10,0x10,0x10,0xFF,0x10,0x90,0x04,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x00,
0x04,0x44,0x82,0x7F,0x01,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,// "打",0

0x00,0xFC,0x24,0x24,0xFC,0x00,0x08,0xE8,0x08,0x08,0xFF,0x08,0x08,0xE8,0x08,0x00,
0x00,0x3F,0x11,0x11,0x3F,0x00,0x00,0x03,0x02,0x02,0x3F,0x42,0x42,0x47,0x70,0x00,// "盹",1
		};
    const uint8_t FCounting_StopDoze[] = {
0x80,0x60,0xF8,0x07,0x00,0x04,0x74,0x54,0x55,0x56,0x54,0x54,0x74,0x04,0x00,0x00,
0x00,0x00,0xFF,0x00,0x03,0x01,0x05,0x45,0x85,0x7D,0x05,0x05,0x05,0x01,0x03,0x00,// "停",0

0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,// "止",1

		};
    const uint8_t FCounting_PauseDoze[] = {
0x82,0x9A,0x96,0x93,0xFA,0x52,0x52,0x80,0x7E,0x12,0x12,0x12,0xF1,0x11,0x10,0x00,
0x00,0x01,0x00,0xFE,0x93,0x92,0x93,0x92,0x92,0x92,0x92,0xFE,0x03,0x00,0x00,0x00,// "暂",0

0x80,0x60,0xF8,0x07,0x00,0x04,0x74,0x54,0x55,0x56,0x54,0x54,0x74,0x04,0x00,0x00,
0x00,0x00,0xFF,0x00,0x03,0x01,0x05,0x45,0x85,0x7D,0x05,0x05,0x05,0x01,0x03,0x00,// "停",1
		};
    const uint8_t FCounting_ResumeDoze[] = {
0x20,0x30,0xAC,0x63,0x10,0x00,0xFE,0x48,0x50,0x40,0xFF,0x40,0x50,0x48,0x00,0x00,
0x22,0x67,0x22,0x12,0x12,0x00,0x7F,0x44,0x42,0x41,0x7F,0x41,0x42,0x44,0x40,0x00,// "继",0

0x20,0x30,0xAC,0x63,0x20,0x18,0x20,0x24,0xA4,0x24,0x3F,0xA4,0x24,0xA4,0x60,0x00,
0x22,0x67,0x22,0x12,0x12,0x12,0x88,0x8A,0x4C,0x29,0x18,0x0F,0x18,0x28,0xC8,0x00,// "续",1
		};
    const uint8_t FCounting_Exit[] = {
0x40,0x40,0x42,0xCC,0x00,0x00,0xFF,0x49,0x49,0xC9,0x49,0x49,0x7F,0x80,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x40,0x5F,0x48,0x44,0x40,0x41,0x42,0x45,0x58,0x40,0x00,// "退",0

0x00,0x00,0x7C,0x40,0x40,0x40,0x40,0xFF,0x40,0x40,0x40,0x40,0xFC,0x00,0x00,0x00,
0x00,0x7C,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0xFC,0x00,0x00,// "出",1
		};
		int i;

		#define COUNTING_OFFSET (32)
    OledShowFont8X16(0 + COUNTING_OFFSET, 1, &Decimal[countdownMinutes / 10 * 16]);
    OledShowFont8X16(8 + COUNTING_OFFSET, 1, &Decimal[countdownMinutes % 10 * 16]);
    OledShowFont8X16(16 + COUNTING_OFFSET, 1, colon);
    OledShowFont8X16(24 + COUNTING_OFFSET, 1, &Decimal[countdownSeconds / 10 * 16]);
    OledShowFont8X16(32 + COUNTING_OFFSET, 1, &Decimal[countdownSeconds % 10 * 16]);
    OledShowFont8X16(40 + COUNTING_OFFSET, 1, dot);
    OledShowFont8X16(48 + COUNTING_OFFSET, 1, &Decimal[countdownMilliseconds / 10 * 16]);
    OledShowFont8X16(56 + COUNTING_OFFSET, 1, &Decimal[countdownMilliseconds % 10 * 16]);

    if (currentSelection == DozeCounting_StartDozeButton) {
				// 反色显示
				for(i = 0; i < 2; i++) {
					OledShowFont16X16R(ConvertRowToPixelCN(i), ConvertLineToPixel(2), (dozeButtonState == Button_StartDoze ? FCounting_StartDoze : FCounting_StopDoze) + i*32);
				}
		} else {
				for(i = 0; i < 2; i++) {
					OledShowFont16X16(ConvertRowToPixelCN(i), ConvertLineToPixel(2), (dozeButtonState == Button_StartDoze ? FCounting_StartDoze : FCounting_StopDoze)  + i*32);
				}
    }
		
    if (currentSelection == DozeCounting_PauseDozeButton) {
				// 反色显示
				for(i = 0; i < 2; i++) {
					OledShowFont16X16R(ConvertRowToPixelCN(i + 3), ConvertLineToPixel(2), (pauseButtonState == Button_PauseDoze ? FCounting_PauseDoze : FCounting_ResumeDoze) + i*32);
				}
		} else {
				for(i = 0; i < 2; i++) {
					OledShowFont16X16(ConvertRowToPixelCN(i + 3), ConvertLineToPixel(2), (pauseButtonState == Button_PauseDoze ? FCounting_PauseDoze : FCounting_ResumeDoze)  + i*32);
				}
    }
		
    if (currentSelection == DozeCounting_ExitButton) {
				// 反色显示
				for(i = 0; i < 2; i++) {
					OledShowFont16X16R(ConvertRowToPixelCN(i + 6), ConvertLineToPixel(2), FCounting_Exit + i*32);
				}
		} else {
				for(i = 0; i < 2; i++) {
					OledShowFont16X16(ConvertRowToPixelCN(i + 6), ConvertLineToPixel(2), FCounting_Exit + i*32);
				}
    }
}

// 显示打盹时间设置界面
void DisplayDozeTimeSetting(void) {
    // 第二行显示时间
    const uint8_t colon[] = {0x00,0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00,0x00};
    const uint8_t dot[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0};

    // 第三行显示完成按钮
    const uint8_t FDozeTimeSetting_Done[] = {
0x10,0x0C,0x04,0x24,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x24,0x04,0x14,0x0C,0x00,
0x00,0x81,0x81,0x41,0x31,0x0F,0x01,0x01,0x01,0x7F,0x81,0x81,0x81,0xF1,0x00,0x00,// "完",0

0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0x08,0x08,0xFF,0x08,0x09,0x0A,0xC8,0x08,0x00,
0x80,0x60,0x1F,0x00,0x10,0x20,0x1F,0x80,0x40,0x21,0x16,0x18,0x26,0x41,0xF8,0x00,// "成",1
		};
		int i;

      if (currentSelection == DozeTimeSetting_Minutes) {
				// 反色
				OledShowFont8X16R(0 + COUNTING_OFFSET, 1, &Decimal[dozeMinutes / 10 * 16]);
				OledShowFont8X16R(8 + COUNTING_OFFSET, 1, &Decimal[dozeMinutes % 10 * 16]);
      } else {
				OledShowFont8X16(0 + COUNTING_OFFSET, 1, &Decimal[dozeMinutes / 10 * 16]);
				OledShowFont8X16(8 + COUNTING_OFFSET, 1, &Decimal[dozeMinutes % 10 * 16]);
      }
    
     if (currentSelection == DozeTimeSetting_Seconds) {
				// 反色
				OledShowFont8X16R(24 + COUNTING_OFFSET, 1, &Decimal[dozeSeconds / 10 * 16]);
				OledShowFont8X16R(32 + COUNTING_OFFSET, 1, &Decimal[dozeSeconds % 10 * 16]);
      } else {
				OledShowFont8X16(24 + COUNTING_OFFSET, 1, &Decimal[dozeSeconds / 10 * 16]);
				OledShowFont8X16(32 + COUNTING_OFFSET, 1, &Decimal[dozeSeconds % 10 * 16]);
     }

    
      if (currentSelection == DozeTimeSetting_Milliseconds) {
				// 反色
				OledShowFont8X16R(48 + COUNTING_OFFSET, 1, &Decimal[dozeMilliseconds / 10 * 16]);
				OledShowFont8X16R(56 + COUNTING_OFFSET, 1, &Decimal[dozeMilliseconds % 10 * 16]);
      } else {
				OledShowFont8X16(48 + COUNTING_OFFSET, 1, &Decimal[dozeMilliseconds / 10 * 16]);
				OledShowFont8X16(56 + COUNTING_OFFSET, 1, &Decimal[dozeMilliseconds % 10 * 16]);
      }
     OledShowFont8X16(16 + COUNTING_OFFSET, 1, colon);
     OledShowFont8X16(40 + COUNTING_OFFSET, 1, dot);
			
      if (currentSelection == DozeTimeSetting_Done) {
				// 反色显示
				for(i = 0; i < 2; i++) {
					OledShowFont16X16R(ConvertRowToPixelCN(i + 3), ConvertLineToPixel(2), FDozeTimeSetting_Done + i*32);
				}
		} else {
				for(i = 0; i < 2; i++) {
					OledShowFont16X16(ConvertRowToPixelCN(i + 3), ConvertLineToPixel(2), FDozeTimeSetting_Done + i*32);
				}
      }
}

// 显示个性铃声选择界面
void DisplayCustomRing(void) {
    const uint8_t FCustomRing_Sound1[] = {
0x40,0x30,0xEF,0x24,0x24,0x40,0x20,0x10,0x0C,0x23,0xCC,0x10,0x20,0x40,0x40,0x00,
0x01,0x01,0x7F,0x21,0x11,0x00,0x01,0x09,0x11,0x21,0xD1,0x0D,0x03,0x00,0x00,0x00,// "铃",0

0x04,0x14,0xD4,0x54,0x54,0x54,0x54,0xDF,0x54,0x54,0x54,0x54,0xD4,0x14,0x04,0x00,
0x80,0x60,0x1F,0x02,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0x00,// "声",1

0x00,0x20,0x10,0x10,0xF0,0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x0F,0x08,0x08,0x00,// "1",2
		};
    const uint8_t FCustomRing_Sound2[] = {
0x40,0x30,0xEF,0x24,0x24,0x40,0x20,0x10,0x0C,0x23,0xCC,0x10,0x20,0x40,0x40,0x00,
0x01,0x01,0x7F,0x21,0x11,0x00,0x01,0x09,0x11,0x21,0xD1,0x0D,0x03,0x00,0x00,0x00,// "铃",0

0x04,0x14,0xD4,0x54,0x54,0x54,0x54,0xDF,0x54,0x54,0x54,0x54,0xD4,0x14,0x04,0x00,
0x80,0x60,0x1F,0x02,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0x00,// "声",1

0x00,0x10,0x10,0x10,0x90,0xF0,0x00,0x00,0x00,0x0C,0x0C,0x0A,0x09,0x08,0x08,0x00,// "2",2
		};
    const uint8_t FCustomRing_Sound3[] = {
0x40,0x30,0xEF,0x24,0x24,0x40,0x20,0x10,0x0C,0x23,0xCC,0x10,0x20,0x40,0x40,0x00,
0x01,0x01,0x7F,0x21,0x11,0x00,0x01,0x09,0x11,0x21,0xD1,0x0D,0x03,0x00,0x00,0x00,// "铃",0

0x04,0x14,0xD4,0x54,0x54,0x54,0x54,0xDF,0x54,0x54,0x54,0x54,0xD4,0x14,0x04,0x00,
0x80,0x60,0x1F,0x02,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0x00,// "声",1

0x00,0x10,0x90,0x90,0x90,0x70,0x00,0x00,0x00,0x08,0x08,0x08,0x09,0x0F,0x06,0x00,// "3",2

		};
    const uint8_t FCustomRing_Sound4[] = {
0x40,0x30,0xEF,0x24,0x24,0x40,0x20,0x10,0x0C,0x23,0xCC,0x10,0x20,0x40,0x40,0x00,
0x01,0x01,0x7F,0x21,0x11,0x00,0x01,0x09,0x11,0x21,0xD1,0x0D,0x03,0x00,0x00,0x00,// "铃",0

0x04,0x14,0xD4,0x54,0x54,0x54,0x54,0xDF,0x54,0x54,0x54,0x54,0xD4,0x14,0x04,0x00,
0x80,0x60,0x1F,0x02,0x02,0x02,0x02,0x03,0x02,0x02,0x02,0x02,0x03,0x00,0x00,0x00,// "声",1

0x00,0x00,0xC0,0x20,0x10,0xF0,0x00,0x00,0x02,0x03,0x02,0x02,0x02,0x0F,0x02,0x00,// "4",2
		};
		int i;

      if (currentSelection == CustomRing_Sound1) {
				// 反色显示
				for(i = 0; i < 2; i++) {
					OledShowFont16X16R(ConvertRowToPixelCN(i), ConvertLineToPixel(0), FCustomRing_Sound1 + i*32);
				}
				OledShowFont8X16R(ConvertRowToPixelCN(2), ConvertLineToPixel(0), FCustomRing_Sound1 + 2*32);
		} else {
				for(i = 0; i < 2; i++) {
					OledShowFont16X16(ConvertRowToPixelCN(i), ConvertLineToPixel(0), FCustomRing_Sound1 + i*32);
				}
				OledShowFont8X16(ConvertRowToPixelCN(2), ConvertLineToPixel(0), FCustomRing_Sound1 + 2*32);
      }

      if (currentSelection == CustomRing_Sound2) {
				// 反色显示
				for(i = 0; i < 2; i++) {
					OledShowFont16X16R(ConvertRowToPixelCN(i), ConvertLineToPixel(1), FCustomRing_Sound2 + i*32);
				}
				OledShowFont8X16R(ConvertRowToPixelCN(2), ConvertLineToPixel(1), FCustomRing_Sound2 + 2*32);
		} else {
				for(i = 0; i < 2; i++) {
					OledShowFont16X16(ConvertRowToPixelCN(i), ConvertLineToPixel(1), FCustomRing_Sound2 + i*32);
				}
				OledShowFont8X16(ConvertRowToPixelCN(2), ConvertLineToPixel(1), FCustomRing_Sound2 + 2*32);
      }
      if (currentSelection == CustomRing_Sound3) {
				// 反色显示
				for(i = 0; i < 2; i++) {
					OledShowFont16X16R(ConvertRowToPixelCN(i), ConvertLineToPixel(2), FCustomRing_Sound3 + i*32);
				}
				OledShowFont8X16R(ConvertRowToPixelCN(2), ConvertLineToPixel(2), FCustomRing_Sound3 + 2*32);
		} else {
				for(i = 0; i < 2; i++) {
					OledShowFont16X16(ConvertRowToPixelCN(i), ConvertLineToPixel(2), FCustomRing_Sound3 + i*32);
				}
				OledShowFont8X16(ConvertRowToPixelCN(2), ConvertLineToPixel(2), FCustomRing_Sound3 + 2*32);
      }
      if (currentSelection == CustomRing_Sound4) {
				// 反色显示
				for(i = 0; i < 2; i++) {
					OledShowFont16X16R(ConvertRowToPixelCN(i), ConvertLineToPixel(3), FCustomRing_Sound4 + i*32);
				}
				OledShowFont8X16R(ConvertRowToPixelCN(2), ConvertLineToPixel(3), FCustomRing_Sound4 + 2*32);
		} else {
				for(i = 0; i < 2; i++) {
					OledShowFont16X16(ConvertRowToPixelCN(i), ConvertLineToPixel(3), FCustomRing_Sound4 + i*32);
				}
				OledShowFont8X16(ConvertRowToPixelCN(2), ConvertLineToPixel(3), FCustomRing_Sound4 + 2*32);
      }
}

// 显示关于作者界面
void DisplayAbout(void) {
    const uint8_t FAbout_JinChenye[] = {
0x80,0x80,0x40,0x20,0x50,0x48,0x44,0xC3,0x44,0x48,0x50,0x20,0x40,0x80,0x80,0x00,
0x40,0x40,0x42,0x4A,0x72,0x42,0x42,0x7F,0x42,0x42,0x62,0x5A,0x42,0x40,0x40,0x00,// "金",0

0x00,0x00,0xC0,0x5F,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x5F,0x40,0x40,0x00,0x00,
0x80,0x60,0x1F,0x04,0xFD,0x85,0x45,0x0D,0x15,0x25,0x25,0x55,0x4D,0x84,0x84,0x00,// "晨",1

0x80,0x70,0x00,0xFF,0x10,0x28,0x10,0xFC,0x03,0x40,0x20,0x7F,0x88,0x86,0xE0,0x00,
0x80,0x60,0x18,0x07,0x08,0x30,0x04,0x05,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x00,// "烨",2
		};
    const uint8_t FAbout_WangShaoyan[] = {
0x00,0x02,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0x02,0x00,0x00,
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,// "王",0

0x20,0x30,0xAC,0x63,0x30,0x00,0x82,0x62,0x1E,0x02,0x02,0x42,0x82,0x7E,0x00,0x00,
0x22,0x67,0x22,0x12,0x12,0x01,0x00,0xFE,0x42,0x42,0x42,0x42,0x42,0xFE,0x00,0x00,// "绍",1

0x00,0x80,0x88,0x46,0x40,0x20,0x10,0x0F,0x10,0x10,0x28,0x24,0x42,0x80,0x00,0x00,
0x80,0x80,0x48,0x46,0x20,0x10,0x08,0x07,0x08,0x10,0x28,0x46,0x40,0x80,0x80,0x00,// "炎",2
		};
    const uint8_t FAbout_WangBoren[] = {
0x00,0x02,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0x02,0x00,0x00,
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,// "王",0

0x20,0x20,0xFF,0x20,0x24,0xF4,0x54,0x54,0x54,0xFF,0x54,0x55,0x56,0xF4,0x04,0x00,
0x00,0x00,0xFF,0x00,0x08,0x0B,0x19,0x69,0x09,0x0B,0x49,0x89,0x7D,0x0B,0x08,0x00,// "博",1

0x00,0x80,0x60,0xF8,0x07,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
0x01,0x00,0x00,0xFF,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,// "仁",2
		};
    const uint8_t FAbout_WuTianhao[] = {
0x00,0x00,0x80,0x9E,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x9E,0x80,0x00,0x00,0x00,
0x84,0x84,0x44,0x44,0x24,0x14,0x0C,0x07,0x0C,0x14,0x24,0x44,0x44,0x84,0x84,0x00,// "吴",0

0x40,0x40,0x42,0x42,0x42,0x42,0x42,0xFE,0x42,0x42,0x42,0x42,0x42,0x40,0x40,0x00,
0x80,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x03,0x0C,0x10,0x20,0x40,0x80,0x80,0x00,// "天",1

0x00,0xF8,0x0C,0x0B,0x08,0xF8,0xA0,0x9E,0x88,0x88,0xFF,0x88,0x88,0x88,0x80,0x00,
0x00,0x7F,0x21,0x21,0x21,0x7F,0x00,0xFC,0x44,0x44,0x44,0x44,0x44,0xFC,0x00,0x00,// "皓",2
		};
		const uint8_t eraser[] = {0,0,0,0,0,0,0,0};
		int i;
			
    OledClear();
    
    // 动画效果
    for (i = 0; i < 4; i++) {
        if (aboutAnimationX[i] + 3 * 16 > 128 || aboutAnimationX[i] < 0) {
            aboutAnimationDirection[i] *= -1;
        }
        aboutAnimationX[i] += aboutAnimationDirection[i];
    }
		
		for (i = 0; i < 3; i++) {
				OledShowFont1X16(aboutAnimationX[0] - aboutAnimationDirection[0] + ConvertRowToPixelCN(i), ConvertLineToPixel(0), eraser);
				OledShowFont16X16(aboutAnimationX[0] + ConvertRowToPixelCN(i), ConvertLineToPixel(0), FAbout_JinChenye + i*32);
				OledShowFont1X16(aboutAnimationX[1] - aboutAnimationDirection[1] + ConvertRowToPixelCN(i), ConvertLineToPixel(1), eraser);
				OledShowFont16X16(aboutAnimationX[1] + ConvertRowToPixelCN(i), ConvertLineToPixel(1), FAbout_WangShaoyan + i*32);
				OledShowFont1X16(aboutAnimationX[2] - aboutAnimationDirection[2] + ConvertRowToPixelCN(i), ConvertLineToPixel(2), eraser);
				OledShowFont16X16(aboutAnimationX[2] + ConvertRowToPixelCN(i), ConvertLineToPixel(2), FAbout_WangBoren + i*32);
				OledShowFont1X16(aboutAnimationX[3] - aboutAnimationDirection[3] + ConvertRowToPixelCN(i), ConvertLineToPixel(3), eraser);
				OledShowFont16X16(aboutAnimationX[3] + ConvertRowToPixelCN(i), ConvertLineToPixel(3), FAbout_WuTianhao + i*32);
		}
		
		delayms(50);

}

// 处理按键按下
void HandleButtonPress(void) {

    
    if (GPIO_ReadInputDataBit(KEY1_PORT, KEY1_Pin) == 0) {
        //BTN_LEFT
        if(isDozeTimeSettingMode) {
            switch (dozeTimeSettingSelection)
            {
            case DozeTimeSetting_Minutes:
                if(dozeMinutes > 0) dozeMinutes--;
								else dozeMinutes = 59;
                break;
            case DozeTimeSetting_Seconds:
                if(dozeSeconds > 0) dozeSeconds--;
								else dozeSeconds = 59;
                break;
            case DozeTimeSetting_Milliseconds:
                if(dozeMilliseconds > 0) dozeMilliseconds--;
								else dozeSeconds = 99;
                break;
            
            default:
                break;
            }
						while(GetKey() == KEY1);
            return;
        }
        
        switch (currentPage) {
            case MainMenu:
                currentSelection = (currentSelection - 1 + 4) % 4;
                break;
            case DozeCounting:
							  currentSelection -= 1;
								if (currentSelection == DozeCounting_PauseDozeButton && dozeButtonState == Button_StartDoze) {
									// 打盹钟还没开始，不允许选中暂停按钮
									currentSelection -= 1;
								}
								if (currentSelection < DozeCounting_StartDozeButton) {
									currentSelection = DozeCounting_ExitButton;
									// 超出边界循环回去
								}
                break;
            case DozeTimeSetting:
                currentSelection -= 1;
								if (currentSelection < DozeTimeSetting_Minutes) {
									// 超出边界循环回去
									currentSelection = DozeTimeSetting_Done;
								}
                break;
            case CustomRing:
                currentSelection -= 1;
								if (currentSelection < CustomRing_Sound1) {
									// 超出边界循环回去
									currentSelection = CustomRing_Sound4;
								}
                switch (currentSelection) {
                    case CustomRing_Sound1:
                        CurrentRingSheet = RingSheet1;
                        CurrentRingSheetTime = RingSheet1Time;
												NowSheetTick = 0;
												isRinging = 1;
                        break;
                    case CustomRing_Sound2:
                        CurrentRingSheet = RingSheet2;
                        CurrentRingSheetTime = RingSheet2Time;
												NowSheetTick = 0;
												isRinging = 1;
                        break;
                    case CustomRing_Sound3:
                        CurrentRingSheet = RingSheet3;
                        CurrentRingSheetTime = RingSheet3Time;
												NowSheetTick = 0;
												isRinging = 1;
                        break;
                    case CustomRing_Sound4:
                        CurrentRingSheet = RingSheet4;
                        CurrentRingSheetTime = RingSheet4Time;
												NowSheetTick = 0;
												isRinging = 1;
                        break;
                }
                break;
            case About:
                // 任意键返回主菜单
                currentPage = MainMenu;
                currentSelection = MainMenu_EnterDozeCounting;
                break;
        }
    } else if (GPIO_ReadInputDataBit(KEY2_PORT, KEY2_Pin) == 0) {
        //BTN_RIGHT
         if(isDozeTimeSettingMode) {
             switch (dozeTimeSettingSelection)
            {
            case DozeTimeSetting_Minutes:
                if(dozeMinutes < 59) dozeMinutes++;
								else dozeMinutes = 0;
                break;
            case DozeTimeSetting_Seconds:
                if(dozeSeconds < 59) dozeSeconds++;
								else dozeMinutes = 0;
                break;
            case DozeTimeSetting_Milliseconds:
                if(dozeMilliseconds < 99) dozeMilliseconds++;
								else dozeMinutes = 0;
                break;
            
            default:
                break;
            }
						while(GetKey() == KEY2);
            return;
        }

        switch (currentPage) {
            case MainMenu:
                currentSelection = (currentSelection + 1) % 4;
                break;
            case DozeCounting:
							  currentSelection += 1;
								if (currentSelection == DozeCounting_PauseDozeButton && dozeButtonState == Button_StartDoze) {
									// 打盹钟还没开始，不允许选中暂停按钮
									currentSelection += 1;
								}
								if (currentSelection > DozeCounting_ExitButton) {
									currentSelection = DozeCounting_StartDozeButton;
									// 超出边界循环回去
								}
                break;
            case DozeTimeSetting:
                currentSelection += 1;
								if (currentSelection > DozeTimeSetting_Done) {
									// 超出边界循环回去
									currentSelection = DozeTimeSetting_Minutes;
								}
                break;
            case CustomRing:
                currentSelection += 1;
								if (currentSelection > CustomRing_Sound4) {
									// 超出边界循环回去
									currentSelection = CustomRing_Sound1;
								}
                switch (currentSelection) {
                    case CustomRing_Sound1:
                        CurrentRingSheet = RingSheet1;
                        CurrentRingSheetTime = RingSheet1Time;
												NowSheetTick = 0;
												isRinging = 1;
                        break;
                    case CustomRing_Sound2:
                        CurrentRingSheet = RingSheet2;
                        CurrentRingSheetTime = RingSheet2Time;
												NowSheetTick = 0;
												isRinging = 1;
                        break;
                    case CustomRing_Sound3:
                        CurrentRingSheet = RingSheet3;
                        CurrentRingSheetTime = RingSheet3Time;
												NowSheetTick = 0;
												isRinging = 1;
                        break;
                    case CustomRing_Sound4:
                        CurrentRingSheet = RingSheet4;
                        CurrentRingSheetTime = RingSheet4Time;
												NowSheetTick = 0;
												isRinging = 1;
                        break;
                }
                break;
            case About:
                // 任意键返回主菜单
                currentPage = MainMenu;
                currentSelection = MainMenu_EnterDozeCounting;
                break;
        }
				while(GetKey() == KEY2);
    } else if (GPIO_ReadInputDataBit(KEY3_PORT, KEY3_Pin) == 0) {
        // BTN_ENTER
          if(isDozeTimeSettingMode) {
               isDozeTimeSettingMode = 0;
								while(GetKey() == KEY3);
               return;
          }
        switch (currentPage) {
            case MainMenu:
                switch (currentSelection) {
                    case MainMenu_EnterDozeCounting:
                        currentPage = DozeCounting;
                        currentSelection = DozeCounting_StartDozeButton;
                        countdownMinutes = dozeMinutes;
                        countdownSeconds = dozeSeconds;
                        countdownMilliseconds = dozeMilliseconds;
                        break;
                    case MainMenu_EnterDozeTimeSetting:
                        currentPage = DozeTimeSetting;
                        currentSelection = DozeTimeSetting_Minutes;
                        break;
                    case MainMenu_EnterCustomRing:
                        currentPage = CustomRing;
                        currentSelection = CustomRing_Sound1;
                        break;
                    case MainMenu_EnterAbout:
                        currentPage = About;
                        currentSelection = About_JinChenye;
                        CurrentRingSheet = RingSheet5;
                        CurrentRingSheetTime = RingSheet5Time;
												NowSheetTick = 0;
												isRinging = 1;
                        break;
                }
								while(GetKey() == KEY3);
                break;
            case DozeCounting:
                switch (currentSelection) {
                    case DozeCounting_StartDozeButton:
                        if (dozeButtonState == Button_StartDoze) {
                            isCountingDown = 1;
                            dozeButtonState = Button_StopDoze;
                            pauseButtonState = Button_PauseDoze;
                        } else {
                            isCountingDown = 0;
                            dozeButtonState = Button_StartDoze;
                            pauseButtonState = Button_PauseDoze;
                            countdownMinutes = dozeMinutes;
                            countdownSeconds = dozeSeconds;
                            countdownMilliseconds = dozeMilliseconds;
                            isPaused = 0;
                            currentSelection = DozeCounting_StartDozeButton; 
                        }
                        break;
                    case DozeCounting_PauseDozeButton:
                        if (pauseButtonState == Button_PauseDoze) {
                            isPaused = 1;
                            pauseButtonState = Button_ResumeDoze;
                        } else {
                            isPaused = 0;
                            pauseButtonState = Button_PauseDoze;
                        }
                        break;
                    case DozeCounting_ExitButton:
                        currentPage = MainMenu;
                        currentSelection = MainMenu_EnterDozeCounting;
                        isCountingDown = 0;
                        dozeButtonState = Button_StartDoze;
                        pauseButtonState = Button_PauseDoze;
                         isPaused = 0;
												isRinging = 0;
												isPlaying = 0;
                        break;
                }
								while(GetKey() == KEY3);
                break;
            case DozeTimeSetting:
                switch (currentSelection) {
                    case DozeTimeSetting_Minutes:
                    case DozeTimeSetting_Seconds:
                    case DozeTimeSetting_Milliseconds:
                        isDozeTimeSettingMode = 1;
                        dozeTimeSettingSelection = currentSelection;
                        break;
                    case DozeTimeSetting_Done:
                        currentPage = MainMenu;
                        currentSelection = MainMenu_EnterDozeCounting;
                        break;
                }
								while(GetKey() == KEY3);
                break;
            case CustomRing:
                switch (currentSelection) {
                    case CustomRing_Sound1:
                        CurrentRingSheet = RingSheet1;
                        CurrentRingSheetTime = RingSheet1Time;
												NowSheetTick = 0;
												isRinging = 0;
                        break;
                    case CustomRing_Sound2:
                        CurrentRingSheet = RingSheet2;
                        CurrentRingSheetTime = RingSheet2Time;
												NowSheetTick = 0;
												isRinging = 0;
                        break;
                    case CustomRing_Sound3:
                        CurrentRingSheet = RingSheet3;
                        CurrentRingSheetTime = RingSheet3Time;
												NowSheetTick = 0;
												isRinging = 0;
                        break;
                    case CustomRing_Sound4:
                        CurrentRingSheet = RingSheet4;
                        CurrentRingSheetTime = RingSheet4Time;
												NowSheetTick = 0;
												isRinging = 0;
                        break;
                }
                currentPage = MainMenu;
                currentSelection = MainMenu_EnterDozeCounting;
								while(GetKey() == KEY3);
								isRinging = 0;
								isPlaying = 0;
                break;
            case About:
                // 任意键返回主菜单
                currentPage = MainMenu;
                currentSelection = MainMenu_EnterDozeCounting;
								while(GetKey() == KEY3);
								isRinging = 0;
								isPlaying = 0;
                break;
        }
    }
		
		while(GetKey() != KEY_NO);
}

void BeepTickingOn(int16_t freq){
    SetFreq(freq); 
    isPlaying = 1;
}

void BeepTickingOff(){
    isPlaying = 0;
}

// 播放铃声
void PlayRing(void) {
	  static int32_t count = 0, Last_Clock = 0, Last_SheetTick = -1;
		if (!isRinging) return;
	
    if (CurrentRingSheet[NowSheetTick] != -1 && Last_SheetTick != NowSheetTick) {
        BeepTickingOn(CurrentRingSheet[NowSheetTick]);
				Last_SheetTick = NowSheetTick;
				count = CurrentRingSheetTime[NowSheetTick] / 10;
				Last_Clock = Global_Clock;
    }
		//delayms(100);
		if (Global_Clock - Last_Clock >= count) {
				BeepTickingOff();
				delayms(15);
				++NowSheetTick;
				count = 0;
		}
		if (CurrentRingSheet[NowSheetTick] == -1) {
				BeepTickingOff();
				isRinging = 0;
		}
}

void Beep(uint16_t freq, uint16_t t){
    isPlaying = 1;
    SetFreq(freq);  // C
    delayms(t);
    isPlaying = 0;
    delayms(10);
}

















