/*
	Copyright (C) 2018 ER2C
	Politektik Elektronika Negeri Surabaya
	Agung Pambudi <agung.pambudi55@yahoo.com>
*/
/*
	prioritas interrupt
	0 timer
	1 scheduling
	4 task
*/

#ifndef FLOWRTOS_H
#define FLOWRTOS_H

#ifndef __arm__
#error solox
#else

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "flowrtos_io.h"
#include "clock_freq.h"
#include "epit.h"
#include "uart_imx.h"
#include "debug_console_imx.h"
#include "pin_mux.h"
#include "rdc.h"
#include "rdc_defs_imx6sx.h"
#include "ccm_imx6sx.h"
#include "wdog_imx.h"

#include "flowrtos_timer.h"
#include "flowrtos_task.h"
#include "flowrtos_interrupt.h"
#include "flowrtos_malloc_TSLF.h"

#include /*flowrtos_io*/"dxl.h"
#include /*flowrtos_io*/"gy521.h"

#endif
#endif