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
    __HAL_RCC_I2C1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef cfg;
    cfg.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    cfg.Mode = GPIO_MODE_AF_OD;
    cfg.Pull = GPIO_NOPULL;
    cfg.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &cfg);
    int_pin();
}

int getImuDataSync(float *accArry, float *gyroArray){
    float acc[3], gyro[3];
    if(!mpu6050_getDataSync(imu, acc, gyro)){
        memcpy(accArry, acc, sizeof(acc));
        memcpy(gyroArray, gyro, sizeof(gyro));
        return 0;
    }
    return 1;
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
    HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
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

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c){
    (void)hi2c;
    BaseType_t xHigherPriorityTaskWoken = 0;

    xSemaphoreGiveFromISR (imu->i2c->semaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR (xHigherPriorityTaskWoken);
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c){
     (void)hi2c;
    BaseType_t xHigherPriorityTaskWoken = 0;

    xSemaphoreGiveFromISR (imu->i2c->semaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR (xHigherPriorityTaskWoken);
}
}
