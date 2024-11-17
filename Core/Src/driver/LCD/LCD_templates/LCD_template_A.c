/**
  ******************************************************************************
  * @file           : LCD_template_A.c
  * @brief          : LCD template A functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-09 gael fargeas created
  *
  */

/* Includes ---------------------------------------------------------*/
#include "LCD_template_A.h"


const LCD_template_typedef hLCD_template_A = {
		.title_x = 10,
		.title_y = 10,
		.font_title = &Font24,
		.text_x = 10,
		.text_y = 50,
		.font_text = &Font20,
};

/* Functions --------------------------------------------------------*/
/**
* @brief display the template A
* @param None.
* @retval None
*/
void LCD_template_A_display(void)
{
	uint16_t x1 = 40;
	uint16_t y1 = 35;

	uint16_t w = lcdGetWidth() - (x1 * 2);
	uint16_t h = 5;
	uint16_t r = 10;

	lcdFillRoundRect(x1, y1, w, h, r, COLOR_CYAN);
}
