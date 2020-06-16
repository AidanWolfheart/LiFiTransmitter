/**
  ******************************************************************************
  * @file    ADC_Driver.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides ADC functions.
  ******************************************************************************
  */

#include "stm32f746xx.h"
#include "Types.h"

/**
* @brief  Initializes the ADC.
* @param  None
* @retval None
*/
void ADC3Init(void)
{
		// configure resolution to 8 bits
		//ADC3->CR1 |=  ADC_CR1_RES_1;              // Commented because we use the default config of 12 bits
		
		//Configure Alignment & Single Conversion
		ADC3->CR2 &=~ (0 << 11); // Align right
		ADC3->CR2 &=~ (0 << 1);  // Single Conversion mode
		
		// ADON enable
		ADC3 ->CR2 |= ADC_CR2_ADON;		// turn on conversion
}

/**
* @brief  Function to convert analog-digital readings.
* @param  None
* @return Reading of the result from data register
*/
U16 ADC_Convert(void)
{
		U16 ADC_Result;
	
		// Start conversion
		ADC3->CR2 |= (1 << 30);	
		while(((ADC3->SR >> 1) & 0x0001) == 0)	// waiting until the conversion is done
		{
		}
		
		ADC_Result = ADC3->DR;
		return ADC_Result;
}
