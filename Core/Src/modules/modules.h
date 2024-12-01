/**
  ******************************************************************************
  * @file           : modules.h
  * @brief          : Header for hat_AM2320.c file.
  * 				  This file contains the modules defines.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-10-31 gael fargeas created
  *
  */
#ifndef SRC_MODULES_H_
#define SRC_MODULES_H_

/* Define -------------------------------------------------------------*/
#define MODULES_NUMBER 1

/* Module AM2320
 * com : I2C1
 * SDA	PB7
 * SCL	PB6
 */
#define MODULE_AM2320_ENABLE
#define MODULE_AM2320_TIMER_MS 1000
#define MODULE_AM2320_ADDRESS 0xB8


/* Module SMBUS
 * com : I2C2
 * SDA	PB11
 * SCL	PB10
 */
#define MODULE_SMBUS_ENABLE
#define MODULE_SMBUS_TIMER_MS 1000
#define MODULE_SMBUS_ADDRESS 0xB8

/* Module WIRELESS
 * com : SPI2
 * MOSI	PB15
 * MISO	PB14
 * SCK	PB13
 * CS	PB12
 */
#define MODULE_WIRELESS_ENABLE
#define MODULE_WIRELESS_TIMER_MS 1000

/* Include -------------------------------------------------------------*/
#include "stdint.h"

/* Typedef -------------------------------------------------------------*/
typedef struct
{
	char title[20];
	char text[100];
} Module_info_typedef;

typedef enum
{
  MODULE_DEFAULT 	= 0,
  MODULE_AM2320		= 1
} module_list_enum;

/* Variables -----------------------------------------------------------*/
extern module_list_enum active_module[MODULES_NUMBER];

/* Function ------------------------------------------------------------*/
void module_init(void);

#endif /* SRC_MODULES_H_ */
