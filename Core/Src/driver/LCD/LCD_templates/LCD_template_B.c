/**
  ******************************************************************************
  * @file           : LCD_template_B.c
  * @brief          : LCD template B functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-09 gael fargeas created
  *
  */

/* Includes ---------------------------------------------------------*/
#include "LCD_template_B.h"


/* Variables --------------------------------------------------------*/
const LCD_template_typedef hLCD_template_B = {
		.title_x = 10,
		.title_y = 10,
		.font_title = &Font24,
		.text_x = 10,
		.text_y = 50,
		.font_text = &Font20,
};

/* Functions --------------------------------------------------------*/
/**
* @brief display the template B
* @param None.
* @retval None
*/
void LCD_template_B_display(void)
{
 LCD_template_draw_image(&bmtemplate_B);
}
