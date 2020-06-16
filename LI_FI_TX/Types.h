/**
  ******************************************************************************
  * @file    Types.h 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   Header file for types.
  ******************************************************************************
  */

typedef unsigned         	 char U8; /**< unsigned 8 bit */
typedef unsigned short     int U16; /**< unsigned 16 bit */
typedef unsigned           int U32; /**< unsigned 32 bit */

typedef   signed          char S8; /**< signed 8 bit */
typedef   signed short     int S16; /**< signed 16 bit */
typedef   signed           int S32; /**< unsigned 32 bit */

#define SET_BIT(R, Bit_Number) R|=(1<<Bit_Number)
#define CLEAR_BIT(R, Bit_Number) R&=~(1<<Bit_Number)
#define GET_BIT(R,Bit_Number) ((R&(1<<Bit_Number))>>Bit_Number)

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5
#define PORTG 6

#define INPUT_MODE  0
#define OUTPUT_MODE 1
#define AF_MODE     2
#define ANALOG_MODE 3

#define NO_PULL   0
#define PULL_UP   1
#define PULL_DOWN 2

#define BUTTON_1 1
#define BUTTON_2 2
#define BUTTON_3 4
#define BUTTON_4 8
#define BUTTON_5 16
#define BUTTON_6 32

#define COMMAND_1 251
#define COMMAND_2 252
#define COMMAND_3 253
#define COMMAND_4 254

#define MAX_FILE_SIZE 102400
#define APB2BUS_CLOCK 16000000

#define INIT_STATE               0
#define WAIT_FILE_TRANSFER_START 1
#define RX_FILE_STATE            2
#define TX_FILE_STATE 					 3