/**
  ******************************************************************************
  * @file    GLCD_driver.c 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   This file provides functions that drives the board screen.
  ******************************************************************************
  */

#include "Types.h"
#include "GLCD_Driver.h"
#include "Board_GLCD.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"

/** @GLCD MAIN_Private_FunctionPrototypes
* @{
*/ 
extern TOUCH_STATE  tsc_state;
/**
* @}
*/ 

/** @defgroup MAIN_Private_Variables
* @{
*/	
Button_Type Button1; /**< Button 1 */
Button_Type Button2; /**< Button 2 */
Button_Type Button3; /**< Button 3 */
Button_Type Button4; /**< Button 4 */
Button_Type Button5; /**< Button 5 */
Button_Type Button6; /**< Button 6 */
U8 RefreshDisplayFlag; /**< Flag to refresh screen */
/**
* @}
*/ 

/**
* @brief Clears the screen by drawing elements again.
* @param None 
* @retval None
*/	
void RefreshDisplay(void)
{
	GLCD_ClearScreen ();
	GLCD_DrawRectangle(5,5,470,262);
	GLCD_DrawRectangle(7,7,466,258);
	
	GLCD_DrawString(65,55,"PC");
	GLCD_DrawString(20,85,"Keyboard");	
	GLCD_DrawString(200,55,"File");
	GLCD_DrawString(173,85,"Transfer");
	GLCD_DrawString(340,55,"Periph.");
	GLCD_DrawString(385,85,"1");	
	GLCD_DrawString(340,55,"Periph.");
	GLCD_DrawString(385,85,"1");	
	GLCD_DrawString(30,175,"Periph.");
	GLCD_DrawString(75,205,"2");	
	GLCD_DrawString(185,175,"Periph.");
	GLCD_DrawString(230,205,"3");
	GLCD_DrawString(340,175,"Periph.");
	GLCD_DrawString(385,205,"4");
	
	GLCD_DrawRectangle(Button1.x,Button1.y,Button1.Width,Button1.Height);
	GLCD_DrawRectangle(Button2.x,Button2.y,Button2.Width,Button2.Height);
	GLCD_DrawRectangle(Button3.x,Button3.y,Button3.Width,Button3.Height);
	GLCD_DrawRectangle(Button4.x,Button4.y,Button4.Width,Button4.Height);
	GLCD_DrawRectangle(Button5.x,Button5.y,Button5.Width,Button5.Height);
	GLCD_DrawRectangle(Button6.x,Button6.y,Button6.Width,Button6.Height);
	
	RefreshDisplayFlag = 0;
}

/**
* @brief Draws a bold frame around a selected button.
* @param Button: the button to frame.
* @retval None
*/	
void SelectButton (U8 Button)
{
	Button_Type* ButtonsArr[6] = {&Button1, &Button2, &Button3, &Button4, &Button5, &Button6};
	U8 i;
	
	RefreshDisplay();
	
	for (i = 0; i < 3 ; i++)
	{
		GLCD_DrawRectangle(ButtonsArr[Button]->x - i, ButtonsArr[Button]->y - i, ButtonsArr[Button]->Width, ButtonsArr[Button]->Height);
	}
}

/**
* @brief Specifies the dimensions of a button.
* @param None
* @retval None
*/	
void ButtonDimensionsInit (void)
{
	Button1.x = 15;
	Button1.y = 45;
	Button1.Width = 135;
	Button1.Height = 70;
	
	Button2.x = 162;
	Button2.y = 45;
	Button2.Width = 144;
	Button2.Height = 70;
	
	Button3.x = 318;
	Button3.y = 45;
	Button3.Width = 148;
	Button3.Height = 70;
	
	Button4.x = 15;
	Button4.y = 165;
	Button4.Width = 135;
	Button4.Height = 70;
	
	Button5.x = 162;
	Button5.y = 165;
	Button5.Width = 144;
	Button5.Height = 70;
	
	Button6.x = 318;
	Button6.y = 165;
	Button6.Width = 148;
	Button6.Height = 70;
}

/**
* @brief Receives the coordinates of a touch.
* @param None  
* @return Which button to select
*/	
U8 GetTouchPositionFlags (void)
{
	U8 ButtonFlags = 0;
	RefreshDisplayFlag = 1;
	
	 if((tsc_state.x > Button1.x) && (tsc_state.x < Button1.x+Button1.Width)
		&&(tsc_state.y > Button1.y) && (tsc_state.y < Button1.y+Button1.Height))
	 {
		 SET_BIT(ButtonFlags,0);
	 }
	
	if((tsc_state.x > Button2.x) && (tsc_state.x < Button2.x+Button2.Width)
		&&(tsc_state.y > Button2.y) && (tsc_state.y < Button2.y+Button2.Height))	
	{
		SET_BIT(ButtonFlags,1);
	}
	
	if((tsc_state.x > Button3.x) && (tsc_state.x < Button3.x+Button3.Width)
		&&(tsc_state.y > Button3.y) && (tsc_state.y < Button3.y+Button3.Height))
	{
		SET_BIT(ButtonFlags,2);
	}
		
	if((tsc_state.x > Button4.x) && (tsc_state.x < Button4.x+Button4.Width)
		&&(tsc_state.y > Button4.y) && (tsc_state.y < Button4.y+Button4.Height))
	{
		SET_BIT(ButtonFlags,3);
	}
	
	if((tsc_state.x > Button5.x) && (tsc_state.x < Button5.x+Button5.Width)
		&&(tsc_state.y > Button5.y) && (tsc_state.y < Button5.y+Button5.Height))	
	{
		SET_BIT(ButtonFlags,4);
	}

	if((tsc_state.x > Button6.x) && (tsc_state.x < Button6.x+Button6.Width)
	&&(tsc_state.y > Button6.y) && (tsc_state.y < Button6.y+Button6.Height))
	{
		SET_BIT(ButtonFlags,5);
	}
	
	return ButtonFlags;
}