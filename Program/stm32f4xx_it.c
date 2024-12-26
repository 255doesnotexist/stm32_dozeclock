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
#include "global.h"

/*
*************************************
* Key1(PI8)�İ����жϴ������
**************************************
*/
uint16_t t = 1;
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
// ��ʱ���жϷ������ - 10ms�жϣ�����ˢ�½���Ͷ���
void TIM2_IRQHandler(void) {
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
                            dozeButtonState = Button_StartDoze;
                            pauseButtonState = Button_PauseDoze;
                            countdownMinutes = dozeMinutes;
                            countdownSeconds = dozeSeconds;
                            countdownMilliseconds = dozeMilliseconds;
                            isPaused = 0;
                            currentSelection = DozeCounting_StartDozeButton;
                            PlayRing();
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
void TIM3_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == 1)  //����жϱ�־�Ƿ�Ϊ1
	{
		  //LedToggle(LED2);   //�����л�
		  TIM_ClearFlag(TIM3, TIM_IT_Update); //����жϱ�־
	}	
}

