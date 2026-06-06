#ifndef __GPS_H
#define __GPS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "minmea.h"
#include "stm32l4xx_hal_dma.h"
#include "stm32l4xx_hal_uart.h"

#define PMTK_API_SET_FIX_CTL_5HZ "$PMTK300,200,0,0,0,0*2F\r\n"

#define PMTK_SET_BAUD_9600 "$PMTK251,9600*17\r\n"
#define PMTK_SET_NMEA_OUTPUT_GGA "$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n"

#define PMTK_Q_RELEASE "$PMTK605*31\r\n"

#define PGCMD_ANTENNA "$PGCMD,33,1*6C\r\n"

    void send_uart(UART_HandleTypeDef huart, char *str);
    bool process_nmea_sentence(const char *sentence, struct minmea_sentence_gga *frame);

#ifdef __cplusplus
}
#endif

#endif /* __GPS_H */