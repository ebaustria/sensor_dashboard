#ifndef __LOGGING_H
#define __LOGGING_H

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        uint16_t us_length;
        char message[100];
    } LogMessage_t;

    extern QueueHandle_t x_log_queue;
    extern SemaphoreHandle_t x_dma_tx_complete_semaphore;

#ifdef __cplusplus
}
#endif

#endif /* __LOGGING_H */