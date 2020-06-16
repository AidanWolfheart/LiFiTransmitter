/**
  ******************************************************************************
  * @file    GLCD_Driver.h 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   Header file for GLCD driver.
  ******************************************************************************
  */

#include "Types.h"

void GLCDWriteChar (U8 Char);
void InitScreen (void);
void ConsoleWriteState(U8 PeripheralNo, U8 PeripheralState);
void NextLineNextClearScreen(void);
void NextLineCurrentClearScreen(void);
void IncerementPosition(U8 Increment);
void BackSpace(void);
