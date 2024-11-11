/**
  ******************************************************************************
  * @file           : LCD_template.h
  * @brief          : Header for LCD_template.c file.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-09 gael fargeas created
  *
  */
#ifndef SRC_DRIVER_LCD_LCD_TEMPLATES_LCD_TEMPLATE_H_
#define SRC_DRIVER_LCD_LCD_TEMPLATES_LCD_TEMPLATE_H_

#include <stdint.h>
#include "fonts.h"
#include "image.h"
#include "ili9341.h"


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
  LCD_TEMPLATE_DEFAULT = 0,
  LCD_TEMPLATE_A	= 1,
  LCD_TEMPLATE_B    = 2,
  LCD_TEMPLATE_C    = 3,
  LCD_TEMPLATE_D  	= 4
} LCD_template_select;

#include "LCD_template_A.h"
#include "LCD_template_B.h"

extern const LCD_template_select LCD_template_selected;

void LCD_template_draw_image(GUI_CONST_STORAGE GUI_BITMAP *bmLogo);


#endif /* SRC_DRIVER_LCD_LCD_TEMPLATES_LCD_TEMPLATE_H_ */
