/**
  ******************************************************************************
  * @file           : hat_LCD.h
  * @brief          : Header for hat_LCD.c file.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-08 gael fargeas created
  *
  */
#ifndef SRC_HAT_HAT_LCD_H_
#define SRC_HAT_HAT_LCD_H_

/* Includes ---------------------------------------------------------*/
#include "ili9341.h"
#include "LCD_template.h"
#include "modules.h"

/* Defines ----------------------------------------------------------*/
#define LCD_REFRESH_RATE 1000

/* Functions prototypes ---------------------------------------------*/
void hat_LCD_init(void);
void hat_LCD_display(Module_info_typedef *hModule_info, LCD_template_select template_selected);

#endif /* SRC_HAT_HAT_LCD_H_ */
