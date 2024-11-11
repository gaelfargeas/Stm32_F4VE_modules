/**
  ******************************************************************************
  * @file           : module_loader.c
  * @brief          : Modules initialization.
  ******************************************************************************
  * history:
  * ================================================================
  * 2024-10-31 gael fargeas created
  *
  */

#include "modules.h"

void module_init(void)
{
	uint8_t index = 0;

#ifdef MODULE_AM2320_ENABLE
	active_module[index] = MODULE_AM2320;
	index++;
#endif
}
