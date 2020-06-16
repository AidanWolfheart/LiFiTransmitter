/**
  ******************************************************************************
  * @file    main.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides main program functions.
  ******************************************************************************
  */

#include "stm32f746xx.h"
#include <stdio.h>
#include "GPIO_Driver.h"
#include "Tx_Control.h"
#include "Tim2_Delay.h"
#include "UART_Driver.h"

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32746g_discovery_sdram.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"
#include "GLCD_Conf.h"
#include "GLCD_Driver.h"

#define FILE_RX_TIME_OUT (APB2BUS_CLOCK/1000)*250  //250ms


extern GLCD_FONT     GLCD_Font_16x24;
extern U8 RefreshDisplayFlag;
extern Button_Type Button1;
extern Button_Type Button2;
extern Button_Type Button3;
extern Button_Type Button4;
extern Button_Type Button5;
extern Button_Type Button6;

U8 UARTRxFlag = 0;
U8 TxChar;
TOUCH_STATE  tsc_state;
U8 FileArr[MAX_FILE_SIZE] = {0};
U32 FileArrIndex = 0;

	
/**
* @brief  Main program - contains superloop for Receiver side.
* @param  None
* @retval int
*/
int main (void)
{	
	U8 ButtonFlags;
	U32 FileSendIndex = 0;
	static U8 FileTransferState = 0;
	
	
	
	//enable clock for port C and G 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;	
	
	//Set PG6 As Output Pin
	GPIOInitPin(PORTG, 6, OUTPUT_MODE, NO_PULL);

	DelayInit();
	UART6_Init();
	
	GPIOG->BSRR |= (1 <<6);  // Init Pin ON
	
	NVIC_EnableIRQ(USART6_IRQn); //interrupt for usart6
	
	//Initialize GLCD
	GLCD_Initialize (); 
  GLCD_SetBackgroundColor (GLCD_COLOR_CYAN);
  GLCD_ClearScreen (); 
	GLCD_SetForegroundColor (GLCD_COLOR_MAROON);
  GLCD_SetFont (&GLCD_Font_16x24);
	
	ButtonDimensionsInit();

	Touch_Initialize();  
	
	RefreshDisplay();

//===========================================================================================	
	while(1)
	{
		Touch_GetState(&tsc_state);
		if (tsc_state.pressed)
		{
			ButtonFlags = GetTouchPositionFlags();
		}
		
		switch (ButtonFlags)
		{
			case BUTTON_1:
			if(UARTRxFlag == 1)  // This flag is 1 only when UART had received a char, Set in the interrupt routine
			{
				Send_Byte(TxChar);
				UARTRxFlag = 0;
			}
			if(RefreshDisplayFlag == 1)  //this flag in set only when the screen in pressed
			{
				SelectButton(0); //Clear screen, draw the initial screen, highlight the button
			}
			break;
			
			case BUTTON_2:
			if(RefreshDisplayFlag == 1)
			{
				FileTransferState = INIT_STATE;
			}
			
			switch(FileTransferState)
			{
				case INIT_STATE:
				if(RefreshDisplayFlag == 1)
				{
					SelectButton(1);
					//Order the Rx to enter Rx mode	
					SendFileTransferCmd();
				}
				FileTransferState = WAIT_FILE_TRANSFER_START;			
				break;
				
				case WAIT_FILE_TRANSFER_START:  //Between computer and Tx using UART
				if (UARTRxFlag == 1)   //If a char is received from computer
				{
					UARTRxFlag = 0;
					FileArr[FileArrIndex] = TxChar;
					FileArrIndex++;
					FileTransferState = RX_FILE_STATE;
				}
				break;
				
				case RX_FILE_STATE:             //Receivie file from computer via UART
				//Receive the rest of the file from computer by UART, 
				ReceiveFile();
				if (TIM2->CNT > FILE_RX_TIME_OUT)//if tx didnt recieve any chr for ~0.5 sec it will indicate the recieving is done.
				{
					FileTransferState = TX_FILE_STATE;
				}
				break;
				
				case TX_FILE_STATE:						//Transmmit file to receiver by light
				//Send the buffered file to Rx by light withe the max possible speed
				for(FileSendIndex = 0; FileSendIndex < FileArrIndex; FileSendIndex++)
				{
					Send_Byte(FileArr[FileSendIndex]);
					TIM2Delay(50);
				}
					FileArrIndex = 0;
					ButtonFlags = 1; // go   back to pc keyboard
					RefreshDisplayFlag = 1;
				break;	
				
				default:
				break;
			}
			break;
			
			case BUTTON_3:
			if(RefreshDisplayFlag == 1)
			{
				Send_Byte(COMMAND_1);
			  SelectButton(2);
			}
			break;

			case BUTTON_4:

			if(RefreshDisplayFlag == 1)
			{
				Send_Byte(COMMAND_2);
			  SelectButton(3);
			}		
			break;

			case BUTTON_5:

			if(RefreshDisplayFlag == 1)
			{
				Send_Byte(COMMAND_3);
			  SelectButton(4);
			}		
			break;

			case BUTTON_6:

			if(RefreshDisplayFlag == 1)
			{
				Send_Byte(COMMAND_4);
			  SelectButton(5);
			}	
			break;	

			default:
			break;
		}
	}
}

/**
* @brief  Handles the interrupt to read the coming character
* @param  None
* @retval None
*/
void USART6_IRQHandler (void)
{
	TxChar = USART6->RDR;                 //UART6 Rx Interrupt
	UARTRxFlag = 1;
	TIM2Reset();
}

