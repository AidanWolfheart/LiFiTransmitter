/**
  ******************************************************************************
  * @file    GLCD_Driver.h 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   Header file for GLCD driver.
  ******************************************************************************
  */

#include "Types.h"

/**
 * A structure to represent a button 
 */
typedef struct
{
	U16 x; /**< the x coordinate */
	U16 y; /**< the y coordinate */
	U16 Width; /**< width */
	U16	Height; /**< height */
}Button_Type;

void RefreshDisplay(void);
void SelectButton (U8 Button);
void ButtonDimensionsInit (void);
U8 GetTouchPositionFlags (void);
