/*
 * hat_LCD.c
 *
 *  Created on: 8 nov. 2024
 *      Author: gael fargeas
 */
#include "hat_LCD.h"

void hat_LCD_init(void)
{
	LCD_BL_ON();
	lcdInit();
	lcdSetOrientation(LCD_ORIENTATION_PORTRAIT);
	lcdFillRGB(COLOR_BLACK);
}

void hat_LCD_display(Module_info_typedef *hModule_info, LCD_template_select template_selected)
{
	// Variables
	const LCD_template_typedef *template_data;
	static LCD_template_select template_displayed = LCD_TEMPLATE_DEFAULT;

	// Display template (background)
	switch (template_selected) {
		case LCD_TEMPLATE_A:
			if(LCD_template_select != LCD_TEMPLATE_A)
			{
				LCD_template_A_display();
				LCD_template_select = LCD_TEMPLATE_A;
			}

			template_data = &hLCD_template_A;

			break;
		case LCD_TEMPLATE_B:
			if(LCD_template_select != LCD_TEMPLATE_B)
			{
				LCD_template_B_display();
				LCD_template_select = LCD_TEMPLATE_B;
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
