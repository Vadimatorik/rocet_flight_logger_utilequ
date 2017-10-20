/*
 * balance_motionsensor.c
 *
 *  Created on: 13 дек. 2015 г.
 *      Author: jdi
 */
#include "mpu6050.h"

mpu6050_t *imu;


port_i2c_initCfg_t i2c_cfg  = {
            .i2c_inst = I2C1,
    .speed = 100000,
    .dmaTx = NULL, //DMA1_Channel6,

            .dmaRx = NULL//DMA1_Channel7,
};


mpu6050_init_t cfg = {
    .i2c_cfg = &i2c_cfg,
    .thread_priority = 3,
    .period = 5
};

void balance_motionsensor_init(void){

    imu = mpu6050_init(&cfg);
     //HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 6, 0);
    //HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
 //   HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 6, 0);
  //  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
	HAL_NVIC_SetPriority(I2C1_EV_IRQn, 6, 0);
	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
}


//перывание по ноге  mpu6050  готовность данных
extern "C" {
void EXTI0_IRQHandler(void){
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
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
