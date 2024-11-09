/*
 * hat_LCD.h
 *
 *  Created on: 8 nov. 2024
 *      Author: gael fargeas
 */

#ifndef SRC_HAT_HAT_LCD_H_
#define SRC_HAT_HAT_LCD_H_

#include "ili9341.h"
#include "LCD_template.h"
#include "modules.h"

#define LCD_REFRESH_RATE 1000

void hat_LCD_init(void);
void hat_LCD_display(Module_info_typedef *hModule_info, LCD_template_select template_selected);

#endif /* SRC_HAT_HAT_LCD_H_ */
