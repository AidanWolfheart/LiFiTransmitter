/**
  ******************************************************************************
  * @file    UART6_Driver.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides functions that drives the UART.
  ******************************************************************************
  */

#include "stm32f746xx.h"
#include "Types.h"
#include "GPIO_Driver.h"

extern U8 FileArr[MAX_FILE_SIZE];
extern U32 FileArrIndex;
extern U8 UARTRxFlag;
extern U8 TxChar;

/**
* @brief  Initializes UART2, 9600 baud rate, PORTA.2 as TX, PORTA.3 as RX, 
* Enables clock, cnables TX, enables UART2.
* @param  None
* @retval None
*/
void UART6_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
	
	GPIOInitPin(PORTC, 6, AF_MODE, NO_PULL);
	GPIOInitPin(PORTC, 7, AF_MODE, NO_PULL);
	
	GPIOC->AFR[0] &= ~(0xF << 24);
	GPIOC->AFR[0] |=  (0x8 << 24);
	
	GPIOC->AFR[0] &= ~(0xF << 28);
	GPIOC->AFR[0] |=  (0x8 << 28);
	
	USART6->CR1 |= USART_CR1_UE;
	USART6->CR1 |= USART_CR1_RE;
	USART6->CR1 |= USART_CR1_TE;
	USART6->CR1 |= USART_CR1_RXNEIE;
	
	USART6->CR2 &= ~(0x3 << 12);
	USART6->CR2 |= (0x2 << 12);
	
	USART6->GTPR |= (0x1 >> 0);
	     
	USART6->BRR = 0x8B; 
}

/**
* @brief Transfer character to UART.
* @param TxChar: character to transfer.
* @retval None
*/
void UART6_TX(U8 TxChar)
{
		USART6->TDR = TxChar;
		while (((USART6->ISR & USART_ISR_TC) >> USART_ISR_TC_Pos) == 0)
		{	
		}
		USART2->ISR &= ~(USART_ISR_TC);
}

/**
* @brief Receive the character from UART.
* @param None
* @return The received character
*/
U8 UART6_RX(void)
{
		U8 TxChar;
		while(((USART6->ISR & USART_ISR_RXNE) >> USART_ISR_RXNE_Pos) == 0)
		{
		}
		TxChar = USART6->RDR;
		
		return TxChar;
}

/**
* @brief Receives the stream of characters as a file in bytes array.
* @param None 
* @retval None
*/	
void ReceiveFile(void)
{
	if (UARTRxFlag == 1)
	{
		UARTRxFlag = 0;
		FileArr[FileArrIndex] = TxChar;
		FileArrIndex++;
	}
}
