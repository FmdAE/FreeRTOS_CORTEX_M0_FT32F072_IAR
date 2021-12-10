/**
  *********************************************************************************
  * @file    	    InitTask.c
  * @author  	    FMD AE
  * @brief   		InitTask program body 	
  * @version 	    V1.0.0           
  * @data		    2021-09-27
  *********************************************************************************
  * @attention
  * COPYRIGHT (C) 2021 Fremont Micro Devices (SZ) Corporation All rights reserved.
  *    This software is provided by the copyright holders and contributors,and the
  *software is believed to be accurate and reliable. However, Fremont Micro Devices
  *(SZ) Corporation assumes no responsibility for the consequences of use of such
  *software or for any infringement of patents of other rights of third parties,
  *which may result from its use. No license is granted by implication or otherwise
  *under any patent rights of Fremont Micro Devices (SZ) Corporation.
  *  ******************************************************************************
  */
/* Includes ----------------------------------------------------------------------*/
#include "InitTask.h"

/* Private Constant --------------------------------------------------------------*/
/* Public Constant ---------------------------------------------------------------*/
/* Private typedef ---------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------*/
static xTaskHandle pInitTaskHandle = NULL;

/* Public variables --------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
void InitTask(void *param);
static void SystemApplicationDeviceInit(void);
static void DeleteInitTask(void);

/* Public function ------ --------------------------------------------------------*/
/**********************************************************************************
  * @brief  CreateInitTask program.
  * @param  None
  * @note
  * @retval None
  *********************************************************************************
*/  
void CreateInitTask(void)
{
	xTaskCreate(InitTask, (portCHAR const* )"InitTask", TASK_STACK_INIT, NULL, TASK_PRIO_INIT, &pInitTaskHandle);
}

/* Private function ------ -------------------------------------------------------*/
/**********************************************************************************
  * @brief  DeleteInitTask program.
  * @param  None
  * @note
  * @retval None
  *********************************************************************************
*/ 
static void DeleteInitTask(void)
{
	vTaskDelete(pInitTaskHandle);
}

/**********************************************************************************
  * @brief  SystemApplicationDeviceInit program.
  * @param  None
  * @note
  * @retval None
  *********************************************************************************
*/
static void SystemApplicationDeviceInit(void)
{
	__disable_irq();         
	Led_Init();
	Key_Init();
	Usart_Init();
	ADC_Config();
//	Iwdg_Init();
	TIM_PWM_Init();
 	TSC_ParaDef  tTSC_ParaStruct;			
	tTSC_ParaStruct.MeantimeMaxKeyNum = 2;
	tTSC_ParaStruct.BaselineDownSpeed = 50;
	tTSC_ParaStruct.BaselineEqualSpeed = 50;
	tTSC_ParaStruct.BaselineUpSpeed = 50;
	tTSC_ParaStruct.Multiple = 80;
	tTSC_ParaStruct.SignalNoiseRatio = 30;
	tTSC_ParaStruct.SingleFilter = 4;
	tTSC_ParaStruct.StrongFilter = 4;
	TSC_Init(&tTSC_ParaStruct);						            /* configure TSC parameters*/	
	TSC_EnableKey11(10);
	TSC_EnableKey12(10);       
	__enable_irq();
}
/**********************************************************************************
  * @brief  InitTask program.
  * @param  *param
  * @note
  * @retval None
  *********************************************************************************
*/
void InitTask(void *param)
{
	SystemApplicationDeviceInit();
	CreateHighProTask();
	CreateLowProTask();
	DeleteInitTask();
	
}
/************************* (C) COPYRIGHT FMD *****END OF FILE*********************/