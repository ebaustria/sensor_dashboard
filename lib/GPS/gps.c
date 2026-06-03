#include "gps.h"
#include "stm32l4xx_hal.h"

void send_uart(UART_HandleTypeDef huart, char *str)
{
    HAL_UART_Transmit(&huart, (uint8_t *)str, (uint16_t)sizeof(str), 100);
    HAL_Delay(50);
}