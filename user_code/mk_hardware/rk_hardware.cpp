#include "rk_hardware.h"

extern i2c rkI2cObj;

void hardwareInit ( void ) {
	__HAL_FLASH_PREFETCH_BUFFER_ENABLE();
	rkGlobalPortObj.reinit_all_ports();
	rkI2cObj.reinit();
}
