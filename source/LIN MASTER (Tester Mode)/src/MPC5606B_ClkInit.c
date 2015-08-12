/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %MPC5606B_ClkInit.c%
* Instance:         1
* %version:         1.4 %
* %created_by:      Michele Balbi %
* %date_created:    20 June 2015 %
*=============================================================================*/
/* DESCRIPTION : C file for clocks initialization                             */
/*============================================================================*/
/* FUNCTION COMMENT : This file configures running modes and clock            */
/*                    initialization for the MCU and its peripherals.         */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/06/2015  |                               | Michele Balbi    */
/* 	First Draft.                                                              */
/*----------------------------------------------------------------------------*/
/*  1.1      | 21/06/2015  |                               | Michele Balbi    */
/* 	Corrected invalid write to a read-only register.                          */
/*----------------------------------------------------------------------------*/
/*  1.2      | 26/06/2015  |                               | Michele Balbi    */
/* 	Now using defines from MPC5606_Mapper.h                                   */
/*----------------------------------------------------------------------------*/
/*  1.3      | 30/06/2015  |                               | Michele Balbi    */
/* 	Corrections and formatting for C Code Review template compliance.         */
/*----------------------------------------------------------------------------*/
/*  1.4      | 30/07/2015  |                               | Michele Balbi    */
/* 	Added private defines for MCTL and PCTL modules from the .h file.         */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "MPC5606B_ClkInit.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

/* Defines for mode changes through the MCTL register */
#define MCTL_RUN0_KEY			0x40005AF0u
#define MCTL_RUN0_KEY_INV		0x4000A50Fu
#define MCTL_RUN1_KEY			0x50005AF0u
#define MCTL_RUN1_KEY_INV		0x5000A50Fu
#define MCTL_RUN2_KEY			0x60005AF0u
#define MCTL_RUN2_KEY_INV		0x6000A50Fu
#define MCTL_RUN3_KEY			0x70005AF0u
#define MCTL_RUN3_KEY_INV		0x7000A50Fu
#define MCTL_HALT_KEY			0x80005AF0u
#define MCTL_HALT_KEY_INV		0x8000A50Fu
#define MCTL_STOP_KEY			0xA0005AF0u
#define MCTL_STOP_KEY_INV		0xA000A50Fu
#define MCTL_STANDBY_KEY		0xD0005AF0u
#define MCTL_STANDBY_KEY_INV	0xD000A50Fu

/* Defines for the current mode*/
#define RUN0_MODE		4
#define RUN1_MODE		5
#define RUN2_MODE		6
#define RUN3_MODE		7
#define HALT_MODE		8
#define STOP_MODE		10
#define STANDBY_MODE	13


/* Register gating addresses offsets for PCTL registers */
#define PCTL_ADC_0 		32
#define PCTL_ADC_1	 	33
#define PCTL_LINFLEX_0	48
#define PCTL_LINFLEX_1	49
#define PCTL_LINFLEX_2	50
#define PCTL_LINFLEX_3	51
#define PCTL_LINFLEX_4	52
#define PCTL_LINFLEX_5	53
#define PCTL_LINFLEX_6	54
#define PCTL_LINFLEX_7	55
#define PCTL_LINFLEX_8	12
#define PCTL_LINFLEX_9	13
#define PCTL_SIUL 		68
#define PCTL_WKPU		69
#define PCTL_EMIOS_0 	72
#define PCTL_EMIOS_1 	73
#define PCTL_RTC		91
#define PCTL_PIT 		92

/* Defines for peripheral sets clock dividers */
#define PS1_DIV		0
#define PS2_DIV		1
#define PS3_DIV		2

/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */

/* Private functions */
/* ----------------- */

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	initModesAndClock
 *  Description          :	Initializes running mode and clock of the MCU.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  yes
 **************************************************************/
void initModesAndClock(void) {
  ME.MER.R = 0x0000001Du;          /* Enable DRUN, RUN0, SAFE, RESET modes */
                                  /* Initialize PLL before turning it on: */
  CGM.FMPLL_CR.R = 0x02400100u;    /* 8 MHz xtal: Set PLL0 to 64 MHz */
  								  /*  Divide by 64, 8 in ODF, 1 in IDF */
  ME.RUN[0].R = 0x001F0074u;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  ME.RUNPC[1].R = 0x00000010u; 	  /* Peri. Cfg. 1 settings: only run in RUN0 mode */
  
  ME.PCTL[PCTL_SIUL].R = 0x01u; 	  /* MPC56xxB/S SIU: select ME.RUNPC[1] */
  ME.PCTL[PCTL_LINFLEX_0].R = 0x01u; 	  /* for LINFLEX_2 module */
  ME.PCTL[PCTL_LINFLEX_2].R = 0x01u;
                                  
  /* Mode Transition to enter RUN0 mode: */
  ME.MCTL.R = MCTL_RUN0_KEY;         /* Enter RUN0 Mode & Key */
  ME.MCTL.R = MCTL_RUN0_KEY_INV;     /* Enter RUN0 Mode & Inverted Key */  
  while (ME.GS.B.S_MTRANS) {}    	 /* Wait for mode transition to complete */    
  
  while(ME.GS.B.S_CURRENTMODE != RUN0_MODE) {} /* Verify RUN0 is the current mode */
}


/**************************************************************
 *  Name                 :	initPeriClkGen
 *  Description          :	Initializes clock of peripheral sets which will
 							be needed in the project.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  yes
 **************************************************************/
 void initPeriClkGen(void) {
/* Use the following code as required for MPC56xxB or MPC56xxS:*/
  CGM.SC_DC[PS1_DIV].R = 0x80u;   /* MPC56xxB/S: Enable peri set 1 sysclk divided by 1 */
}


/**************************************************************
 *  Name                 :	disableWatchdog
 *  Description          :	Disables the MCU's watchdog.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  yes
 **************************************************************/
void disableWatchdog(void) {
  SWT.SR.R = 0x0000c520u;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928u; 
  SWT.CR.R = 0x8000010Au;     /* Clear watchdog enable (WEN) */
} 
