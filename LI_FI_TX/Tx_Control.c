/**
  ******************************************************************************
  * @file    Tx_Control.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides functions for transmission control.
  ******************************************************************************
  */

#include "stm32f746xx.h"
#include "Tim2_Delay.h"

/**
* @brief Sends a start word 0101 to let receiver side know that data is about to be transferred.  
* @param None
* @retval None
*/	
void SendStartWord (void)
{
			GPIOG->BSRR |= (1 << 22); //Off
			TIM2Delay(1);
			GPIOG->BSRR |= (1 <<6);   //On
			TIM2Delay(1);	
			GPIOG->BSRR |= (1 << 22); //Off
			TIM2Delay(1);
			GPIOG->BSRR |= (1 << 6);  //On
			TIM2Delay(1);
}

/**
* @brief Sends a sequence of bits to the receiver.
* @param  TX_BYTE: Byte to transfer.
* @retval None
*/	
void Send_Byte (U8 TX_BYTE)
{
	U8 i, BIT;
	SendStartWord();

	for (i = 0 ; i < 8 ; i++)
	{
		BIT = GET_BIT(TX_BYTE , i);

		if (BIT == 1)
		{
			GPIOG->BSRR |= (1 <<6);
			TIM2Delay(1);
		}
		else if (BIT == 0)
		{
			GPIOG->BSRR |= (1 <<22);
			TIM2Delay(1);
		}
	}
	GPIOG->BSRR |= (1 <<6); //On
}

/**
* @brief Sends an array of characters to let receiver side know a file is about to be transferred.
* @param None 
* @retval None
*/	
void SendFileTransferCmd (void)
{
	int i = 0;
	U8 FTCmd[19] = {'F', 'I', 'L', 'E', ' ', 'T', 'R', 'A', 'N', 'S', 'F', 'E', 'R', ' ', 'S', 'T', 'A', 'R', 'T'};
	for (i = 0; i <19; i++)
	{
		Send_Byte(FTCmd[i]);
		TIM2Delay(50);
	}
}