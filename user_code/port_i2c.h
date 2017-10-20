/*
 * port_i2c.h
 *
 *  Created on: 06 дек. 2015 г.
 *      Author: jdi
 */

#ifndef PORT_I2C_H_
#define PORT_I2C_H_
#include "stm32f1xx_hal_conf.h"
#include "user_os.h"

#include "stdint.h"
typedef struct{
	I2C_HandleTypeDef handle;
	xSemaphoreHandle semaphore; // семафор по завершению приёма или отправки
}port_i2c_t;

typedef struct{
	I2C_TypeDef *i2c_inst;
	uint32_t speed; //  Гц, до 400000 Гц
	DMA_Channel_TypeDef * dmaTx;
	DMA_Channel_TypeDef * dmaRx;
}port_i2c_initCfg_t;

port_i2c_t* port_i2c_init(port_i2c_initCfg_t *cfg);
#endif /* PORT_I2C_H_ */
