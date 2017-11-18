#include "mpu6050.h"
#include <string.h>

mpu6050_t *imu = NULL;
//MPU6050_interapt
void int_pin(void){
//	__HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef cfg;
    cfg.Pin = GPIO_PIN_13;
    cfg.Mode = GPIO_MODE_IT_RISING;
    cfg.Pull = GPIO_NOPULL;
    cfg.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &cfg);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 7, 0);
}

void startImu(void){
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void i2c_pins(void){
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef cfg;
    cfg.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    cfg.Mode = GPIO_MODE_AF_OD;
    cfg.Pull = GPIO_NOPULL;
    cfg.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &cfg);
    int_pin();
}

char t_name[] = "imuThread";

mpu6050_init_t cfg = {
    .i2c_cfg = {
        .i2c_inst = I2C1,
        .speed = 100000,
        .dmaTx = DMA1_Channel6,
        .dmaRx = DMA1_Channel7,
    },
    .thread_name = t_name,
    .thread_priority = 3,
    .period = 5,
    .start = startImu
};


void balance_motionsensor_init(void){
    i2c_pins();

    imu = mpu6050_init(&cfg);
}

//перывание по ноге  mpu6050  готовность данных
extern "C" {
void EXTI15_10_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
    dataReadyIRQ(imu);
}

void I2C1_EV_IRQHandler(void){
     HAL_I2C_EV_IRQHandler(&imu->i2c->handle);
}

void DMA1_Channel6_IRQHandler(void){
    HAL_DMA_IRQHandler(imu->i2c->handle.hdmatx);
}

void DMA1_Channel7_IRQHandler(void){
    HAL_DMA_IRQHandler(imu->i2c->handle.hdmarx);
}

}
