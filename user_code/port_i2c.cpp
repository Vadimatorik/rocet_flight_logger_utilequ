/*
 * port_i2c.c
 *
 *  Created on: 06 дек. 2015 г.
 *      Author: jdi
 */

#include "stm32f1xx_hal.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "port_i2c.h"
#include "string.h"


port_i2c_t* port_i2c_init(port_i2c_initCfg_t *cfg){
	configASSERT(cfg);
    port_i2c_t *i2c = (port_i2c_t *) pvPortMalloc(sizeof(*i2c));
	configASSERT(i2c);
	memset(i2c, 0, sizeof(*i2c));
	i2c->handle.Instance = cfg->i2c_inst;
	i2c->handle.Init.ClockSpeed = cfg->speed;
	i2c->handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
	i2c->handle.Init.OwnAddress1 = 0x18; //адрес нашего контроллера, взят из головы
	i2c->handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c->handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	i2c->handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	HAL_StatusTypeDef staus;
    (void)staus;
	staus = HAL_I2C_Init(&i2c->handle);
	i2c->semaphore = xSemaphoreCreateBinary();
	DMA_HandleTypeDef *dma;
	if ( cfg->dmaTx != NULL ) {
        i2c->handle.hdmatx = (DMA_HandleTypeDef *)pvPortMalloc (sizeof (*dma));
		configASSERT ( i2c->handle.hdmatx );
		dma = i2c->handle.hdmatx;
		dma->Instance = cfg->dmaTx;
	#ifdef __STM32F4xx_HAL_H
		dma->Init.Channel = init->dma_txChannel;
	#endif
		dma->Init.Direction = DMA_MEMORY_TO_PERIPH;
		dma->Init.PeriphInc = DMA_PINC_DISABLE;
		dma->Init.MemInc = DMA_MINC_ENABLE;
		dma->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		dma->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		dma->Init.Mode = DMA_NORMAL;
		dma->Init.Priority = DMA_PRIORITY_HIGH;
	#ifdef __STM32F4xx_HAL_H
		dma->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	#endif
		HAL_DMA_Init ( i2c->handle.hdmatx );
		dma->Parent = &i2c->handle;
	}
	if ( cfg->dmaRx != NULL ) {
        i2c->handle.hdmarx = (DMA_HandleTypeDef *)pvPortMalloc (sizeof (*dma));
		configASSERT ( i2c->handle.hdmarx );
		dma = i2c->handle.hdmarx;
		dma->Instance = cfg->dmaRx;
	#ifdef __STM32F4xx_HAL_H
		dma->Init.Channel = init->dma_txChannel;
	#endif
		dma->Init.Direction = DMA_PERIPH_TO_MEMORY;
		dma->Init.PeriphInc = DMA_PINC_DISABLE;
		dma->Init.MemInc = DMA_MINC_ENABLE;
		dma->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		dma->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		dma->Init.Mode = DMA_NORMAL;
		dma->Init.Priority = DMA_PRIORITY_HIGH;
	#ifdef __STM32F4xx_HAL_H
		dma->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	#endif
		HAL_DMA_Init ( i2c->handle.hdmarx );
		dma->Parent = &i2c->handle;
	}
	__HAL_I2C_ENABLE(&i2c->handle);
	return i2c;
}

