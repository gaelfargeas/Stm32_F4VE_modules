/**
  ******************************************************************************
  * @file           : hat_SMBUS.h
  * @brief          : Header for hat_SMBUS.c file.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-12 gael fargeas created
  *
  */

#ifndef SRC_HAT_SMBUS_HAT_SMBUS_H_
#define SRC_HAT_SMBUS_HAT_SMBUS_H_

/* Includes ---------------------------------------------------------*/
#include "SMBUS/driver_SMBUS.h"


/* Functions prototypes ---------------------------------------------*/
module_SMBUS_HandleTypeDef hat_SMBUS_init(I2C_HandleTypeDef *hi2c, uint8_t smbus_adress);
uint16_t hat_SMBUS_get_remaining_capacity_alarm(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_remaining_time_alarm(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_battery_mode(module_SMBUS_HandleTypeDef *hsmbus);
int16_t hat_SMBUS_get_at_rate(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_at_rate_time_to_full(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_at_rate_time_to_empty(module_SMBUS_HandleTypeDef *hsmbus);
uint8_t hat_SMBUS_get_at_rate_ok(module_SMBUS_HandleTypeDef *hsmbus);
int16_t hat_SMBUS_get_temperature(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_voltage(module_SMBUS_HandleTypeDef *hsmbus);
int16_t hat_SMBUS_get_current(module_SMBUS_HandleTypeDef *hsmbus);
int16_t hat_SMBUS_get_average_current(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_max_error(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_relative_state_of_charge(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_absolute_state_of_charge(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_remaining_capacity(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_full_charge_capacity(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_run_time_to_empty(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_average_time_to_empty(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_average_time_to_full(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_charging_current(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_charging_voltage(module_SMBUS_HandleTypeDef *hsmbus);
uint16_t hat_SMBUS_get_battery_status(module_SMBUS_HandleTypeDef *hsmbus);


#endif /* SRC_HAT_SMBUS_HAT_SMBUS_H_ */
