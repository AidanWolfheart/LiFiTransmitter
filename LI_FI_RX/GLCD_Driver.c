/**
  ******************************************************************************
  * @file    GLCD_Driver.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides GLCD functions.
  ******************************************************************************
  */

#include "Types.h"
#include "Board_GLCD.h"
#include "GPIO_Driver.h"
#include "GLCD_Driver.h"
#include "UART_Driver.h"

/** @defgroup GLCD_Private_Variables
* @{
*/
static U16 CursorPos = 10;
static U16 CursorLine = 10;
static U8 ClrScreenFlag = 0;
static U8 ConsoleFlag = 0;
U8 RxState;
U8 FileTransFlag;
/**
* @}
*/ 
	
/**
* @brief Writes a character to either GLCD or streams it to UART, 
* based on received state command.
* @param Char: the received character. 
* @retval None
*/	
void GLCDWriteChar (U8 Char)
{
	//10 lines with increment 25 pixel
	//27 Position in each line 17 pixel 
	U8 i, TrueAsciiFlag = 0;
	U8 PinState = 0;
	//Command to switch to file transfer
	static U8 FTCmd[19] = {'F', 'I', 'L', 'E', ' ', 'T', 'R', 'A', 'N', 'S', 'F', 'E', 'R', ' ', 'S', 'T', 'A', 'R', 'T'};
	static U8 FTBuffer[19] = {0};
	U8 static FTBufferIndex = 0;
	U8 IDCounter = 0;
	
	switch(RxState)
	{		
		case WriteKBAndCMD:	
			
		for (FTBufferIndex = 0; FTBufferIndex < 18; FTBufferIndex++)
		{
			FTBuffer[FTBufferIndex] = FTBuffer[FTBufferIndex + 1];
		}
		
		FTBuffer[18] = Char;
		
		if (Char == 'S')
		{
			i++;
		}
		FTBufferIndex = 0;
		while((FTCmd[FTBufferIndex] == FTBuffer[FTBufferIndex]) && (FTBufferIndex < 19))
		{
			IDCounter++;
			FTBufferIndex++;
		}
			if (IDCounter == 19)
			{
				RxState = FILE_TRANSFER;
			}
			else
			{
				RxState = WriteKBAndCMD;
			}
			
		//Differrent received commands will trigger different receiver behaviour
		//Commands are special sequences of characters, they coexist with typical
		//ASCII characters
		switch(Char)
		{
		case COMMAND_1:
			PinState = TogglePin(PORTG,6);
			ConsoleWriteState(0x1, PinState);
		break;
		
		case COMMAND_2:
			PinState = TogglePin(PORTB, 4);
			ConsoleWriteState(0x2, PinState);
		break;
		
		case COMMAND_3:
			PinState = TogglePin(PORTG, 7);
			ConsoleWriteState(0x3, PinState);
		break;
			
		case COMMAND_4:
			PinState = TogglePin(PORTA, 15);
			ConsoleWriteState(0x4, PinState);
		break;
			
		case ENTER_BUTTON:
			NextLineCurrentClearScreen();
		break;
			
		case BACK_SPACE_BUTTON:
			BackSpace();
		break;
		
		default:
		if(ClrScreenFlag == 1)
		{
			InitScreen();
			ClrScreenFlag = 0;
		}
		else if(ConsoleFlag == 1)
		{
			NextLineCurrentClearScreen();
			ConsoleFlag = 0;
		}
		
		GLCD_DrawChar(CursorPos, CursorLine, Char);
		IncerementPosition(0x1);
		}
		break;	
		
		case FILE_TRANSFER:
		UART6_TX(Char);	 //Send byte to computer
		FileTransFlag = 1;
		break;
		
		default:
		break;
	}
}

//	U8 AsciiArr[63] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
//										 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
//										 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '};
//	i = 0;
//	while (i < 63)
//	{
//		if(Char == AsciiArr[i])
//		{
//			TrueAsciiFlag = 1;
//			break;
//		}
//		i++;
//	}	
//	if(TrueAsciiFlag == 1)
//	{

//	}

/**
* @brief Initialises the GLCD.
* @param  None
* @retval None
*/
void InitScreen (void)
{
	U16 LinePosition;
	U8 LineCounter;
	GLCD_ClearScreen();
	
	GLCD_DrawRectangle(5,5,470,262);
	GLCD_DrawRectangle(7,7,466,258);
	
	LinePosition = 34;
	for(LineCounter = 0;LineCounter < 10;LineCounter ++)
	{
	GLCD_DrawHLine(10,LinePosition,463);
	LinePosition += 25;
	}
}

/**
* @brief Clears the GLCD and sets cursor to line 1.
* @param  None
* @retval None
*/
void NextLineNextClearScreen(void)
{
	CursorPos = 10;
	CursorLine += 25;
	if(CursorLine >250)
	{
		CursorLine = 10;
		ClrScreenFlag = 1;
	}
}

/**
* @brief Increments a new line in the current screen.
* @param  None
* @retval None
*/
void NextLineCurrentClearScreen(void)
{
	CursorPos = 10;
	CursorLine += 25;
	if(CursorLine >250)
	{
		CursorLine = 10;
		InitScreen();
	}
}

/**
* @brief Increments the cursor per each character.  
* @param Increment: the amount to increment for.
* @retval None
*/
void IncerementPosition(U8 Increment)
{
	CursorPos += (16 * Increment);
	if (CursorPos > 452)
	{
		NextLineNextClearScreen();
	}	
}

/**
* @brief Write current task behaviour on the console. 
* @param  PeripheralNo: 
* @param  PeripheralState:
* @retval None
*/
void ConsoleWriteState(U8 PeripheralNo, U8 PeripheralState)
{
	const char* StringsArray[4] = {(const char*)"Peripheral 1: ",(const char*)"Peripheral 2: ",(const char*)"Peripheral 3: ",(const char*)"Peripheral 4: "};
	
	if (!(CursorPos == 10))
	{
		NextLineCurrentClearScreen();
	}
	GLCD_DrawString(CursorPos, CursorLine, StringsArray[PeripheralNo - 1]);
	IncerementPosition(0x17);
	
	if (PeripheralState == 0)
	{
		GLCD_DrawString(CursorPos , CursorLine, "OFF");
		IncerementPosition(0x3);
	}                            
	else                         
	{                            
		GLCD_DrawString(CursorPos , CursorLine, "ON");
		IncerementPosition(0x2);
	}
	ConsoleFlag = 1;
}

/**
* @brief Allows backspace functionality to remove characters.
* @param  None
* @retval None
*/
void BackSpace(void)
{
	if (CursorPos == 10)
	{	
		if(!(CursorLine == 10))
		{
			CursorLine -= 25;
			CursorPos  = 452;
			GLCD_DrawChar(CursorPos, CursorLine, ' ');
		}
	}
	else
	{
		CursorPos -= 16;
		GLCD_DrawChar(CursorPos, CursorLine, ' ');
	}
}
