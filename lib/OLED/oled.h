#ifndef __OLED_H
#define __OLED_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "u8x8.h"
#include "minmea.h"
#include <stdint.h>

    uint8_t u8x8_gpio_and_delay_stm32(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
    uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

    void init_oled();
    void update_oled(struct minmea_sentence_gga *x_received_frame);

#ifdef __cplusplus
}
#endif

#endif /* __OLED_H */