#include "rk_pins.h"
#include "user_os.h"

const pin_cfg rkTpChPinCfg				= { GPIOA, { .Pin = GPIO_PIN_0,		.Mode = GPIO_MODE_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_LOW } };
const pin_cfg rkTpWtPinCfg				= { GPIOA, { .Pin = GPIO_PIN_1,		.Mode = GPIO_MODE_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_LOW } };

const pin_cfg rkUartTxPinCfg			= { GPIOA, { .Pin = GPIO_PIN_2,		.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkUartRxPinCfg			= { GPIOA, { .Pin = GPIO_PIN_3,		.Mode = GPIO_MODE_AF_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const pin_cfg rkAdcPinCfg				= { GPIOA, { .Pin = GPIO_PIN_4,		.Mode = GPIO_MODE_ANALOG,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_LOW } };

const pin_cfg rkLed0PinCfg				= { GPIOB, { .Pin = GPIO_PIN_7,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkLed1PinCfg				= { GPIOA, { .Pin = GPIO_PIN_5,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const pin_cfg rkFlashResPinCfg			= { GPIOA, { .Pin = GPIO_PIN_6,		.Mode = GPIO_MODE_OUTPUT_OD,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_LOW } };
const pin_cfg rkFlashWpPinCfg			= { GPIOA, { .Pin = GPIO_PIN_8,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const pin_cfg rkPpOnPinCfg				= { GPIOA, { .Pin = GPIO_PIN_9,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkPpInPinCfg				= { GPIOB, { .Pin = GPIO_PIN_7,		.Mode = GPIO_MODE_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const pin_cfg rkEspModePinCfg			= { GPIOB, { .Pin = GPIO_PIN_1,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkEspEnPinCfg				= { GPIOB, { .Pin = GPIO_PIN_8,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkEspRstPinCfg			= { GPIOB, { .Pin = GPIO_PIN_9,		.Mode = GPIO_MODE_OUTPUT_OD,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const pin_cfg rkMpuIntPinCfg			= { GPIOB, { .Pin = GPIO_PIN_2,		.Mode = GPIO_MODE_IT_RISING,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkMpuSclPinCfg			= { GPIOB, { .Pin = GPIO_PIN_10,	.Mode = GPIO_MODE_AF_OD,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkMpuSdaPinCfg			= { GPIOB, { .Pin = GPIO_PIN_11,	.Mode = GPIO_MODE_AF_OD,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const pin_cfg rkSpi1ClkPinCfg			= { GPIOB, { .Pin = GPIO_PIN_3,		.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkSpi1MisoPinCfg			= { GPIOB, { .Pin = GPIO_PIN_4,		.Mode = GPIO_MODE_AF_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkSpi1MosiPinCfg			= { GPIOB, { .Pin = GPIO_PIN_5,		.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkSpi1CsPinCfg			= { GPIOA, { .Pin = GPIO_PIN_15,	.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const pin_cfg rkSpi2ClkPinCfg			= { GPIOB, { .Pin = GPIO_PIN_13,	.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkSpi2MisoPinCfg			= { GPIOB, { .Pin = GPIO_PIN_14,	.Mode = GPIO_MODE_AF_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkSpi2MosiPinCfg			= { GPIOB, { .Pin = GPIO_PIN_15,	.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const pin_cfg rkSpi2CsPinCfg			= { GPIOB, { .Pin = GPIO_PIN_12,	.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const pin_cfg rkGlobalPortPinCfg[] = {
	rkTpChPinCfg,		rkTpWtPinCfg,
	rkUartTxPinCfg,		rkUartRxPinCfg,
	rkAdcPinCfg,
	rkLed0PinCfg,		rkLed1PinCfg,
	rkFlashResPinCfg,	rkFlashWpPinCfg,
	rkPpOnPinCfg,		rkPpInPinCfg,
	rkEspModePinCfg,	rkEspEnPinCfg,		rkEspRstPinCfg,
	rkMpuIntPinCfg,		rkMpuSclPinCfg,		rkMpuSdaPinCfg,
	rkSpi1ClkPinCfg,	rkSpi1MisoPinCfg,	rkSpi1MosiPinCfg,		rkSpi1CsPinCfg,
	rkSpi2ClkPinCfg,	rkSpi2MisoPinCfg,	rkSpi2MosiPinCfg,		rkSpi2CsPinCfg
};

global_port	rkGlobalPortObj( rkGlobalPortPinCfg, M_SIZE_ARRAY( rkGlobalPortPinCfg ) );
extern global_port	rkGlobalPortObj;
