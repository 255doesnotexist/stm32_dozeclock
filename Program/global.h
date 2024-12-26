#ifndef GLOBAL_H
#define GLOBAL_H

#define NULL 0

// 界面枚举
typedef enum {
    MainMenu,
    DozeCounting,
    DozeTimeSetting,
    CustomRing,
    About
} Page;

// 按钮状态枚举 (针对第三行可变按钮)
typedef enum {
    Button_StartDoze,
    Button_StopDoze,
    Button_PauseDoze,
    Button_ResumeDoze,
    Button_Exit
} DozeCountingButtonState;

// 界面内选中按钮枚举
typedef enum {
    MainMenu_EnterDozeCounting,
    MainMenu_EnterDozeTimeSetting,
    MainMenu_EnterCustomRing,
    MainMenu_EnterAbout,

    DozeCounting_StartDozeButton,
    DozeCounting_PauseDozeButton,
    DozeCounting_ExitButton,

    DozeTimeSetting_Minutes,
    DozeTimeSetting_Seconds,
    DozeTimeSetting_Milliseconds,
    DozeTimeSetting_Done,

    CustomRing_Sound1,
    CustomRing_Sound2,
    CustomRing_Sound3,
    CustomRing_Sound4,

    About_JinChenye,
    About_WangShaoyan,
    About_WangBoren,
    About_WuTianhao
} Selection;

//外部函数声明（延时函数）
extern void delayms(uint32_t msnum);
// 全局变量
extern Page currentPage;
extern Selection currentSelection;
extern DozeCountingButtonState dozeButtonState;
extern DozeCountingButtonState pauseButtonState;

extern uint8_t dozeMinutes;
extern uint8_t dozeSeconds; // 默认5秒
extern uint8_t dozeMilliseconds;

extern uint8_t countdownMinutes;
extern uint8_t countdownSeconds;
extern uint8_t countdownMilliseconds;

extern uint8_t isCountingDown;
extern uint8_t isPaused;
extern uint8_t isDozeTimeSettingMode;
extern uint8_t dozeTimeSettingSelection;
#endif