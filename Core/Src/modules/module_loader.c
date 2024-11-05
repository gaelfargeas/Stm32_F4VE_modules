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


int modules_enable[MODULES_NUMBER] = {MODULE_A_ENABLE};
int modules_timer[MODULES_NUMBER] = {MODULE_A_TIMER_MS};


/* Init Module A */
//modules_enable[0] = MODULE_A_ENABLE;
//modules_timer[0] = MODULE_A_TIMER_MS;
