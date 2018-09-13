#include "rk_pins.h"
#include "user_os.h"

const McHardwareInterfacesImplementation::PinCfg rkTpChPinCfg			= { GPIOA, { .Pin = GPIO_PIN_0,		.Mode = GPIO_MODE_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_LOW } };
const McHardwareInterfacesImplementation::PinCfg rkTpWtPinCfg			= { GPIOA, { .Pin = GPIO_PIN_1,		.Mode = GPIO_MODE_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_LOW } };

const McHardwareInterfacesImplementation::PinCfg rkUartTxPinCfg			= { GPIOA, { .Pin = GPIO_PIN_2,		.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkUartRxPinCfg			= { GPIOA, { .Pin = GPIO_PIN_3,		.Mode = GPIO_MODE_AF_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const McHardwareInterfacesImplementation::PinCfg rkAdcPinCfg			= { GPIOA, { .Pin = GPIO_PIN_4,		.Mode = GPIO_MODE_ANALOG,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_LOW } };

const McHardwareInterfacesImplementation::PinCfg rkLed0PinCfg			= { GPIOB, { .Pin = GPIO_PIN_7,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkLed1PinCfg			= { GPIOA, { .Pin = GPIO_PIN_5,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const McHardwareInterfacesImplementation::PinCfg rkFlashResPinCfg		= { GPIOA, { .Pin = GPIO_PIN_6,		.Mode = GPIO_MODE_OUTPUT_OD,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_LOW } };
const McHardwareInterfacesImplementation::PinCfg rkFlashWpPinCfg		= { GPIOA, { .Pin = GPIO_PIN_8,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const McHardwareInterfacesImplementation::PinCfg rkPpOnPinCfg			= { GPIOA, { .Pin = GPIO_PIN_9,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkPpInPinCfg			= { GPIOB, { .Pin = GPIO_PIN_7,		.Mode = GPIO_MODE_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const McHardwareInterfacesImplementation::PinCfg rkEspModePinCfg		= { GPIOB, { .Pin = GPIO_PIN_1,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkEspEnPinCfg			= { GPIOB, { .Pin = GPIO_PIN_8,		.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkEspRstPinCfg			= { GPIOB, { .Pin = GPIO_PIN_9,		.Mode = GPIO_MODE_OUTPUT_OD,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const McHardwareInterfacesImplementation::PinCfg rkMpuIntPinCfg			= { GPIOB, { .Pin = GPIO_PIN_2,		.Mode = GPIO_MODE_IT_RISING,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkMpuSclPinCfg			= { GPIOB, { .Pin = GPIO_PIN_10,	.Mode = GPIO_MODE_AF_OD,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkMpuSdaPinCfg			= { GPIOB, { .Pin = GPIO_PIN_11,	.Mode = GPIO_MODE_AF_OD,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const McHardwareInterfacesImplementation::PinCfg rkSpi1ClkPinCfg		= { GPIOB, { .Pin = GPIO_PIN_3,		.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkSpi1MisoPinCfg		= { GPIOB, { .Pin = GPIO_PIN_4,		.Mode = GPIO_MODE_AF_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkSpi1MosiPinCfg		= { GPIOB, { .Pin = GPIO_PIN_5,		.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkSpi1CsPinCfg			= { GPIOA, { .Pin = GPIO_PIN_15,	.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const McHardwareInterfacesImplementation::PinCfg rkSpi2ClkPinCfg		= { GPIOB, { .Pin = GPIO_PIN_13,	.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkSpi2MisoPinCfg		= { GPIOB, { .Pin = GPIO_PIN_14,	.Mode = GPIO_MODE_AF_INPUT,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkSpi2MosiPinCfg		= { GPIOB, { .Pin = GPIO_PIN_15,	.Mode = GPIO_MODE_AF_PP,		.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };
const McHardwareInterfacesImplementation::PinCfg rkSpi2CsPinCfg			= { GPIOB, { .Pin = GPIO_PIN_12,	.Mode = GPIO_MODE_OUTPUT_PP,	.Pull = GPIO_NOPULL,	.Speed = GPIO_SPEED_FREQ_HIGH } };

const McHardwareInterfacesImplementation::PinCfg rkGlobalPortPinCfg[] = {
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

McHardwareInterfacesImplementation::PortGlobal	rkGlobalPortObj( rkGlobalPortPinCfg, M_SIZE_ARRAY( rkGlobalPortPinCfg ) );
extern McHardwareInterfacesImplementation::PortGlobal	rkGlobalPortObj;
