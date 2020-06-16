/**
  ******************************************************************************
  * @file    TIM2_Driver.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides Timer functions.
  ******************************************************************************
  */

#include "stm32f746xx.h"
#include "Types.h"

/** @defgroup TIM2_Private_Defines
* @{
*/ 
#define APB2BUS_CLOCK 16000000
/**
* @}
*/ 

/**
* @brief Initialises the TIM2.
* @param  None
* @retval None
*/
void DelayInit (void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->CR1 |= (1 << 0);
}

/**
* @brief Sets the delay for TIM2 in milliseconds.
* @param DelayInMs: Specified delay in milliseconds. 
* @retval None
*/
void TIM2Delay(U16 DelayInMs)
{
	U32 TimerTicks;
	U32 TIMFrequencyDivided;
		
	TIMFrequencyDivided = 	APB2BUS_CLOCK / 1000;
		
	TimerTicks = DelayInMs * TIMFrequencyDivided;
	
	TIM2->CNT = 0;
	while (TIM2->CNT < TimerTicks)
	{
	}
}

/**
* @brief Sets the delay for TIM2 in microseconds.
* @param  DelayInus: Specified delayin microseconds.
* @retval None
*/
void TIM2Delayus(U32 DelayInus)
{
	U32 TimerTicks;
	U32 TIMFrequencyDivided;
		
	TIMFrequencyDivided = 	APB2BUS_CLOCK / 1000000;
		
	TimerTicks = DelayInus * TIMFrequencyDivided;
	
	TIM2->CNT = 0;
	while (TIM2->CNT < TimerTicks)
	{
	}
}

/**
* @brief Resets the TIM2.
* @param  None
* @retval None
*/
void TIM2Reset(void)
{
	TIM2->CNT = 0;
}
