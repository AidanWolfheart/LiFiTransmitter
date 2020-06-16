/**
  ******************************************************************************
  * @file    Tim2_Delay.h 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   Header file for TIM2 delay.
  ******************************************************************************
  */

#include "Types.h"

void DelayInit (void);
void TIM2Delay(U16 DelayInMs);
void TIM2Delayus(U32 DelayInus);
void TIM2Reset(void);
	