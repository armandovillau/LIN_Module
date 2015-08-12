/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %MPC5606B_PIT_lib.h%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    08 July 2015 %
*=============================================================================*/
/* DESCRIPTION : Provides needed defines and macros to manage timers modules. */
/*============================================================================*/
/* FUNCTION COMMENT : The PIT library makes it easier to configure and use    */
/*					  the timers.                                             */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 08/07/2015  |                               | Michele Balbi    */
/* First Draft of file.                                          			  */
/*============================================================================*/

#ifndef MPC5606B_PIT_LIB
#define MPC5606B_PIT_LIB

#include "MPC5606B.h"

#define CLK_FREQ 	64000000u

/* Timer Macros */

#define TIMER_INIT()							(PIT.PITMCR.R = 0u)
#define TIMER_LOAD_VALUE_CYCLES(ticks,timer)	(PIT.CH[(timer)].LDVAL.R = (ticks))
#define TIMER_LOAD_VALUE_MS(ms,timer)			(PIT.CH[(timer)].LDVAL.R = ((ms)*(CLK_FREQ/1000u))-1u)
#define TIMER_LOAD_VALUE_US(us,timer)			(PIT.CH[(timer)].LDVAL.R = ((us)*(CLK_FREQ/1000000u))-1u)
#define TIMER_GET_VALUE_CYCLES(timer)			(PIT.CH[(timer)].CVAL.R)
#define TIMER_GET_VALUE_MS(timer)				((PIT.CH[(timer)].LDVAL.R - PIT.CH[(timer)].CVAL.R)/(CLK_FREQ/1000u))

#define TIMER_ENABLE_INT(timer)				(PIT.CH[(timer)].TCTRL.B.TIE = 1u)
#define TIMER_DISABLE_INT(timer)			(PIT.CH[(timer)].TCTRL.B.TIE = 0u)
#define TIMER_START(timer)					(PIT.CH[(timer)].TCTRL.B.TEN = 1u)
#define TIMER_STOP(timer)					(PIT.CH[(timer)].TCTRL.B.TEN = 0u)
#define TIMER_IS_RUNNING(timer)				(PIT.CH[(timer)].TCTRL.B.TEN)
#define TIMER_CLEAR_INT_FLAG(timer)			(PIT.CH[(timer)].TFLG.B.TIF = 1u)


#endif
