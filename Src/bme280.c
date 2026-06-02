#include "bme280.h"
#include "stm32l4xx_hal.h"
#include "logging.h"

bool reset_bme280(void)
{
	HAL_StatusTypeDef status;
	uint8_t data = 0xB6;
	status = HAL_I2C_Mem_Write(&hi2c1, BME280_ADDR, RESET_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &data, 1, 1000);
	HAL_Delay(500);

	//Checking for is reset process done
	uint8_t id;
	status = HAL_I2C_Mem_Read(&hi2c1, BME280_ADDR, CHIP_ID_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &id, 1, 1000);

	return id == BME280_CHIP_ID;
}

/**
  * @brief  Puts the BME280 into sleep mode
  *
  * @param  None
  *
  * @retval None
  */
HAL_StatusTypeDef sleep_mode_bme280(void)
{
	uint8_t init = 0;
	init = BME280_SLEEP_MODE;

	return HAL_I2C_Mem_Write(&hi2c1, BME280_ADDR, CTRL_MEAS_REG_ADDR, 1, &init, 1, 1000);

}

/**
  * @brief  Initialization of BME280
  *
  * @retval None
  */
void configure_bme280(void)
{
	HAL_StatusTypeDef hal_status = HAL_ERROR;
	uint8_t init = 0;

	// Setting it to sleep mode because the config register can only be changed while the BME280 is in sleep mode
	hal_status = sleep_mode_bme280();
	if (hal_status == HAL_OK)
	{

		// printf("BME280 was put into sleep mode so that the config register could be set.!\n");
		// Configuration of config register, which controls standby time, filter coefficient, and 3-wire SPI interface
		init = ((0x5 << 5) | (0x0 << 2) | (0x0 << 0));
		HAL_I2C_Mem_Write(&hi2c1, BME280_ADDR, CONFIG_REG_ADDR, 1, &init, 1, 1000);
		HAL_Delay(100);
		init = 0;
	}

	// Configuration of ctrl_hum register, which controls humidity oversampling
	init = ((0x1 << 0) & 0x7);
	HAL_I2C_Mem_Write(&hi2c1, BME280_ADDR, CTRL_HUM_REG_ADDR, 1, &init, 1, 1000);
	HAL_Delay(100);
	init = 0;

	// Configuration of ctrl_meas register, which controls temperature oversampling, pressure oversampling, and device mode
	init = (0x1 << 5) | (0x1 << 2) | 0x1;
	HAL_I2C_Mem_Write(&hi2c1, BME280_ADDR, CTRL_MEAS_REG_ADDR, 1, &init, 1, 1000);
	HAL_Delay(100);
	init = 0;

	// printf("BME280 Initialization process is done!\n");
}