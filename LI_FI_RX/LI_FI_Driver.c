/**
  ******************************************************************************
  * @file    LI_FI_Driver.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides LIFI functions.
  ******************************************************************************
  */

#include "stm32f746xx.h"
#include "Types.h"
#include "ADC_Driver.h"
#include "TIM2_Delay.h"

/** @defgroup LIFI_Private_Defines
* @{
*/ 
#define TransDrop 60
#define GUARD_FACTOR 0
/**
* @}
*/ 

/** @defgroup LIFI_Private_FunctionPrototypes
* @{
*/ 
U8 RoundNumber(float x);
U8 InvertBool(U8 CurrentBit);
/**
* @}
*/ 

/**
* @brief Processes the received byte and returns an character or 0.
* Looks at the bytes after the start word and gets the representation of it
* as a character.
* @param  None
* @retvar 0: Start word does not match 0101 pattern
* @retvar n: The character if start word 0101 matches
*/
U8 CheckByteRX (void)
{
	U8  RxChar = 0;
	U16 ADC_Results[256];
	U16 ResultIndex = 0;
	U8  BitCounter[12] = {0};
	U8  BitCounterIndex = 0;
	U8  RxByteArr[12] = {0};
	U16 ConsDiff = 0;
	U8  TransFlag = 0;    //1 if we are going from On to Off
	float  AvgCount = 1.5;
	float  NoOfBits[12] = {1.2};
	U8 i,j,k,CurrentBit;
	//=====================================================================
	U16 MinReading, MaxReading, AvgReading;
	U8  ReadingsCounter[12] = {0};
	U8  ReadingsCounterIndex = 0;
	U8  AvgReadingsPerBit;
	//=====================================================================	
	for (ResultIndex = 0; ResultIndex < 256; ResultIndex++)
	{
		ADC_Results[ResultIndex] = ADC_Convert();
		TIM2Delayus(115);
	}

//====================================================================================================	
	ADC_Results[0] = ADC_Results[1];
	
	MinReading = 65500;
	MaxReading = 0;
	
	for (ResultIndex = 0; ResultIndex < 256; ResultIndex++)
	{
		if (ADC_Results[ResultIndex] < MinReading)
		{
			MinReading = ADC_Results[ResultIndex];
		}
		if (ADC_Results[ResultIndex] > MaxReading)
		{
			MaxReading = ADC_Results[ResultIndex];
		}
	}
	
	AvgReading = (MinReading + MaxReading)/2;
	
	for (ResultIndex = 0; ResultIndex < 256; ResultIndex++)
	{	
		if ((ADC_Results[ResultIndex] >= (AvgReading + GUARD_FACTOR)) && ((ADC_Results[ResultIndex + 1] < (AvgReading - GUARD_FACTOR))))
		{
			TransFlag = 1;
		}
		else if ((ADC_Results[ResultIndex] < (AvgReading - GUARD_FACTOR)) && ((ADC_Results[ResultIndex + 1] >= (AvgReading + GUARD_FACTOR))))
		{
			TransFlag = 1;
		}
		
		if (TransFlag == 1)
		{
			ReadingsCounterIndex++;
			ReadingsCounter[ReadingsCounterIndex]++;     //Move to the next group and increase it by 1
			TransFlag = 0;
		}
		else
		{
			ReadingsCounter[ReadingsCounterIndex]++;     //Increase The current Group by 1
		}
	}
	
	AvgReadingsPerBit = (float)(ReadingsCounter[0] + ReadingsCounter[1] + ReadingsCounter[2])/ 3.0;   //The Average numer of readings for the first three bits of the start word
	
	CurrentBit = 0;                                 //Because Start Word starts with Zero
	k = 0;
	i = 0;
	while (i < 12)
	{
		if (k >= 12)
		{
			break;
		}
		
		NoOfBits[i] = RoundNumber(ReadingsCounter[i] / AvgReadingsPerBit);
	
		for(j = 0 ; j < NoOfBits[i]; j++)
		{
			RxByteArr[k] = CurrentBit;
			k++;
		}
		
		CurrentBit = InvertBool(CurrentBit);
		i++;
	}
	for (i = 4; i < 12; i++)
	{
		if(RxByteArr[i] == 1)
		{
			SET_BIT(RxChar,(i - 4));
		}
		else
		{
			CLEAR_BIT(RxChar,(i - 4));
		}
	}
	
	if (!(RxByteArr[0] == 0x0
			&&RxByteArr[1] == 0x1
			&&RxByteArr[2] == 0x0
			&&RxByteArr[3] == 0x1))        
	{	
		RxChar = 0;
	}
	else
	{
 		i++;
	}
		//=======================================================================================================	
	return(RxChar);
}
	
/**
* @brief Rounds the number to the next zero. 
* @param x: Number to round.
* @return Rounded number
*/
U8 RoundNumber(float x)
{
	U8 y;
	
	y = x + 0.5;
	return y;
}

/**
* @brief Inverts/reverses a Boolean representation.
* @param CurrentBit: a Boolean to be reversed.
* @return The reverse of input Boolean
*/
U8 InvertBool(U8 CurrentBit)
{
	U8 ReturnedBit;
	
	if (CurrentBit == 0)
	{
		ReturnedBit =  1;
	}
	else
	{
		ReturnedBit = 0;
	}
	return ReturnedBit;
}
