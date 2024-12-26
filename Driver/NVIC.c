/*
************************************************
* 文件: NVIC.c
* 功能: NVIC中断配置
* 作者：Lijh
************************************************
*/
//引用头文件
#include "NVIC.h"

//NVIC初始化
void NvicCfg(void)
{ 
		NVIC_InitTypeDef  NVIC_InitStructure;
	  /* Configure the NVIC Group */  
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	  //按键 Key1(PI8)的NVIC配置
    //NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;         //中断通道
	  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //主优先级
	  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //子优先级
		//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //中断使能 
	  //NVIC_Init(&NVIC_InitStructure);                            //完成初始化
	
	  //TIM2的NVIC配置
	  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;          
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;     
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
    NVIC_Init(&NVIC_InitStructure);  
	
		//TIM3的NVIC配置
	  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;          
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
    NVIC_Init(&NVIC_InitStructure);  
	
}


