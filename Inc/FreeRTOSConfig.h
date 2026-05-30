#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
 #include <stdint.h>
 extern uint32_t SystemCoreClock;
#endif

// TODO Check config args

#define vPortSVCHandler    SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#define configUSE_PREEMPTION 1

#define configUSE_TICK_HOOK 0
#define configUSE_IDLE_HOOK 1

#define configTICK_RATE_HZ						( 1000 )
#define configCPU_CLOCK_HZ						SystemCoreClock
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 16 * 1024 ) )

#define configUSE_16_BIT_TICKS 0

#define configMAX_PRIORITIES 5
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 0

#endif /* FREERTOS_CONFIG_H */