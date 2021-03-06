#include <stdint.h>
#include "stm32f1xx_hal_conf.h"
#include "stm32f1xx_hal.h"
#include "timer_counter.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

extern "C" {
volatile uint8_t freeRTOSMemoryScheme = configUSE_HEAP_SCHEME;
}

#if ( configGENERATE_RUN_TIME_STATS	== 1 )
extern McHardwareInterfacesImplementation::TimCounter			timRunTimeStats;
#endif

extern "C" {

void* malloc(size_t size) {
    return pvPortMalloc(size);
}

void* calloc(size_t num, size_t size) {
    return pvPortMalloc(num * size);
}

void free(void* ptr) {
    return vPortFree(ptr);
}

void* operator new(size_t sz) {
    return pvPortMalloc(sz);
}

void* operator new[](size_t sz) {
    return pvPortMalloc(sz);
}

void operator delete(void* p) {
    vPortFree(p);
}

void operator delete[](void* p) {
    vPortFree(p);
}

void operator delete( void* p, size_t size ) {
	( void )size;
    vPortFree(p);
}

void operator delete[]( void* p, size_t size ) {
	( void )size;
    vPortFree(p);
}

void vApplicationMallocFailedHook( void ) {
	while(1);
}

void vApplicationStackOverflowHook ( void ) {
	while(1);
}

#if ( configGENERATE_RUN_TIME_STATS	== 1 )

void vConfigureTimerForRunTimeStats ( void ) {
	/// Таймер настроится при конфигурации RCC внутри AyPlayer.
}

uint32_t vGetRunTimeCounterValue ( void ) {
	return timRunTimeStats.getCounter();
}

#endif

void prvGetRegistersFromStack ( uint32_t *pulFaultStackAddress ) {
	__attribute__((unused)) volatile uint32_t r0;
	__attribute__((unused)) volatile uint32_t r1;
	__attribute__((unused)) volatile uint32_t r2;
	__attribute__((unused)) volatile uint32_t r3;
	__attribute__((unused)) volatile uint32_t r12;
	__attribute__((unused)) volatile uint32_t lr; 		/// Link register.
	__attribute__((unused)) volatile uint32_t pc;		/// Program counter.
	__attribute__((unused)) volatile uint32_t psr;		/// Program status register.

	r0	=	pulFaultStackAddress[ 0 ];
	r1	=	pulFaultStackAddress[ 1 ];
	r2	=	pulFaultStackAddress[ 2 ];
	r3	=	pulFaultStackAddress[ 3 ];

	r12	=	pulFaultStackAddress[ 4 ];
	lr	=	pulFaultStackAddress[ 5 ];
	pc	=	pulFaultStackAddress[ 6 ];
	psr	=	pulFaultStackAddress[ 7 ];

	for( ;; );
}


}
