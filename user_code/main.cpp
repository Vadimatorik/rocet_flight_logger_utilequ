#include "main.h"

void housekeeping_thread ( void* p_arg ) {
    (void)p_arg;
    while( true ) {
        USER_OS_DELAY_MS(100);
     //   mpu6050_getData(imu, a, g);
    }
}

#define TB_HOUSEKEEPING_SIZE           500
USER_OS_STATIC_TASK_STRUCT_TYPE         ts_housekeeping;
USER_OS_STATIC_STACK_TYPE               tb_housekeeping             [ TB_HOUSEKEEPING_SIZE ];

extern "C" {

int main (void){
    rk_hardware_init();
    USER_OS_STATIC_TASK_CREATE( housekeeping_thread, "hous", TB_HOUSEKEEPING_SIZE, NULL, 1, tb_housekeeping, &ts_housekeeping );
    vTaskStartScheduler();
    while ( true ) {};
}

}
