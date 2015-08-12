/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         main.c
* version:          1.0
* created_by:       Gilberto Ochoa
* date_created:     Mon  Jul 13   2015 
*=============================================================================*/
/* DESCRIPTION :  This File contains initializations and main settings        */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 13/07/2015  |                               | Gilberto Ochoa   */
/*           |             |                               |                  */
/*============================================================================*/

/* Includes */
/* -------- */

#include "MCU_derivative.h"

/** GPIO funtion prototypes  */
#include    "GPIO.h"
#include    "PIT.h"
#include    "SchM.h"
#include    "SchM_Cfg.h"
#include    "MemAlloc_Cfg.h"
#include    "LIN_Driver.h"


#define BAUDRATE_9600 9600

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


/* Private functions prototypes */
/* ---------------------------- */
void disableWatchdog(void);


/* Exported functions prototypes */
/* ----------------------------- */



/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 :  main
 *  Description          :  The Main function
 *  Parameters           :  void
 *  Return               :  void
 *  Critical/explanation :  No
 **************************************************************/
void main(void) 

{
	MemAllocInit(&MemAllocConfig);
	
	
	initModesAndClock();
	/*Enable peri set 1 sysclk divided by 1 */
	initPeriClkGen();
	/* Disable Watchdog */
	disableWatchdog();
	/*Initialize LEDs on TRK-MPC560xB board */
	vfnGPIO_LED_Init();
	/*Initialize BUTTONs on TRK-MPC560xB board */
	vfnGPIO_BUTTON_Init();	
	/*Initialize Interrupts */
	INTC_InitINTCInterrupts();
	/*Initialize Exception Handlers */
	EXCEP_InitExceptionHandlers();
	
	IntcInterruptLINFLEXHandlers();
	
  
  
  	initLINFlex_0(BAUDRATE_9600);         /* Initialize FLEXCAN 0 as master */
    
    
   SchM_Init(&SchedulerConfig);
    /* Enable External Interrupts*/
    
    
    SchM_Start();
    
	
	/* Infinite loop */
	for (;;) 
	{


        
	}
}



/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 :  disableWatchdog
 *  Description          :  Disable the Watchdog
 *  Parameters           :  void
 *  Return               :  void
 *  Critical/explanation :  No
 **************************************************************/
void disableWatchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}