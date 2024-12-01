/**
  ******************************************************************************
  * @file           : driver_NRF24L01.c
  * @brief          : NRF24L01 driver functions.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-11-27 gael fargeas created
  *
  */

/* Includes ---------------------------------------------------------*/
#include "driver_NRF24L01.h"

/* Functions --------------------------------------------------------*/
/**
* @brief Set the CS GPIO to high.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_cs_high(module_wireless_HandleTypeDef *hwirelessmodule)
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
HAL_StatusTypeDef driver_NRF24L01_cs_low(module_wireless_HandleTypeDef *hwirelessmodule)
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

/**
* @brief NRF24L01 initialization.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param template_selected: Template selected.
* @param mode:				NRF24L01 module mode (RX or TX).
* @param freq_MHz:			NRF24L01 module signal frequency.
* @param data_rate:			NRF24L01 module data rate.
* @param power:				NRF24L01 module signal power.
* @param crc_lenght:		NRF24L01 module data CRC lenght.
* @param address_width:		NRF24L01 module data lenght.
* @param retr_count:		NRF24L01 module data automatic retransmission count.
* @param retr_delay:		NRF24L01 module data automatic retransmission delay.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_init(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_MODE_RX_TX mode, uint16_t freq_MHz,
		NRF24L01_RF_SETUP_DATA_RATE data_rate, NRF24L01_RF_SETUP_POWER power, NRF24L01_CRC_LENGHT crc_length,
		NRF24L01_ADDRESS_WIDTH address_width, NRF24L01_RETR_COUNT retr_count, NRF24L01_RETR_DELAY retr_delay)
{
	HAL_StatusTypeDef status = HAL_OK;

	driver_NRF24L01_reset(hwirelessmodule);

	switch (mode) {
		case RF24L01_TX_MODE:
			driver_NRF24L01_set_ptx_mode(hwirelessmodule);
			driver_NRF24L01_power_up(hwirelessmodule);
			break;

		case RF24L01_RX_MODE:
			driver_NRF24L01_set_prx_mode(hwirelessmodule);
			driver_NRF24L01_power_up(hwirelessmodule);
			driver_NRF24L01_rx_set_payload_0_widths(hwirelessmodule, hwirelessmodule->payload_length);

			break;
		default:
			break;
	}

	driver_NRF24L01_set_rf_channel(hwirelessmodule, freq_MHz);
	driver_NRF24L01_set_rf_setup_air_data_rate(hwirelessmodule, data_rate);
	driver_NRF24L01_set_rf_setup_tx_output_power(hwirelessmodule, power);

	driver_NRF24L01_set_crc_length(hwirelessmodule, crc_length);
	driver_NRF24L01_set_address_widths(hwirelessmodule, address_width);

	driver_NRF24L01_auto_retransmit_count(hwirelessmodule, retr_count);
	driver_NRF24L01_auto_retransmit_delay(hwirelessmodule, retr_delay);

	return status;
}

/**
* @brief Write data to a register.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param reg:		Register address to be write.
* @param value:		Pointer to the data to write.
* @param data_size:	Size of "value".
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_write_register(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t reg, uint8_t *value, uint8_t value_size)
{
	uint8_t command = NRF24L01_CMD_WRITE_REGISTER | reg;
	uint8_t status;
	HAL_StatusTypeDef ret_status = HAL_OK;

	driver_NRF24L01_cs_low(hwirelessmodule);

	ret_status = HAL_SPI_TransmitReceive(hwirelessmodule->spi_handler, &command, &status, sizeof(status), hwirelessmodule->timeout);
	if(ret_status != HAL_OK)
	{
		return ret_status;
	}

	ret_status = HAL_SPI_Transmit(hwirelessmodule->spi_handler, value, value_size, hwirelessmodule->timeout);

	driver_NRF24L01_cs_high(hwirelessmodule);

	if(ret_status != HAL_OK)
	{
		return ret_status;
	}

	return ret_status;
}

/**
* @brief Read data from a register.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param reg:		Register address to be read.
* @param data:		Pointer to the data to read.
* @param data_size:	Size of "data".
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_read_register(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t reg, uint8_t *data, uint8_t data_size)
{
    uint8_t command = NRF24L01_CMD_READ_REGISTER | reg;
    uint8_t status;
    HAL_StatusTypeDef ret_status = HAL_OK;

	driver_NRF24L01_cs_low(hwirelessmodule);

	ret_status = HAL_SPI_TransmitReceive(hwirelessmodule->spi_handler, &command, &status, sizeof(status), hwirelessmodule->timeout);
	if(ret_status != HAL_OK)
	{
		return ret_status;
	}

	ret_status = HAL_SPI_Receive(hwirelessmodule->spi_handler, data, data_size, hwirelessmodule->timeout);

	driver_NRF24L01_cs_high(hwirelessmodule);

	if(ret_status != HAL_OK)
	{
		return ret_status;
	}

	return ret_status;
}

/**
* @brief Reset NRF24L01 (set register to default values).
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_reset(module_wireless_HandleTypeDef *hwirelessmodule)
{
	HAL_StatusTypeDef status = HAL_OK;

	driver_NRF24L01_cs_low(hwirelessmodule);
	driver_NRF24L01_cs_high(hwirelessmodule);

	// Set registers to default value
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_CONFIG, (uint8_t *) 0x08, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_EN_AA, (uint8_t *) 0x3F, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_EN_RXADDR, (uint8_t *) 0x03, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_SETUP_AW, (uint8_t *) 0x03, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_SETUP_RETR, (uint8_t *) 0x03, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RF_CH, (uint8_t *) 0x02, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RF_SETUP, (uint8_t *) 0x07, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_STATUS, (uint8_t *) 0x7E, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P0, (uint8_t *) 0x00, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P0, (uint8_t *) 0x00, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P1, (uint8_t *) 0x00, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P2, (uint8_t *) 0x00, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P3, (uint8_t *) 0x00, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P4, (uint8_t *) 0x00, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P5, (uint8_t *) 0x00, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_FIFO_STATUS, (uint8_t *) 0x11, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_DYNPD, (uint8_t *) 0x00, sizeof(uint8_t));
	driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_FEATURE, (uint8_t *) 0x00, sizeof(uint8_t));

	return status;
}

/**
* @brief Flush RX fifo register.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_flush_rx_fifo(module_wireless_HandleTypeDef *hwirelessmodule)
{
    uint8_t command = NRF24L01_CMD_FLUSH_RX;
    uint8_t status;
    HAL_StatusTypeDef ret_status = HAL_OK;

	driver_NRF24L01_cs_low(hwirelessmodule);
	ret_status = HAL_SPI_TransmitReceive(hwirelessmodule->spi_handler, &command, &status, 1, hwirelessmodule->timeout);
	driver_NRF24L01_cs_high(hwirelessmodule);

	if(status == 0)
	{
		return HAL_ERROR;
	}

	return ret_status;
}

/**
* @brief Flush TX fifo register.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_flush_tx_fifo(module_wireless_HandleTypeDef *hwirelessmodule)
{
    uint8_t command = NRF24L01_CMD_FLUSH_TX;
    uint8_t status;
    HAL_StatusTypeDef ret_status = HAL_OK;

    driver_NRF24L01_cs_low(hwirelessmodule);
    ret_status = HAL_SPI_TransmitReceive(hwirelessmodule->spi_handler, &command, &status, 1, hwirelessmodule->timeout);
    driver_NRF24L01_cs_high(hwirelessmodule);

    if(status == 0)
    {
    	return HAL_ERROR;
    }

    return ret_status;

}

/**
* @brief Set the CRC length.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param crc_lenght:		NRF24L01 module data CRC lenght.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_set_crc_length(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_CRC_LENGHT crc_length)
{
	// Check bytes value
	if(crc_length > 1)
	{
		return HAL_ERROR;
	}

	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	switch (crc_length) {
		case RF24L01_CRC_1_BYTE:
			config &= 0xFB ; // 0b1111 1011
			break;
		case RF24L01_CRC_2_BYTES:
			config |= 1 << 2;
			break;
		default:
			return HAL_ERROR;
			break;
	}

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Power up NRF24L01.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_power_up(module_wireless_HandleTypeDef *hwirelessmodule)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	config |= 0b10;

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Power down NRF24L01.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_power_down(module_wireless_HandleTypeDef *hwirelessmodule)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	config &= 0xFD; // 0b1111 1101

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Set NRF24L01 in Rx mode.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_set_prx_mode(module_wireless_HandleTypeDef *hwirelessmodule)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	config |= 1;

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Set NRF24L01 in Tx mode.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_set_ptx_mode(module_wireless_HandleTypeDef *hwirelessmodule)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	config &= 0xFE; // 0b1111 1110

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_CONFIG, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Write data in Tx fifo.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param tx_payload:	Pointer to the data to send.
* @param payload_size:	Size amount of data to be send.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_write_tx_fifo(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *tx_payload, uint8_t payload_size)
{
	return driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_CMD_WRITE_TX_PAYLOAD, tx_payload, payload_size);
}

/**
* @brief Read data from Rx fifo
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param rx_payload:	Pointer to the data to read.
* @param payload_size:	Size amount of data to be received.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_read_rx_fifo(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *rx_payload, uint8_t payload_size)
{
	return driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_CMD_READ_RX_PAYLOAD, rx_payload, payload_size);
}

/**
* @brief Get NRF24L01 status.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param data:		Pointer to data buffer.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_get_status(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data)
{
	return driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_CMD_NOP, data, sizeof(uint8_t));
}

/**
* @brief Set NRF24L01 address width.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                			informations for the specified wireless connection.
* @param address_width:		NRF24L01 module data lenght.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_set_address_widths(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_ADDRESS_WIDTH address_width)
{
	return driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_SETUP_AW, &address_width, sizeof(uint8_t));
}

/**
* @brief Set NRF24L01 automatic retransmission.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param count:			NRF24L01 module data automatic retransmission count.
* @param delay:			NRF24L01 module data automatic retransmission delay.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_auto_retransmit(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RETR_DELAY delay, NRF24L01_RETR_COUNT count)
{
	uint8_t value = ((delay << 4) + count);
	return driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_SETUP_RETR, &value , sizeof(uint8_t));
}

/**
* @brief Set NRF24L01 automatic retransmission: delay only.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param delay:			NRF24L01 module data automatic retransmission delay.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_auto_retransmit_delay(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RETR_DELAY delay)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_SETUP_RETR, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	config &= 0x0F;
	config |= delay << 4;

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_SETUP_RETR, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Set NRF24L01 automatic retransmission: count only.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param count:			NRF24L01 module data automatic retransmission count.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_auto_retransmit_count(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RETR_COUNT count)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_SETUP_RETR, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	config &= 0xF0;
	config |= count;

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_SETUP_RETR, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Set NRF24L01 signal frequency.
* @param hwirelessmodule: 	Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param freq_MHz:			NRF24L01 module signal frequency.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_set_rf_channel(module_wireless_HandleTypeDef *hwirelessmodule, uint16_t freq_MHz)
{
	HAL_StatusTypeDef status = HAL_OK;

	uint16_t frequency = freq_MHz - 2400;

	if(frequency > 255)
	{
		return HAL_ERROR;
	}
	uint8_t tmp_freq = (uint8_t) frequency;
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RF_CH, &tmp_freq, sizeof(uint8_t));

	return status;
}

/**
* @brief Set NRF24L01 signal data setup.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param enable:			Enable NRF24L01 module continuous carrier signal.
* @param data_rate:			NRF24L01 module data rate.
* @param power:				NRF24L01 module signal power.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_set_rf_setup(module_wireless_HandleTypeDef *hwirelessmodule, bool enable, NRF24L01_RF_SETUP_DATA_RATE data_rate, NRF24L01_RF_SETUP_POWER power)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Change config
	config |= (enable << 7);

	switch (data_rate) {
		case RF24L01_RF_SETUP_DATA_RATE_1MBPS:
			break;
		case RF24L01_RF_SETUP_DATA_RATE_2MBPS:
			config |= 0b1 << 3;
			break;
		case RF24L01_RF_SETUP_DATA_RATE_250KBPS:
			config |= 0b1 << 5;
			break;

		default:
			return HAL_ERROR;
			break;
	}

	config |= (power << 1);

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RF_SETUP, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Set NRF24L01 signal data setup; continuous carrier signal.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param enable:			Enable NRF24L01 module continuous carrier signal.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_set_rf_setup_continuous_carrier (module_wireless_HandleTypeDef *hwirelessmodule, bool enable)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_RF_SETUP, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	config &= 0x7F; // 0b0111 1111
	config |= (enable << 7);

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RF_SETUP, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Set NRF24L01 signal data setup: data rate.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection..
* @param data_rate:			NRF24L01 module data rate.
*
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_set_rf_setup_air_data_rate(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RF_SETUP_DATA_RATE data_rate)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_RF_SETUP, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	config &= 0xD7; // 0b1101 0111

	switch (data_rate) {
		case RF24L01_RF_SETUP_DATA_RATE_1MBPS:
			break;
		case RF24L01_RF_SETUP_DATA_RATE_2MBPS:
			config |= 0b1 << 3;
			break;
		case RF24L01_RF_SETUP_DATA_RATE_250KBPS:
			config |= 0b1 << 5;
			break;

		default:
			return HAL_ERROR;
			break;
	}


	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RF_SETUP, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Set NRF24L01 signal data setup: output power.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param power:				NRF24L01 module signal power.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_set_rf_setup_tx_output_power(module_wireless_HandleTypeDef *hwirelessmodule, NRF24L01_RF_SETUP_POWER power)
{
	uint8_t config = 0;
	HAL_StatusTypeDef status = HAL_OK;

	// Get config
	status = driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_RF_SETUP, &config, sizeof(uint8_t));
	if(status != HAL_OK)
	{
		return status;
	}

	// Change config
	config &= 0xF9; // 0b1111 1001
	config |= (power << 1);

	// Set new config
	status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RF_SETUP, &config, sizeof(uint8_t));

	return status;
}

/**
* @brief Clear maximum number of TX retransmits interrupt.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_clear_max_rt(module_wireless_HandleTypeDef *hwirelessmodule)
{
	uint8_t data = 0;
	HAL_StatusTypeDef ret_status = HAL_OK;

	// Get status
	ret_status = driver_NRF24L01_get_status(hwirelessmodule, &data);
	if(ret_status != HAL_OK)
	{
		return ret_status;
	}

	// Change status
	data |= 0x10;

	// Write new status
	ret_status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_STATUS, &data, sizeof(uint8_t));

	return ret_status;

}

/**
* @brief Clear data Sent TX FIFO interrupt.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_clear_tx_ds(module_wireless_HandleTypeDef *hwirelessmodule)
{
	uint8_t data = 0;
	HAL_StatusTypeDef ret_status = HAL_OK;

	// Get status
	ret_status = driver_NRF24L01_get_status(hwirelessmodule, &data);
	if(ret_status != HAL_OK)
	{
		return ret_status;
	}

	// Change status
	data |= 0x20;

	// Write new status
	ret_status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_STATUS, &data, sizeof(uint8_t));

	return ret_status;
}

/**
* @brief clear Data Ready RX FIFO interrupt.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_clear_rx_dr(module_wireless_HandleTypeDef *hwirelessmodule)
{
	uint8_t data = 0;
	HAL_StatusTypeDef ret_status = HAL_OK;

	// Get status
	ret_status = driver_NRF24L01_get_status(hwirelessmodule, &data);
	if(ret_status != HAL_OK)
	{
		return ret_status;
	}

	// Change status
	data |= 0x40;

	// Write new status
	ret_status = driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_STATUS, &data, sizeof(uint8_t));

	return ret_status;
}

/**
* @brief Set Rx payload width for data pipe 0.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param bytes:				 data pipe 0 payload width.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_0_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes)
{
	return driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P0, &bytes, sizeof(uint8_t));
}

/**
* @brief Set Rx payload width for data pipe 1.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param bytes:				 data pipe 1 payload width.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_1_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes)
{
	return driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P1, &bytes, sizeof(uint8_t));
}

/**
* @brief Set Rx payload width for data pipe 2.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param bytes:				 data pipe 2 payload width.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_2_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes)
{
	return driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P2, &bytes, sizeof(uint8_t));
}

/**
* @brief Rx payload width for data pipe 3.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param bytes:				 data pipe 3 payload width.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_3_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes)
{
	return driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P3, &bytes, sizeof(uint8_t));
}

/**
* @brief Rx payload width for data pipe 4.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param bytes:				 data pipe 4 payload width.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_4_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes)
{
	return driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P4, &bytes, sizeof(uint8_t));
}

/**
* @brief Rx payload width for data pipe 5.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param bytes:				 data pipe 5 payload width.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_rx_set_payload_5_widths(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t bytes)
{
	return driver_NRF24L01_write_register(hwirelessmodule, NRF24L01_REG_RX_PW_P5, &bytes, sizeof(uint8_t));
}

/**
* @brief Get NRF24L01 fifo status.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param status:			Pointer to data buffer.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_get_fifo_status(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *status)
{
	return driver_NRF24L01_read_register(hwirelessmodule, NRF24L01_REG_FIFO_STATUS, status, sizeof(uint8_t));
}

/**
* @brief send data.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param data:			pointer to data buffer.
* @param data_size:		Size amount of data to be send.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_send_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data, uint8_t data_size)
{
	return driver_NRF24L01_write_tx_fifo(hwirelessmodule, data, data_size);
}

/**
* @brief receive data.
* @param hwirelessmodule: Pointer to a wireless_module_HandleTypeDef structure that contains
*                	informations for the specified wireless connection.
* @param data:	 		pointer to data buffer.
* @param data_size:		Size amount of data to be received.
* @retval HAL status
*/
HAL_StatusTypeDef driver_NRF24L01_receice_data(module_wireless_HandleTypeDef *hwirelessmodule, uint8_t *data, uint8_t data_size)
{
	return driver_NRF24L01_read_rx_fifo(hwirelessmodule, data, data_size);
}
