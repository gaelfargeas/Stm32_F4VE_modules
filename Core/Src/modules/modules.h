/**
  ******************************************************************************
  * @file           : module_loader.c
  * @brief          : Header for modules.c file.
  *                   This file contains the modules defines.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-10-31 gael fargeas created
  *
  */
#ifndef SRC_MODULES_H_
#define SRC_MODULES_H_

#define MODULES_NUMBER 1

/* Module AM2320
 * com : I2C1
 * SDA	PB7
 * SCL	PB6
 */
#define MODULE_AM2320_ENABLE
#define MODULE_AM2320_TIMER_MS 1000
#define MODULE_AM2320_ADDRESS 0xB8


#endif /* SRC_MODULES_H_ */
