#include "rk_hardware.h"

void hardwareInit ( void ) {
	__HAL_FLASH_PREFETCH_BUFFER_ENABLE();
	rkGlobalPortObj.reinit_all_ports();
}
