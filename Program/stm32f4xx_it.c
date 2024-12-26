/*
*********************************************************************************************************
*	名称 : stm32f4xxx_it.c
*	说明 : 存放中断服务函数
* 作者 : Lijh
*****************************************************************************************************
*/
//引用头文件
#include "key.h"
#include "led.h"
#include "timer.h"
#include "global.h"

/*
*************************************
* Key1(PI8)的按键中断处理程序
**************************************
*/
uint16_t t = 1;
void EXTI9_5_IRQHandler(void)
{ 
    if (EXTI_GetITStatus(EXTI_Line8) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
}
// 外部中断服务程序 - 按键中断
/*
*************************************
* Tim2的中断处理程序
**************************************
*/
// 定时器中断服务程序 - 10ms中断，用于刷新界面和动画
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
                            // 时间到
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
		  TIM_ClearFlag(TIM2, TIM_IT_Update); //清除中断标志
    }
}

/*************************************
* Tim3的中断处理程序
**************************************
*/
void TIM3_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == 1)  //检查中断标志是否为1
	{
		  //LedToggle(LED2);   //亮灭切换
		  TIM_ClearFlag(TIM3, TIM_IT_Update); //清除中断标志
	}	
}

