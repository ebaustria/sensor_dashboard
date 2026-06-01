#ifndef __BME_280_H
#define __BME_280_H

#include <stdint.h>
#include "stm32l4xx_hal_def.h"
#include "stm32l4xx_hal_dma.h"
#include "stm32l4xx_hal_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

extern I2C_HandleTypeDef hi2c1;

#define BME280_ADDR 			    0x76
#define BME280_CHIP_ID 				0x60

#define CONFIG_REG_ADDR 			0xF5
#define CTRL_MEAS_REG_ADDR 			0xF4

#define CTRL_HUM_REG_ADDR 			0xF2

/*
 * Sensor mode macros
 */
#define BME280_SLEEP_MODE  			0x0
#define BME280_FORCED_MODE 			0x1
#define BME280_NORMAL_MODE 			0x3

/**
  * BME280 config structure definition
  */
typedef struct
{
	uint8_t over_sampling_t;
	uint8_t over_sampling_p;
	uint8_t over_sampling_h;
	uint8_t mode;
	uint8_t t_standby;
	uint8_t filter;
	uint8_t spi;
} BME280_Config_t;

HAL_StatusTypeDef sleep_mode_bme280(void);
void configure_bme280();

#ifdef __cplusplus
}
#endif

#endif /* __BME_280_H */
