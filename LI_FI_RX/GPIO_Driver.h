/**
  ******************************************************************************
  * @file    GPIO_Driver.h 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   Header file for GPIO driver.
  ******************************************************************************
  */

#include "Types.h"

void GPIOInitPin(U8 PortNumber, U8 PinNumber, U8 PinMode, U8 PullUpPullDown);
void GPIOSetPinValue(U8 PortNumber, U8 PinNumber, U8 PinValue);
U8 TogglePin (U8 PortNumber, U8 PinNumber);
