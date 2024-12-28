/*
*********************************************************************************************************
*	���� : stm32f4xxx_it.c
*	˵�� : ����жϷ�����
* ���� : Lijh
*****************************************************************************************************
*/
//����ͷ�ļ�
#include "key.h"
#include "led.h"
#include "timer.h"
#include "beep.h"
#include "global.h"

/*
*************************************
* Key1(PI8)�İ����жϴ������
**************************************
*/
uint32_t t = 1;
extern uint8_t isPlaying;
void EXTI9_5_IRQHandler(void)
{ 
    if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
}
// �ⲿ�жϷ������ - �����ж�
/*
*************************************
* Tim2���жϴ������
**************************************
*/
extern uint16_t NowSheetTick;
extern uint8_t isRinging;
extern uint32_t Global_Clock;
// ��ʱ���жϷ������ - 10ms�жϣ�����ˢ�½���Ͷ���
void TIM2_IRQHandler(void) {
		++Global_Clock;
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
         if(isCountingDown && !isPaused) {
                if(countdownMilliseconds > 0) {
                    countdownMilliseconds--;
                } else {
                    if(countdownSeconds > 0) {
                        countdownSeconds--;
                        countdownMilliseconds = 99;
                    } else {
                        if(countdownMinutes > 0) {
                            countdownMinutes--;
                            countdownSeconds = 59;
                            countdownMilliseconds = 99;
                        } else {
                            // ʱ�䵽
                            isCountingDown = 0;
													
														countdownMinutes = 5; // ʱ�䵽���ټ�����Ӵ�������
														countdownSeconds = 0;
														countdownMilliseconds = 0;
													
                            dozeButtonState = Button_StartDoze;
                            pauseButtonState = Button_PauseDoze;
                            isPaused = 0;
                            currentSelection = DozeCounting_StartDozeButton;
                            NowSheetTick = 0;
														isRinging = 1;
                        }
                    }
                }
         }
        //HandleButtonPress();
		  TIM_ClearFlag(TIM2, TIM_IT_Update); //����жϱ�־
    }
}

/*************************************
* Tim3���жϴ������
**************************************
*/
uint16_t otime=1000, frqcount=0;
void TIM3_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == 1)  //����жϱ�־�Ƿ�Ϊ1
	{
			if (isPlaying && isRinging) {
				++frqcount;
				if(frqcount>otime){
					frqcount=0;
					BeepToggle();
				}
			}
		  TIM_ClearFlag(TIM3, TIM_IT_Update); //����жϱ�־
	}	
}