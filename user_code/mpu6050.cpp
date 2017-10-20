/*
 * mpu6050.c
 *
 *  Created on: 06 дек. 2015 г.
 *      Author: jdi
 */
#include "mpu6050.h"
#include "mpu6050_defs.h"
#include "port_i2c.h"
#include "string.h"

#define MPU6050_EOK 0
#define MPU6050_ERR 1

static void MPU6050_WriteBits(mpu6050_t *d, uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
static int MPU6050_I2C_BufferRead(mpu6050_t *d, uint8_t slaveAddr, uint8_t* pBuffer, uint8_t readAddr, uint16_t NumByteToRead);
static int MPU6050_I2C_ByteWrite(mpu6050_t *d, uint8_t slaveAddr, uint8_t* pBuffer, uint8_t writeAddr);
static void mpu6050_cfg(mpu6050_t *d);
static void MPU6050_GetRawAccelGyro(mpu6050_t *d, int16_t* AccelGyro);


void imuThread(void * p){
	mpu6050_t *d = (mpu6050_t*) p;
	int16_t acel_gyro_d[6]= {0};
	float a_data[3] = {0};
	float g_data[3] = {0};
	int axes_count;
	TickType_t xLastWakeTime;
	const TickType_t period = d->period;
	configASSERT(d);
	mpu6050_cfg(d);
	xLastWakeTime = xTaskGetTickCount();
	for(;;){
		vTaskDelayUntil(&xLastWakeTime, period);
		MPU6050_GetRawAccelGyro(d, acel_gyro_d);
		for(axes_count = 0; axes_count < 3; axes_count++){
			a_data[axes_count] = (float) acel_gyro_d[axes_count] / 16384.0;
		}
		for(axes_count = 0; axes_count < 3; axes_count++){
			g_data[axes_count] = (float) acel_gyro_d[axes_count+3] / 131.0;
		}
		if (xSemaphoreTake(d->mutex, portMAX_DELAY) == pdTRUE){
			memcpy(d->a_data, a_data, sizeof(a_data));
			memcpy(d->g_data, g_data, sizeof(g_data));
			xSemaphoreGive(d->mutex);
		}
	}
}

mpu6050_t* mpu6050_init(mpu6050_init_t* cfg){
	// TODO:проверки входных данных
    mpu6050_t *d = (mpu6050_t *)pvPortMalloc(sizeof(*d));
    d->i2c = port_i2c_init(cfg->i2c_cfg);
	d->period = cfg->period;
	d->mutex = xSemaphoreCreateMutex();
    xTaskCreate(imuThread, "imuThread", 400, d ,cfg->thread_priority, NULL);
	return d;
}

int mpu6050_getData(mpu6050_t *d, float *a_data, float* g_data){
	int rv = -1;
	if(xSemaphoreTake(d->mutex, 2) == pdTRUE){
		memcpy(a_data, d->a_data, sizeof(d->a_data));
		memcpy(g_data, d->g_data,  sizeof(d->g_data));
		xSemaphoreGive(d->mutex);
		rv = 0;
	}
	return rv;
}

static void mpu6050_cfg(mpu6050_t *d){
    MPU6050_WriteBits(d, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, MPU6050_CLOCK_PLL_XGYRO);
    MPU6050_WriteBits(d, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, MPU6050_GYRO_FS_250);
    MPU6050_WriteBits(d, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, MPU6050_ACCEL_FS_2);
    MPU6050_WriteBits(d, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT,1, DISABLE);
}

/** Write multiple bits in an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 */
static void MPU6050_WriteBits(mpu6050_t *d, uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    uint8_t tmp = 0;
    MPU6050_I2C_BufferRead(d, slaveAddr, &tmp, regAddr, sizeof(tmp));
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    data <<= (bitStart - length + 1); // shift data into correct position
    data &= mask; // zero all non-important bits in data
    tmp &= ~(mask); // zero all important bits in existing byte
    tmp |= data; // combine data with existing byte
    MPU6050_I2C_ByteWrite(d, slaveAddr, &tmp, regAddr);
}

static int MPU6050_I2C_BufferRead(mpu6050_t *d, uint8_t slaveAddr, uint8_t* pBuffer, uint8_t readAddr, uint16_t NumByteToRead){
	xSemaphoreTake(d->i2c->semaphore, 0);
	HAL_I2C_Master_Transmit_IT(&d->i2c->handle, slaveAddr, &readAddr, sizeof(readAddr) );
	if(xSemaphoreTake(d->i2c->semaphore, 10) != pdTRUE){
		return MPU6050_ERR;
	}
	HAL_I2C_Master_Receive_IT(&d->i2c->handle, slaveAddr , pBuffer, NumByteToRead);
	if(xSemaphoreTake(d->i2c->semaphore, 10) != pdTRUE){
		return MPU6050_ERR;
	}
	return MPU6050_EOK;
}

static int MPU6050_I2C_ByteWrite(mpu6050_t *d, uint8_t slaveAddr, uint8_t* pBuffer, uint8_t writeAddr){
	uint8_t tx_buf[2] = {0};
	tx_buf[0] = writeAddr;
	tx_buf[1] = *pBuffer;
	xSemaphoreTake(d->i2c->semaphore, 0);
	HAL_I2C_Master_Transmit_IT(&d->i2c->handle, slaveAddr, tx_buf, sizeof(tx_buf) );
	if(xSemaphoreTake(d->i2c->semaphore, 10) != pdTRUE){
		return MPU6050_ERR;
	}
	return MPU6050_EOK;
}

static void MPU6050_GetRawAccelGyro(mpu6050_t *d, int16_t* AccelGyro)
{
	int i;
    uint8_t tmpBuffer[14];
    MPU6050_I2C_BufferRead(d, MPU6050_DEFAULT_ADDRESS, tmpBuffer, MPU6050_RA_ACCEL_XOUT_H, 14);
    /* Get acceleration */
    for (i = 0; i < 3; i++)
        AccelGyro[i] = ((uint16_t) ((uint16_t) tmpBuffer[2 * i] << 8) + tmpBuffer[2 * i + 1]);
    /* Get Angular rate */
    for (i = 4; i < 7; i++)
        AccelGyro[i - 1] = ((uint16_t) ((uint16_t) tmpBuffer[2 * i] << 8) + tmpBuffer[2 * i + 1]);

}



