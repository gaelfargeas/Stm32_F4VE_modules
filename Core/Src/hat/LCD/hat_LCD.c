/**
  ******************************************************************************
  * @file           : hat_LCD.c
  * @brief          : LCD Hat functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-08 gael fargeas created
  *
  */

/* Includes ---------------------------------------------------------*/
#include "hat_LCD.h"

/* Functions --------------------------------------------------------*/
/**
* @brief LCD initialization
* @param None
* @retval None
*/
void hat_LCD_init(void)
{
	LCD_BL_ON();
	lcdInit();
	lcdSetOrientation(LCD_ORIENTATION_PORTRAIT);
	lcdFillRGB(COLOR_BLACK);
}

/**
* @brief Display template and information
* @param hModule_info: Pointer to a Module_info_typedef structure that contains
*                the information to display for the specified module.
* @param template_selected: Template selected.
* @retval None
*/
void hat_LCD_display(Module_info_typedef *hModule_info, LCD_template_select template_selected)
{
	// Variables
	const LCD_template_typedef *template_data;
	static LCD_template_select template_displayed = LCD_TEMPLATE_DEFAULT;

	// Display template (background)
	switch (template_selected) {
		case LCD_TEMPLATE_A:
			if(template_displayed != LCD_TEMPLATE_A)
			{
				LCD_template_A_display();
				template_displayed = LCD_TEMPLATE_A;
			}

			template_data = &hLCD_template_A;

			break;
		case LCD_TEMPLATE_B:
			if(template_displayed != LCD_TEMPLATE_B)
			{
				LCD_template_B_display();
				template_displayed = LCD_TEMPLATE_B;
			}
			template_data = &hLCD_template_B;
			break;
		default:
			break;
	}

	// Set texts color
	lcdSetTextColor(COLOR_WHITE, COLOR_BLACK);

	// Display title
	lcdSetCursor(template_data->title_x, template_data->title_y);
	lcdSetTextFont(template_data->font_title);
	lcdPrintf(hModule_info->title);

	// Display text
	lcdSetCursor(template_data->text_x, template_data->text_y);
	lcdSetTextFont(template_data->font_text);
	lcdPrintf(hModule_info->text);
}
