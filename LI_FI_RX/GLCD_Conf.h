/**
  ******************************************************************************
  * @file    GLCD_Conf.h 
  * @author  Moaz Hafez and Kiril Chomaniuk
  * @version V1.0.0
  * @date    29-April-2019
  * @brief   Header file for GLCD configuration.
  ******************************************************************************
  */

#define wait_delay HAL_Delay
#define WIDTH		GLCD_WIDTH
#define HEIGHT	GLCD_HEIGHT
#define CHAR_H  GLCD_Font_16x24.height                  /* Character Height (in pixels) */
#define CHAR_W  GLCD_Font_16x24.width                  /* Character Width (in pixels)  */
#define BAR_W   6									  /* Bar Width (in pixels) */
#define BAR_H		24				          /* Bar Height (in pixels) */
#define T_LONG	1000                /* Long delay */
#define T_SHORT 5                   /* Short delay */