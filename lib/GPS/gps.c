#include "gps.h"
#include "logging.h"
#include "stm32l4xx_hal.h"
#include <string.h>

void send_uart(UART_HandleTypeDef huart, char *str)
{
    HAL_UART_Transmit(&huart, (uint8_t *)str, strlen(str), 100);
    HAL_Delay(50);
}

bool process_nmea_sentence(const char *sentence, struct minmea_sentence_gga *frame)
{
    if ( minmea_sentence_id(sentence, false) != MINMEA_SENTENCE_GGA )
    {
        LogMessage_t x_log = {35U, "ERROR: Only GGA mode is supported\r\n"};
        xQueueSend(x_log_queue, &x_log, portMAX_DELAY);
        return false;
    }
    if ( !minmea_parse_gga(frame, sentence) )
    {
        LogMessage_t x_log = {37U, "ERROR: Failed to parse GGA sentence\r\n"};
        xQueueSend(x_log_queue, &x_log, portMAX_DELAY);
        return false;
    }
    return true;
}
