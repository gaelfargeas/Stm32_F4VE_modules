/*
 * LCD_template.h
 *
 *  Created on: 9 nov. 2024
 *      Author: gael fargeas
 */

#ifndef SRC_DRIVER_LCD_LCD_TEMPLATES_LCD_TEMPLATE_H_
#define SRC_DRIVER_LCD_LCD_TEMPLATES_LCD_TEMPLATE_H_

#include <stdint.h>
#include "fonts.h"

typedef struct
{
  uint16_t 					title_x;
  uint16_t 					title_y;
  sFONT *					font_title;
  uint16_t 					text_x;
  uint16_t 					text_y;
  sFONT *					font_text;
} LCD_template_typedef;

typedef enum
{
  LCD_TEMPLATE_A	= 0,
  LCD_TEMPLATE_B    = 1,
  LCD_TEMPLATE_C    = 2,
  LCD_TEMPLATE_D  	= 3
} LCD_template_select;

#include "LCD_template_A.h"
#endif /* SRC_DRIVER_LCD_LCD_TEMPLATES_LCD_TEMPLATE_H_ */
