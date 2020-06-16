/**
  ******************************************************************************
  * @file    main.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides main program functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f746xx.h"
#include <stdio.h>
#include "GPIO_Driver.h"
#include "ADC_Driver.h"
#include "LI_FI_Driver.h"
#include "TIM2_Delay.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32746g_discovery_sdram.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"
#include "GLCD_Conf.h"
#include "GLCD_Driver.h"
#include "UART_Driver.h"


extern GLCD_FONT     GLCD_Font_16x24;
extern U8 RxState;
extern U8 FileTransFlag;


/**
* @brief  Main program - contains superloop for Receiver side
* @param  None
* @retval int
*/
int main (void)
{

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Local Variable Declarations>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	U16 NEW_ADC_RESULT, OLD_ADC_RESULT = 1;
	U8  RECEIVED_BYTE, ReceivedByte;
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Initialization>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//enable clock for port A
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//enable clock for port C
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	//enable clock for port B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	//enable clock for port G
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	//enable RCC_APB2ENR_ADC3EN
	RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
	
	//Set PG6 As Output Pin [D2]
	GPIOInitPin(PORTG, 6, OUTPUT_MODE, NO_PULL);
	//Set PB4 As Output Pin [D3]
	GPIOInitPin(PORTB, 4, OUTPUT_MODE, NO_PULL);
	//Set PG7 As Output Pin [D4]
	GPIOInitPin(PORTG, 7, OUTPUT_MODE, NO_PULL);
	//Set PA13 As Output Pin [D9]
	GPIOInitPin(PORTA, 15, OUTPUT_MODE, NO_PULL);
	
	//Set PA0 mode as analoge
	GPIOInitPin(PORTA, 0, ANALOG_MODE, NO_PULL);
	
	//Initialize ADC3
	ADC3Init();
	
	//Initialize Delay depending on TIM2
	DelayInit();
	
	//Initialize UART
	UART6_Init();
	
	//Initialize GLCD
	GLCD_Initialize ();
  GLCD_SetBackgroundColor (GLCD_COLOR_CYAN);
  GLCD_ClearScreen (); 
	GLCD_SetForegroundColor (GLCD_COLOR_MAROON);
  GLCD_SetFont (&GLCD_Font_16x24);
	
	InitScreen();
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Main Loop>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	while(1)
	{			
		NEW_ADC_RESULT = ADC_Convert();
		
		if ((FileTransFlag == 1) && (TIM2->CNT > FILE_RX_TIME_OUT))
		{
			RxState = WriteKBAndCMD;
			FileTransFlag = 0;
		}		
		
		// check if drop in light occurs
		if ((NEW_ADC_RESULT > OLD_ADC_RESULT) && ((NEW_ADC_RESULT - OLD_ADC_RESULT) > LIGHT_DROP_THRESHOLD))
		{

			ReceivedByte = CheckByteRX(); // checkbyterx returns the recieved character or 0 if it has no start word 
			if (ReceivedByte != 0)
			{
				TIM2Reset();
				GLCDWriteChar(ReceivedByte);// Process the received byte accordingly toggle leds or show on screen or recieve file.
			}
		}
		OLD_ADC_RESULT = NEW_ADC_RESULT;
	}
}
