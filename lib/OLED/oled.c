#include "oled.h"
#include "FreeRTOS.h"
#include "minmea.h"
#include "stm32l4xx_hal_dma.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_spi.h"
#include "task.h"
#include "u8g2.h"
#include <stdio.h>

extern SPI_HandleTypeDef hspi2;
extern u8g2_t u8g2;

uint8_t u8x8_gpio_and_delay_stm32(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch ( msg )
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT:
            break;

        case U8X8_MSG_DELAY_MILLI:
            vTaskDelay(pdMS_TO_TICKS(arg_int));
            break;

        case U8X8_MSG_GPIO_DC:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, arg_int ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;

        case U8X8_MSG_GPIO_RESET:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, arg_int ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;
    }
    return 1;
}

uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch ( msg )
    {
        case U8X8_MSG_BYTE_SEND:
            HAL_SPI_Transmit(&hspi2, (uint8_t *)arg_ptr, arg_int, HAL_MAX_DELAY);
            break;

        case U8X8_MSG_BYTE_INIT:
            break;

        case U8X8_MSG_BYTE_SET_DC:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, arg_int ? GPIO_PIN_SET : GPIO_PIN_RESET);
            break;

        case U8X8_MSG_BYTE_START_TRANSFER:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
            break;

        case U8X8_MSG_BYTE_END_TRANSFER:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
            break;
    }
    return 1;
}

void init_oled()
{
    u8g2_Setup_ssd1327_ws_128x128_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_spi, u8x8_gpio_and_delay_stm32);

    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_courR08_tr);
    u8g2_SendBuffer(&u8g2);
}

void update_oled(struct minmea_sentence_gga *x_received_frame)
{
    char coord_buf[32U];
    char time_buf[32U];
    char alt_buf[32U];

    struct minmea_time time = x_received_frame->time;

    u8g2_ClearBuffer(&u8g2);

    float lat_degs = minmea_tocoord(&x_received_frame->latitude);
    float lon_degs = minmea_tocoord(&x_received_frame->longitude);

    snprintf(time_buf, sizeof(time_buf), "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);

    snprintf(coord_buf, sizeof(coord_buf), "%.4f, %.4f", lat_degs, lon_degs);
    snprintf(alt_buf, sizeof(alt_buf), "%.4f %c", minmea_tofloat(&x_received_frame->altitude),
             x_received_frame->altitude_units);

    u8g2_SetFont(&u8g2, u8g2_font_courR08_tr);

    u8g2_DrawStr(&u8g2, 5U, 15U, time_buf);
    u8g2_DrawStr(&u8g2, 25U, 32U, coord_buf);
    u8g2_DrawStr(&u8g2, 25U, 50U, alt_buf);

    // Globe icon
    u8g2_SetFont(&u8g2, u8g2_font_unifont_t_weather);
    u8g2_DrawGlyph(&u8g2, 5U, 35U, 32);

    // Mountain icon
    u8g2_SetFont(&u8g2, u8g2_font_unifont_t_77);
    u8g2_DrawGlyph(&u8g2, 5U, 50U, 9968);
}
