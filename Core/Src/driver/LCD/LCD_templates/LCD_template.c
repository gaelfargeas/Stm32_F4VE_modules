/**
  ******************************************************************************
  * @file           : LCD_template.c
  * @brief          : LCD template base functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-11 gael fargeas created
  *
  */

/* Includes ---------------------------------------------------------*/
#include "LCD_template.h"

/* Functions --------------------------------------------------------*/
/**
* @brief display image
* @param bmLogo: Pointer to a GUI_BITMAP structure that contains
*                the specified image and his informations.
* @retval None
*/
void LCD_template_draw_image(GUI_CONST_STORAGE GUI_BITMAP *bmLogo)
{
	if (lcdGetOrientation() == LCD_ORIENTATION_LANDSCAPE || lcdGetOrientation() == LCD_ORIENTATION_LANDSCAPE_MIRROR)
	{
		lcdDrawImage((lcdGetWidth() - bmLogo->xSize) / 2, 0, bmLogo);
	}
	else
	{
		lcdDrawImage(0, (lcdGetHeight() - bmLogo->ySize) / 2, bmLogo);
	}
}
