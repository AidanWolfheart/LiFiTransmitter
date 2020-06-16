/**
  ******************************************************************************
  * @file    Types.h 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   Header file for types.
  ******************************************************************************
  */

typedef unsigned         	 char U8;
typedef unsigned short     int U16;
typedef unsigned           int U32;

typedef   signed          char S8;
typedef   signed short     int S16;
typedef   signed           int S32;

#define SET_BIT(R, Bit_Number) R|=(1<<Bit_Number)
#define CLEAR_BIT(R, Bit_Number) R&=~(1<<Bit_Number)

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5
#define PORTG 6
#define PORTH 7
#define PORTI 8

#define INPUT_MODE  0
#define OUTPUT_MODE 1
#define AF_MODE     2
#define ANALOG_MODE 3

#define NO_PULL   0
#define PULL_UP   1
#define PULL_DOWN 2

#define WriteKBAndCMD     0
#define FILE_TRANSFER  		1
#define COMMAND_1			 		251
#define COMMAND_2			 		252
#define COMMAND_3			 		253
#define COMMAND_4			 		254
#define ENTER_BUTTON   		13
#define BACK_SPACE_BUTTON 255

#define APB2BUS_CLOCK 16000000
#define FILE_RX_TIME_OUT (APB2BUS_CLOCK/1000)*250
