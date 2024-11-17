/**
  ******************************************************************************
  * @file           : hat_SMBUS.c
  * @brief          : SMBUS Hat functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-12 gael fargeas created
  *
  */

/* Includes ---------------------------------------------------------*/
#include "hat_SMBUS.h"

/* Functions --------------------------------------------------------*/
/**
* @brief SMBUS initialization
* @param hi2c: Pointer to a I2C_HandleTypeDef structure that contains
*                	informations for the specified I2C.
* @param smbus_adress: SMBUS slave address.
* @retval None
*/
module_SMBUS_HandleTypeDef hat_SMBUS_init(I2C_HandleTypeDef *hi2c, uint8_t smbus_adress)
{
	module_SMBUS_HandleTypeDef hSMBUS = {
			.i2c_handler = hi2c,
			.SMBUS_address = smbus_adress,
			.timeout = HAL_MAX_DELAY,
	};

	return hSMBUS;
}


/**
* @brief Get the "remaining capacity alarm" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_remaining_capacity_alarm(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_REMAINING_CAPACITY_ALARM);

	hsmbus->remaining_capacity_alarm = data;

	return data;
}

/**
* @brief Get the "remaining time alarm" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_remaining_time_alarm(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_REMAINING_TIME_ALARM);

	hsmbus->remaining_time_alarm = data;

	return data;
}

/**
* @brief Get the "battery mode" from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_battery_mode(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_BATTERY_MODE);

	hsmbus->battery_mode = data;

	return data;
}

/**
* @brief Get the "atRate" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
int16_t hat_SMBUS_get_at_rate(module_SMBUS_HandleTypeDef *hsmbus)
{
	int16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_AT_RATE);

	hsmbus->at_rate = data;

	return data;
}

/**
* @brief Get the "atRate (time to full)" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_at_rate_time_to_full(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_AT_RATE_TIME_TO_FULL);

	hsmbus->at_rate_time_to_full = data;

	return data;
}

/**
* @brief Get the "atRate (time to empty)" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_at_rate_time_to_empty(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_AT_RATE_TIME_TO_EMPTY);

	hsmbus->at_rate_time_to_empty = data;

	return data;
}

/**
* @brief Get the "atRate OK" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint8_t hat_SMBUS_get_at_rate_ok(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint8_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_AT_RATE_OK);

	hsmbus->at_rate_ok = data;

	return data;
}

/**
* @brief Get the "temperature" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
int16_t hat_SMBUS_get_temperature(module_SMBUS_HandleTypeDef *hsmbus)
{
	int16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_TEMPERATURE);

	hsmbus->temperature = data;

	return data;
}

/**
* @brief Get the "voltage" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_voltage(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_VOLTAGE);

	hsmbus->voltage= data;

	return data;
}

/**
* @brief Get the "current" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
int16_t hat_SMBUS_get_current(module_SMBUS_HandleTypeDef *hsmbus)
{
	int16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_CURRENT);

	hsmbus->current = data;

	return data;
}

/**
* @brief Get the "average current" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
int16_t hat_SMBUS_get_average_current(module_SMBUS_HandleTypeDef *hsmbus)
{
	int16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_AVERAGE_CURRENT);

	hsmbus->average_current = data;

	return data;
}

/**
* @brief Get the "max error" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_max_error(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_MAX_ERROR);

	hsmbus->max_error = data;

	return data;
}

/**
* @brief Get the "relative state of charge" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_relative_state_of_charge(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_RELATIVE_STATE_OF_CHARGE);

	hsmbus->relative_state_of_charge = data;

	return data;
}

/**
* @brief Get the "absolute state of charge" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_absolute_state_of_charge(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_ABSOLUTE_STATE_OF_CHARGE);

	hsmbus->absolute_state_of_charge = data;

	return data;
}

/**
* @brief Get the "remaining capacity" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_remaining_capacity(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_REMAINING_CAPACITY);

	hsmbus->remaining_capacity = data;

	return data;
}

/**
* @brief Get the "full charge capacity" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_full_charge_capacity(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_FULL_CHARGE_CAPACITY);

	hsmbus->full_charge_capacity = data;

	return data;
}

/**
* @brief Get the "time to run empty" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_run_time_to_empty(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_RUN_TIME_TO_EMPTY);

	hsmbus->run_time_to_empty = data;

	return data;
}

/**
* @brief Get the "avarage time to empty" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_average_time_to_empty(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_AVARAGE_TIME_TO_EMPTY);

	hsmbus->avarage_time_to_empty = data;

	return data;
}

/**
* @brief Get the "average time to full" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_average_time_to_full(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_AVARAGE_TIME_TO_FULL);

	hsmbus->avarage_time_to_full = data;

	return data;
}

/**
* @brief Get the "charging current" value from SMBUS charger
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_charging_current(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_CHARGING_CURRENT);


	return data;
}

/**
* @brief Get the "charging voltage" value from SMBUS charger
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_charging_voltage(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_CHARGING_VOLTAGE);


	return data;
}

/**
* @brief Get the "battery status" value from SMBUS
* @param hsmbus: Pointer to a module_SMBUS_HandleTypeDef structure that contains
*                	informations for the specified SMBUS.
* @retval None
*/
uint16_t hat_SMBUS_get_battery_status(module_SMBUS_HandleTypeDef *hsmbus)
{
	uint16_t data = 0;
	driver_SMBUS_get_data(hsmbus, (uint8_t *) &data, sizeof(data), SMBUS_BATTERY_STATUS);

	hsmbus->battery_status = data;

	return data;
}



