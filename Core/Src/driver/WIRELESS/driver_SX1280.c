/*
 * driver_E28-2G4M27S.c
 *
 *  Created on: 27 nov. 2024
 *      Author: gael fargeas
 */
#include "driver_SX1280.h"


/**
* @brief Set the CS GPIO to high.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_cs_high(module_wireless_HandleTypeDef *hwirelessmodule)
{
	GPIO_PinState pin_status = GPIO_PIN_RESET;

	// Set GPIO
	HAL_GPIO_WritePin(hwirelessmodule->CS_GPIOx, hwirelessmodule->CS_GPIO_Pin, GPIO_PIN_SET);

	// Check GPIO
	pin_status = HAL_GPIO_ReadPin(hwirelessmodule->CS_GPIOx, hwirelessmodule->CS_GPIO_Pin);

	if(pin_status != GPIO_PIN_SET)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

/**
* @brief Set the CS GPIO to low.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_cs_low(module_wireless_HandleTypeDef *hwirelessmodule)
{

	GPIO_PinState pin_status = GPIO_PIN_SET;

	// Set GPIO
	HAL_GPIO_WritePin(hwirelessmodule->CS_GPIOx, hwirelessmodule->CS_GPIO_Pin, GPIO_PIN_RESET);

	// Check GPIO
	pin_status = HAL_GPIO_ReadPin(hwirelessmodule->CS_GPIOx, hwirelessmodule->CS_GPIO_Pin);

	if(pin_status != GPIO_PIN_RESET)
	{
		return HAL_ERROR;
	}

	return HAL_OK;

}
HAL_StatusTypeDef driver_SX1280_init(module_wireless_HandleTypeDef *hwirelessmodule)
{
	HAL_StatusTypeDef ret_status = HAL_OK;

	ret_status = driver_SX1280_reset(hwirelessmodule);

	return ret_status;
}

HAL_StatusTypeDef driver_SX1280_reset(module_wireless_HandleTypeDef *hwirelessmodule)
{
	HAL_StatusTypeDef ret_status = HAL_OK;

//	ret_status = driver_SX1280_write_register(hwirelessmodule, reg, (uint8_t *) 0X00, value_size);

	return ret_status;
}

HAL_StatusTypeDef driver_SX1280_write_register(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t reg, uint8_t *value, uint8_t value_size)
{
	HAL_StatusTypeDef status = HAL_OK;

	// SX1280_CMD_READ_REGISTER 8bit : register 16b : data x*8b
	uint8_t command[3];
	command[0] = SX1280_CMD_WRITE_REGISTER;
	command[1] = ( reg & 0xFF00 ) >> 8;
	command[2] = reg & 0x00FF;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	if(status != HAL_OK)
	{
		driver_SX1280_cs_low(hwirelessmodule);
		return status;
	}

	status = HAL_SPI_Receive(hwirelessmodule->spi_handler, value, value_size, hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

HAL_StatusTypeDef driver_SX1280_read_register(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t reg, uint8_t *value, uint8_t value_size)
{
	HAL_StatusTypeDef status = HAL_OK;

	// SX1280_CMD_WRITE_REGISTER 8bit | register 16b | NOP 8b | receive data x*8b
	uint8_t command[4];
	command[0] = SX1280_CMD_READ_REGISTER;
	command[1] = ( reg & 0xFF00 ) >> 8;
	command[2] = reg & 0x00FF;
	command[3] = SX1280_NOP;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	if(status != HAL_OK)
	{
		driver_SX1280_cs_low(hwirelessmodule);
		return status;
	}

	status = HAL_SPI_Receive(hwirelessmodule->spi_handler, value, value_size, hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

HAL_StatusTypeDef driver_SX1280_send_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *value, uint8_t value_size)
{
	HAL_StatusTypeDef status = HAL_OK;

	// SX1280_CMD_WRITE_BUFFER 8bit | offset 8b | data x*8b
	uint8_t command[2];
	command[0] = SX1280_CMD_WRITE_BUFFER;
	command[1] = SX1280_NOP;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	if(status != HAL_OK)
	{
		driver_SX1280_cs_low(hwirelessmodule);
		return status;
	}

	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, value, value_size, hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

HAL_StatusTypeDef driver_SX1280_receice_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *value, uint8_t value_size)
{
	HAL_StatusTypeDef status = HAL_OK;

	// SX1280_CMD_WRITE_BUFFER 8bit | offset 8b | receive data x*8b
	uint8_t command[2];
	command[0] = SX1280_CMD_READ_BUFFER;
	command[1] = SX1280_NOP;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	if(status != HAL_OK)
	{
		driver_SX1280_cs_low(hwirelessmodule);
		return status;
	}

	status = HAL_SPI_Receive(hwirelessmodule->spi_handler, value, value_size, hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

/**
* @brief Set the transceiver into sleep mode.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param  sleep_config: 	Sleep configuration (data flush or retention).
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_sleep_mode(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_SLEEP_CONFIGS sleep_config)
{
	HAL_StatusTypeDef status = HAL_OK;

	// SX1280_CMD_SET_SLEEP 8bit | sleep_config 8b
	uint8_t command[2];
	command[0] = SX1280_CMD_SET_SLEEP;
	command[1] = sleep_config;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

/**
* @brief Set the transceiver into standby mode.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param  sleep_config: 	Standby configuration (select RC or XTAL clock).
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_standby_mode(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_STANDBY_CONFIGS standby_config)
{
	HAL_StatusTypeDef status = HAL_OK;

	// SX1280_CMD_SET_STANDBY 8bit | standby_config 8b
	uint8_t command[2];
	command[0] = SX1280_CMD_SET_STANDBY;
	command[1] = standby_config;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

/**
* @brief Set the transceiver into FS mode (test purposes of the PLL).
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_FS_mode(module_wireless_HandleTypeDef *hwirelessmodule)
{
	HAL_StatusTypeDef status = HAL_OK;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, (uint8_t *) SX1280_CMD_SET_FS, sizeof(uint8_t), hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

/**
* @brief Set the transceiver into Tx mode.
* @param hwirelessmodule: 		Pointer to a wireless_module_HandleTypeDef structure that contains
*                				informations for the specified wireless connection.
* @param period_base:			RTC step.
* @param Tx_period_base_count:	timeout (period_base * Tx_period_base_count).
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_Tx_mode(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_TX_RX_PERIODE_BASE period_base, uint16_t Tx_period_base_count)
{
	HAL_StatusTypeDef status = HAL_OK;

	// SX1280_CMD_SET_TX 8bit | periodBase 8b | periodBaseCount 16b
	uint8_t command[4];
	command[0] = SX1280_CMD_SET_TX;
	command[1] = period_base;
	command[2] = ( Tx_period_base_count & 0xFF00 ) >> 8;
	command[3] = Tx_period_base_count & 0x00FF;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

/**
* @brief Set the transceiver into Rx mode.
* @param hwirelessmodule: 		Pointer to a wireless_module_HandleTypeDef structure that contains
*                				informations for the specified wireless connection.
* @param period_base:			RTC step.
* @param Rx_period_base_count:	timeout (period_base * Rx_period_base_count).
*
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_Rx_mode(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_TX_RX_PERIODE_BASE period_base, uint16_t Rx_period_base_count)
{
	HAL_StatusTypeDef status = HAL_OK;

	// SX1280_CMD_SET_RX 8bit | periodBase 8b | periodBaseCount 16b
	uint8_t command[4];
	command[0] = SX1280_CMD_SET_RX;
	command[1] = period_base;
	command[2] = (Rx_period_base_count & 0xFF00) >> 8;
	command[3] = Rx_period_base_count & 0x00FF;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

/**
* @brief Set the transceiver into sniff mode.
* @param hwirelessmodule: 			Pointer to a wireless_module_HandleTypeDef structure that contains
*                					informations for the specified wireless connection.
* @param period_base:				RTC step.
* @param Rx_period_base_count:		Rx duration (period_base * Rx_period_base_count).
* @param sleep_period_base_count:	Sleep duration (period_base * sleep_period_base_count).
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_sniff_mode(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_TX_RX_PERIODE_BASE period_base,
		uint16_t Rx_period_base_count, uint16_t sleep_period_base_count)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_RX_DUTY_CYCLE 8bit | periodBase 8b | rxPeriodBaseCount 16b | sleepPeriodBaseCount 16b
		uint8_t command[6];
		command[0] = SX1280_CMD_SET_RX_DUTY_CYCLE;
		command[1] = period_base;
		command[2] = (Rx_period_base_count & 0xFF00) >> 8;
		command[3] = Rx_period_base_count & 0x00FF;
		command[4] = (sleep_period_base_count & 0xFF00) >> 8;
		command[5] = sleep_period_base_count & 0x00FF;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the transceiver into Long preamble mode.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param enable     	  	Enable the mode.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_long_preamble_mode(module_wireless_HandleTypeDef *hwirelessmodule, bool enable)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_LONG_PREAMBLE 8bit | enable 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_LONG_PREAMBLE;
		command[1] = enable;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the transceiver into CAD mode (Channel Activity Detection). it's a LoRa® specific mode of operation where the device searches for a LoRa® signal.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_CAD_mode(module_wireless_HandleTypeDef *hwirelessmodule)
{
	HAL_StatusTypeDef status = HAL_OK;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, (uint8_t *) SX1280_CMD_SET_CAD, sizeof(uint8_t), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the transceiver into Tx continuous wave mode. generate a Continuous Wave (RF tone) at a selected frequency and output power
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_Tx_continuous_wave_mode(module_wireless_HandleTypeDef *hwirelessmodule)
{
	HAL_StatusTypeDef status = HAL_OK;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, (uint8_t *) SX1280_CMD_SET_TX_CONTINUOUS_WAVE, sizeof(uint8_t), hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

/**
* @brief Set the transceiver into Tx continuous preamble mode (test mode). Generate an infinite sequence of alternating ‘0’s and ‘1’s in GFSK, BLE,
* or FLRC modulation and symbol 0 in LoRa®
* @param hwirelessmodule:	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_Tx_continuous_preamble_mode(module_wireless_HandleTypeDef *hwirelessmodule)
{
	HAL_StatusTypeDef status = HAL_OK;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, (uint8_t *) SX1280_CMD_SET_TX_CONTINUOUS_PREAMBLE, sizeof(uint8_t), hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

/**
* @brief Allows the transceiver to send a packet at a user programmable time (time) after the end of a packet reception.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param time:				User programmable time (Tx delay = time + Offset). Offset is a time needed for the transceiver to switch modes and is equal to 33 μs.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_auto_Tx(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t time)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_AUTO_TX 8bit | standby_config 16b
		uint8_t command[3];
		command[0] = SX1280_CMD_SET_AUTO_TX;
		command[1] = (time & 0xFF00) >> 8;
		command[2] = time & 0x00FF;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Modifies the chip behavior so that the state following a Rx or Tx operation is FS and not Standby.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param enable:			Enable.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_auto_FS(module_wireless_HandleTypeDef *hwirelessmodule, bool enable)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_AUTO_FS 8bit | standby_config 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_AUTO_FS;
		command[1] = enable;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the transceiver packet type.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param packet_type:		Enable.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_packet_type(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_PACKET_TYPE packet_type)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_PACKET_TYPE 8bit | packetType 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_PACKET_TYPE;
		command[1] = packet_type;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Get the transceiver packet type.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param packet_type:		pointer to packet type variable.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_get_packet_type(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *packet_type)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_GET_PACKET_TYPE 8bit | receive packet_type 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_GET_PACKET_TYPE;
		command[1] = SX1280_NOP;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		if(status != HAL_OK)
		{
			driver_SX1280_cs_low(hwirelessmodule);
			return status;
		}

		status = HAL_SPI_Receive(hwirelessmodule->spi_handler, packet_type, sizeof(uint8_t), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the frequency of the RF frequency mode.
* @param hwirelessmodule:	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param frequency:			Value equal to the PLL step i.e. 52e6/2^18 Hz, where 52e6 is the crystal frequency in Hz.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_RF_frequency(module_wireless_HandleTypeDef *hwirelessmodule, uint32_t frequency)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_RF_FREQUENCY 8bit | standby_config 24b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_RF_FREQUENCY;
		command[1] = (frequency & 0x00FF0000) >> 16;
		command[2] = (frequency & 0x0000FF00) >> 8;
		command[3] = frequency & 0x000000FF;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the transceiver Tx output power and the Tx ramp time.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param power:				Power value (Pout = -18dbm + power, max 13dbm).
* @param ramp_time:			Ramp time value.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_Tx_params(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t power, SX1280_TX_RAMP_TIME ramp_time)
{
	HAL_StatusTypeDef status = HAL_OK;

	if(power > 31)
	{
		power = 31;
	}

	// SX1280_CMD_SET_TX_PARAMS 8bit | power 8b | ramp_time 8b
	uint8_t command[3];
	command[0] = SX1280_CMD_SET_TX_PARAMS;
	command[1] = power;
	command[2] = ramp_time;

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	return status;
}

/**
* @brief Set the number of symbols on which Channel Activity Detected (CAD) operates.
* @param hwirelessmodule: 		Pointer to a wireless_module_HandleTypeDef structure that contains
*                				informations for the specified wireless connection.
* @param cad_symbol_number:		Number of symbols on which Channel Activity Detected (CAD) operates.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_cad_params(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_CAD_SYMBOL_NUMBER cad_symbol_number)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_CAD_PARAMS 8bit | cadSymbolNum 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_CAD_PARAMS;
		command[1] = cad_symbol_number;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Fixes the base address for the packet handing operation in Tx and Rx mode for all packet types.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param tx_base_adress:	Tx buffer base address.
* @param rx_base_adress:	Rx buffer base address.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_buffer_base_address(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t tx_base_adress, uint8_t rx_base_adress)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_BUFFER_BASE_ADDRESS 8bit | txBaseAdress 8b | rxBaseAdress 8b
		uint8_t command[3];
		command[0] = SX1280_CMD_SET_BUFFER_BASE_ADDRESS;
		command[1] = tx_base_adress;
		command[2] = rx_base_adress;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief configure the modulation parameters of the transceiver.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param modulation_Param1:	For BLE, GFSK and FLRC: 		"BitrateBandwidth".
* 							For LoRa® and Ranging Engine: 	"SpreadingFactor".
*
* @param modulation_Param2:	For BLE and GFSK: 				"ModulationIndex".
* 							For FLRC: 						"CodingRate".
* 							For LoRa® and Ranging Engine: 	"Bandwidth".
*
* @param modulation_Param3:	for BLE, GFSK and FLRC: 		"ModulationShaping".
* 							For LoRa® and Ranging Engine: 	"CodingRate" .
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_modulation_params(module_wireless_HandleTypeDef *hwirelessmodule,
		uint8_t modulation_Param1, uint8_t modulation_Param2, uint8_t modulation_Param3)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_MODULATION_PARAMS 8bit | modParam1 8b | modParam2 8b | modParam3 8b
		uint8_t command[4];
		command[0] = SX1280_CMD_SET_MODULATION_PARAMS;
		command[1] = modulation_Param1;
		command[2] = modulation_Param2;
		command[3] = modulation_Param3;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the parameters of the packet handling block
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param packet_Param1:		For BLE and GFSK: 				"PreambleLength".
* 							For FLRC: 						"ConnectionState".
* 							For LoRa® and Ranging Engine: 	"PreambleLength".
*
* @param packet_Param2:		For BLE and GFSK: 				"SyncWordLength".
* 							For FLRC: 						"CrcLength".
* 							For LoRa® and Ranging Engine: 	"HeaderType".
*
* @param packet_Param3:		for BLE and GFSK: 				"SyncWordMatch".
* 							For FLRC: 						"BleTestPayload".
* 							For LoRa® and Ranging Engine: 	"PayloadLength" .
*
* @param packet_Param4:		For BLE and GFSK: 				"HeaderType".
* 							For FLRC: 						"Whitening".
* 							For LoRa® and Ranging Engine: 	"CRC".
*
* @param packet_Param5:		For BLE and GFSK: 				"PayloadLength".
* 							For FLRC: 						"not used".
* 							For LoRa® and Ranging Engine: 	"InvertIQ/chirp invert".
*
* @param packet_Param6:		for BLE and GFSK: 				"CrcLength".
* 							For FLRC: 						"not used".
* 							For LoRa® and Ranging Engine: 	"not used" .
*
* @param packet_Param7:		For BLE and GFSK: 				"Whitening".
* 							For FLRC: 						"not used".
* 							For LoRa® and Ranging Engine: 	"not used".
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_packet_params(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t packet_Param1,  uint8_t packet_Param2,
		 uint8_t packet_Param3, uint8_t packet_Param4, uint8_t packet_Param5, uint8_t packet_Param6, uint8_t packet_Param7)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_PACKET_PARAMS 8bit | packet_Param1 8b | packet_Param2 8b | packet_Param3 8b | packet_Param4 8b | packet_Param5 8b | packet_Param6 8b | packet_Param7 8b
		uint8_t command[8];
		command[0] = SX1280_CMD_SET_PACKET_PARAMS;
		command[1] = packet_Param1;
		command[2] = packet_Param2;
		command[3] = packet_Param3;
		command[4] = packet_Param4;
		command[5] = packet_Param5;
		command[6] = packet_Param6;
		command[7] = packet_Param7;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Get the length of the last received packet (Rx_payload_length) and the address of the first byte received (Rx_start_buffer_pointer).
* @param hwirelessmodule: 			Pointer to a wireless_module_HandleTypeDef structure that contains
*                					informations for the specified wireless connection.
* @param Rx_payload_length:			Pointer to Rx_payload_length variable.
* @param Rx_start_buffer_pointer:	Pointer to Rx_start_buffer_pointer variable.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_get_Rx_buffer_status(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *Rx_payload_length, uint8_t *Rx_start_buffer_pointer)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_RX_BUFFER_STATUS 8bit | receive Rx_payload_length 8b | Rx_start_buffer_pointer 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_RX_BUFFER_STATUS;
		command[1] = SX1280_NOP;

		uint8_t tmp_data[2];

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		if(status != HAL_OK)
		{
			driver_SX1280_cs_low(hwirelessmodule);
			return status;
		}

		status = HAL_SPI_Receive(hwirelessmodule->spi_handler, tmp_data, sizeof(tmp_data), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		memcpy(Rx_payload_length, tmp_data, 1);
		memcpy(Rx_start_buffer_pointer, tmp_data + 1, 1);

		return status;
}

/**
* @brief Retrieve information about the last received packet.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param packet_status1:	For BLE, GFSKand FLRC: 			"RFU".
* 							For LoRa® and Ranging Engine: 	"rssiSync".
*
* @param packet_status2:	For BLE, GFSKand FLRC: 			"rssiSync".
* 							For LoRa® and Ranging Engine: 	"snr".
*
* @param packet_status3:	For BLE, GFSKand FLRC: 			"errors".
* 							For LoRa® and Ranging Engine: 	"not used".
*
* @param packet_status4:	For BLE, GFSKand FLRC: 			"status".
* 							For LoRa® and Ranging Engine: 	"not used".
*
* @param packet_status5:	For BLE, GFSKand FLRC: 			"sync".
* 							For LoRa® and Ranging Engine: 	"not used".
*
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_get_packet_status(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *packet_status1, uint8_t *packet_status2,
		uint8_t *packet_status3, uint8_t *packet_status4, uint8_t *packet_status5)
{
	HAL_StatusTypeDef status = HAL_OK;

	// SX1280_CMD_GET_PACKET_STATUS 8bit | receive packetStatus 40b
	uint8_t command[2];
	command[0] = SX1280_CMD_GET_PACKET_STATUS;
	command[1] = SX1280_NOP;

	uint8_t tmp_data[5];

	driver_SX1280_cs_high(hwirelessmodule);
	status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
	if(status != HAL_OK)
	{
		driver_SX1280_cs_low(hwirelessmodule);
		return status;
	}

	status = HAL_SPI_Receive(hwirelessmodule->spi_handler, tmp_data, sizeof(tmp_data), hwirelessmodule->timeout);
	driver_SX1280_cs_low(hwirelessmodule);

	memcpy(packet_status1, tmp_data, 1);
	memcpy(packet_status2, tmp_data + 1, 1);
	memcpy(packet_status3, tmp_data + 2, 1);
	memcpy(packet_status4, tmp_data + 3, 1);
	memcpy(packet_status5, tmp_data + 4, 1);

	return status;
}

/**
* @brief Get instantaneous RSSI value during reception of the packet.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param rssi_inst:			pointer to rssi inst variable.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_get_rssi_inst(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *rssi_inst)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_GET_RSSI_LNST 8bit | received rssi_inst 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_GET_RSSI_LNST;
		command[1] = SX1280_NOP;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		if(status != HAL_OK)
		{
			driver_SX1280_cs_low(hwirelessmodule);
			return status;
		}

		status = HAL_SPI_Receive(hwirelessmodule->spi_handler, rssi_inst, sizeof(uint8_t), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Enable IRQs and to route IRQs to DIO pins.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param irq_mask:			IRQ mask.
* @param dio1_mask:			DIO 1 mask.
* @param dio2_mask:			DIO 2 mask.
* @param dio3_mask:			DIO 3 mask.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_dio_irq_params(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t irq_mask, uint16_t dio1_mask, uint16_t dio2_mask, uint16_t dio3_mask)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_SLEEP 8bit | irq_mask 16b | dio1_mask 16b | dio2_mask 16b | dio3_mask 16b
		uint8_t command[9];
		command[0] = SX1280_CMD_SET_DIO_IRQ_PARAMS;

		command[1] = (irq_mask & 0xFF00) >> 8;
		command[2] = irq_mask & 0x00FF;

		command[3] = (dio1_mask & 0xFF00) >> 8;
		command[4] = dio1_mask & 0x00FF;

		command[5] = (dio2_mask & 0xFF00) >> 8;
		command[6] = dio2_mask & 0x00FF;

		command[7] = (dio3_mask & 0xFF00) >> 8;
		command[8] = dio3_mask & 0x00FF;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Get the value of the IRQ register.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param lrq_status:		pointer to IRQ status variable.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_get_irq_status(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t *irq_status)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_GET_LRQ_STATUS 8bit | receive lrq_status 16b
		uint8_t command[2];
		command[0] = SX1280_CMD_GET_IRQ_STATUS;
		command[1] = SX1280_NOP;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		if(status != HAL_OK)
		{
			driver_SX1280_cs_low(hwirelessmodule);
			return status;
		}

		status = HAL_SPI_Receive(hwirelessmodule->spi_handler, (uint8_t *) irq_status, sizeof(irq_status), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Clear the IRQ register.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param lrq_status:		IRQ mask.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_clear_irq_status(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t irq_mask)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_CLEAR_IRQ_STATUS 8bit | irq_mask 16b
		uint8_t command[3];
		command[0] = SX1280_CMD_CLEAR_IRQ_STATUS;
		command[1] = (irq_mask & 0xFF00) >> 8;
		command[2] = irq_mask & 0x00FF;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the regulator mode. By default the LDO is enabled.
* @param hwirelessmodule: 		Pointer to a wireless_module_HandleTypeDef structure that contains
*                				informations for the specified wireless connection.
* @param regulator_mode_param:	regulator mode parameter :
* 								0: Only LDO used for all modes.
* 								1: DC-DC used for STDBY_XOSC, FS, Rx and Tx modes. LDO used for STDBY_RC.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_regulator_mode(module_wireless_HandleTypeDef *hwirelessmodule, bool regulator_mode_param)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_REGULATOR_MODE 8bit | regulator_mode_param 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_REGULATOR_MODE;
		command[1] = regulator_mode_param;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set perf counter mode (no description available in datasheet).
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param UART_speed:		perf counter mode select.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_perf_counter_mode(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t perf_counter_mode)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_PERF_COUNTER_MODE 8bit | standby_config 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_PERF_COUNTER_MODE;
		command[1] = perf_counter_mode;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the UART communication speed (no description available in datasheet).
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param UART_speed:		UART data speed.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_UART_speed(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t UART_speed)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_UART_SPEED 8bit | standby_config 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_UART_SPEED;
		command[1] = UART_speed;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Set the role of the SX1280 in ranging operation.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param ranging_role:		Ranging role (slave or master).
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_ranging_role(module_wireless_HandleTypeDef *hwirelessmodule, SX1280_RANGING_ROLE ranging_role)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_RANGING_ROLE 8bit | ranging_role 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_RANGING_ROLE;
		command[1] = ranging_role;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}

/**
* @brief Enable or disable the advanced ranging mode.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param enable:			enable or disable.
* @retval HAL status
*/
HAL_StatusTypeDef driver_SX1280_set_advanced_ranging_mode(module_wireless_HandleTypeDef *hwirelessmodule, bool enable)
{
	HAL_StatusTypeDef status = HAL_OK;

		// SX1280_CMD_SET_ADVENCED_RANGING 8bit | enable 8b
		uint8_t command[2];
		command[0] = SX1280_CMD_SET_ADVANCED_RANGING;
		command[1] = enable;

		driver_SX1280_cs_high(hwirelessmodule);
		status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, command, sizeof(command), hwirelessmodule->timeout);
		driver_SX1280_cs_low(hwirelessmodule);

		return status;
}



