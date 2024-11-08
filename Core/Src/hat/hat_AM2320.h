/**
  ******************************************************************************
  * @file           : module_loader.c
  * @brief          : Header for hat_AM2320.c file..
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-10-31 gael fargeas created
  *
  */

#ifndef SRC_HAT_HAT_AM2320_H_
#define SRC_HAT_HAT_AM2320_H_

#include "driver_AM2320.h"
#include <stdio.h>

/* Exported functions prototypes ---------------------------------------------*/
HAL_StatusTypeDef AM2320_get_temperature(AM2320_HandleTypeDef *AM2320);
HAL_StatusTypeDef AM2320_get_humidity(AM2320_HandleTypeDef *AM2320);
int AM2320_to_string(AM2320_HandleTypeDef *AM2320);

#endif /* SRC_HAT_HAT_AM2320_H_ */
