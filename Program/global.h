#ifndef GLOBAL_H
#define GLOBAL_H

#define NULL 0

// ����ö��
typedef enum {
    MainMenu,
    DozeCounting,
    DozeTimeSetting,
    CustomRing,
    About
} Page;

// ��ť״̬ö�� (��Ե����пɱ䰴ť)
typedef enum {
    Button_StartDoze,
    Button_StopDoze,
    Button_PauseDoze,
    Button_ResumeDoze,
    Button_Exit
} DozeCountingButtonState;

// ������ѡ�а�ťö��
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

//�ⲿ������������ʱ������
extern void delayms(uint32_t msnum);
// ȫ�ֱ���
extern Page currentPage;
extern Selection currentSelection;
extern DozeCountingButtonState dozeButtonState;
extern DozeCountingButtonState pauseButtonState;

extern uint8_t dozeMinutes;
extern uint8_t dozeSeconds; // Ĭ��5��
extern uint8_t dozeMilliseconds;

extern uint8_t countdownMinutes;
extern uint8_t countdownSeconds;
extern uint8_t countdownMilliseconds;

extern uint8_t isCountingDown;
extern uint8_t isPaused;
extern uint8_t isDozeTimeSettingMode;
extern uint8_t dozeTimeSettingSelection;
#endif