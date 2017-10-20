#include "main.h"
#include "stm32f1xx_hal_conf.h"
#include "balance_motionsensor.h"
#include "mpu6050.h"

float a[3];
float g[3];
extern mpu6050_t *imu;

void housekeeping_thread ( void* p_arg ) {
    (void)p_arg;
    while( true ) {
        USER_OS_DELAY_MS(100);
        mpu6050_getData(imu, a, g);
    }
}

void int_pin(void){
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef cfg;
    cfg.Pin = GPIO_PIN_0;
    cfg.Mode = GPIO_MODE_IT_FALLING;
    cfg.Pull = GPIO_NOPULL;
    cfg.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB,&cfg);
    HAL_NVIC_SetPriority(EXTI0_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void i2c_pins(void){
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef cfg;
    cfg.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    cfg.Mode = GPIO_MODE_AF_OD;
    cfg.Pull = GPIO_NOPULL;
    cfg.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &cfg);
    __HAL_RCC_I2C1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
}



void hardware_init(void){
    int_pin();
    i2c_pins();
}



#define TB_HOUSEKEEPING_SIZE           500
USER_OS_STATIC_TASK_STRUCT_TYPE         ts_housekeeping;
USER_OS_STATIC_STACK_TYPE               tb_housekeeping             [ TB_HOUSEKEEPING_SIZE ];

extern "C" {

int main (void){
    hardware_init();
    balance_motionsensor_init();
    USER_OS_STATIC_TASK_CREATE( housekeeping_thread, "hous", TB_HOUSEKEEPING_SIZE, NULL, 1, tb_housekeeping, &ts_housekeeping );
    vTaskStartScheduler();
    while ( true ) {};
}

}
