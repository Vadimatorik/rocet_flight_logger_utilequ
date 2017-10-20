/*
 * mpu6050.h
 *
 *  Created on: 06 дек. 2015 г.
 *      Author: jdi
 */
#include "port_i2c.h"


#ifndef MPU6050_H_
#define MPU6050_H_

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

#include "stdint.h"
#include "port_i2c.h"

typedef struct {
    port_i2c_initCfg_t* i2c_cfg;
	uint8_t thread_priority;
	int period;
}mpu6050_init_t;


typedef struct _mpu6050{
	port_i2c_t *i2c;
	int period;
	float a_data[3]; // данные акселерометра xyz
	float g_data[3]; //даныне гироскопа xyz
	xSemaphoreHandle mutex;
}mpu6050_t;

mpu6050_t* mpu6050_init(mpu6050_init_t* cfg);
int mpu6050_getData(mpu6050_t *d, float *a_data, float* g_data);


#endif /* MPU6050_H_ */
