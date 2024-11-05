/*
 * hat_AM2320.h
 *
 *  Created on: 31 oct. 2024
 *      Author: gael fargeas
 */

#ifndef SRC_HAT_HAT_AM2320_H_
#define SRC_HAT_HAT_AM2320_H_

#include "driver_AM2320.h"

/* Exported functions prototypes ---------------------------------------------*/
HAL_StatusTypeDef AM2320_get_temperature(AM2320_HandleTypeDef *AM2320);
HAL_StatusTypeDef AM2320_get_humidity(AM2320_HandleTypeDef *AM2320);


#endif /* SRC_HAT_HAT_AM2320_H_ */
