/**
  ******************************************************************************
  * @file    GPIO_Driver.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides GPIO functions.
  ******************************************************************************
  */

#include "stm32f746xx.h"
#include "GPIO_Driver.h"

/**
* @brief Initialises the pin.
* @param PortNumber: the number of the used port.
* @param PinNumber: which pin is it on the board.
* @param PinMode: analog or digital.
* @param PullUpPullDown: Pull-up and Pull-down resistors.
* @retval None
*/
void GPIOInitPin(U8 PortNumber, U8 PinNumber, U8 PinMode, U8 PullUpPullDown)
{
	GPIO_TypeDef* PortNumberArray[7] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG};

	PortNumberArray[PortNumber]->MODER &= ~(0x3 << (2 * PinNumber));
	PortNumberArray[PortNumber]->MODER |=  (PinMode << (2 * PinNumber));
	
	PortNumberArray[PortNumber]->PUPDR &= ~(0x3 << (2 * PinNumber));
	PortNumberArray[PortNumber]->PUPDR |=  (PullUpPullDown << (2 * PinNumber));
}

/**
* @brief Sets the value of a given pin.
* @param PortNumber: the number of the used port.
* @param PinNumber: which pin is it on the board.
* @param PinValue: value to set for the pin.
* @retval None
*/
void GPIOSetPinValue(U8 PortNumber, U8 PinNumber, U8 PinValue)
{
	GPIO_TypeDef* PortNumberArray[7] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG};
	
	switch(PinValue)
	{
		case 0:
			PortNumberArray[PortNumber]->BSRR |= (1 << (PinNumber + 16));
		break;
		
		case 1:
			PortNumberArray[PortNumber]->BSRR |= (1 << PinNumber );
		break;
		
		default:
		break;	
	}
}

/**
* @brief Function to interact with a given pin/port for peripherals. 
* Currently toggles the LED on/off. Checks whether it is currently on to turn it off.
* @param PortNumber: the number of the used port.
* @param PinNumber: which pin is it on the board.
* @retval 0: pin off
* @retval 1: pin on
*/
U8 TogglePin (U8 PortNumber, U8 PinNumber)
{
	GPIO_TypeDef* PortNumberArray[11] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI};
	U8 PINState;

	if ((((PortNumberArray[PortNumber]->ODR) & (0x1 << PinNumber)) >> PinNumber) == 1)
	{
		PortNumberArray[PortNumber]->BSRR |= (1 << (PinNumber + 16));
		PINState = 0;
	}
	else
	{
		PortNumberArray[PortNumber]->BSRR |= (1 << PinNumber );
		PINState = 1;
	}
	return PINState;
}
