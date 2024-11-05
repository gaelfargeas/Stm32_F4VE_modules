/*
 * modules.h
 *
 *  Created on: 31 oct. 2024
 *      Author: gael fargeas
 */

#ifndef SRC_MODULES_H_
#define SRC_MODULES_H_

#include "stdbool.h"

#define MODULES_NUMBER 1




/* Module A : AM2320 Module
 * com : I2C1
 * SDA	PB7
 * SCL	PB6
 */
#define MODULE_A_ENABLE true
#define MODULE_A_TIMER_MS 1000
#define MODULE_A_ADDRESS 0xB8

#endif /* SRC_MODULES_H_ */
