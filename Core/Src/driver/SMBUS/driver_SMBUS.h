/**
  ******************************************************************************
  * @file           : driver_SMBUS.h
  * @brief          : Header for driver_SMBUS.c file.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-12 gael fargeas created
  *
  */

#ifndef SRC_DRIVER_SMBUS_DRIVER_SMBUS_H_
#define SRC_DRIVER_SMBUS_DRIVER_SMBUS_H_


/* Includes ---------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>

/* Defines ----------------------------------------------------------*/
#define SMBUS_MANUFACTURER_ACCESS 		0x00
#define SMBUS_REMAINING_CAPACITY_ALARM 	0x01
#define SMBUS_REMAINING_TIME_ALARM 		0x02
#define SMBUS_BATTERY_MODE 				0x03
#define SMBUS_AT_RATE 					0x04
#define SMBUS_AT_RATE_TIME_TO_FULL 		0x05
#define SMBUS_AT_RATE_TIME_TO_EMPTY 	0x06
#define SMBUS_AT_RATE_OK 				0x07
#define SMBUS_TEMPERATURE 				0x08
#define SMBUS_VOLTAGE 					0x09
#define SMBUS_CURRENT 					0x0A
#define SMBUS_AVERAGE_CURRENT 			0x0B
#define SMBUS_MAX_ERROR 				0x0C
#define SMBUS_RELATIVE_STATE_OF_CHARGE 	0x0D
#define SMBUS_ABSOLUTE_STATE_OF_CHARGE 	0x0E
#define SMBUS_REMAINING_CAPACITY 		0x0F
#define SMBUS_FULL_CHARGE_CAPACITY 		0x10
#define SMBUS_RUN_TIME_TO_EMPTY 		0x11
#define SMBUS_AVARAGE_TIME_TO_EMPTY 	0x12
#define SMBUS_AVARAGE_TIME_TO_FULL 		0x13
#define SMBUS_CHARGING_CURRENT 			0x14
#define SMBUS_CHARGING_VOLTAGE 			0x15
#define SMBUS_BATTERY_STATUS 			0x16

#define SMBUS_COMMANDE_WRITE 			1
#define SMBUS_COMMANDE_READ 			0

/* Typedef ----------------------------------------------------------*/
typedef struct {
	I2C_HandleTypeDef *i2c_handler;
	uint8_t SMBUS_address;
	uint32_t timeout;
	uint16_t remaining_capacity_alarm;
	uint16_t remaining_time_alarm;
	uint16_t battery_mode;
	int16_t at_rate;
	uint16_t at_rate_time_to_full;
	uint16_t at_rate_time_to_empty;
	uint8_t at_rate_ok;
	int16_t temperature;
	uint16_t voltage;
	int16_t current;
	int16_t average_current;
	uint16_t max_error;
	uint16_t relative_state_of_charge;
	uint16_t absolute_state_of_charge;
	uint16_t remaining_capacity;
	uint16_t full_charge_capacity;
	uint16_t run_time_to_empty;
	uint16_t avarage_time_to_empty;
	uint16_t avarage_time_to_full;
	uint16_t battery_status;
} module_SMBUS_HandleTypeDef;

/* Functions prototypes ---------------------------------------------*/
HAL_StatusTypeDef driver_SMBUS_get_data(module_SMBUS_HandleTypeDef *hsmbus, uint8_t *pdata, uint16_t size, uint8_t register_address);

#endif /* SRC_DRIVER_SMBUS_DRIVER_SMBUS_H_ */
