/**
  ******************************************************************************
  * @file    Tx_Control.h
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   Header file for TX control.
  ******************************************************************************
  */

#include "Types.h"

void SendStartWord (void);
void Send_Byte (U8 TX_BYTE);
void SendFileTransferCmd (void);
