/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %MPC5606B_GPIO_lib.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 17 2015 %
*=============================================================================*/
/* DESCRIPTION : C source code for GPIO configuration.                        */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source code used to initialize*/
/* the GPIO pins.                                                             */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/07/2015  |                               | Michele Balbi    */
/* 	Added GPIO_Init() function.                                               */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B_GPIO_lib.h"

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



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */


/* Private functions */
/* ----------------- */


/* Exported functions */
/* ------------------ */
/********************************************************************************
 *  Name                 :	GPIO_Init
 *  Description          :	GPIO configuration function.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  This routine configures the GPIOs used in the 
 							application.
 ********************************************************************************/
 void GPIO_Init(void){
 
 	SIU.PCR[64].R = 0x0103;
	SIU.PCR[65].R = 0x0103;
	SIU.PCR[66].R = 0x0103;
	SIU.PCR[67].R = 0x0103;
	
	SIU.PCR[68].R = 0x200;	/* Embedded board leds seted as outputs */
  	SIU.PCR[69].R = 0x200;
  	SIU.PCR[70].R = 0x200;
  	SIU.PCR[71].R = 0x200;
	
	SIU.PSMI[31].B.PADSEL = 1;
	/*SIU.PSMI[62].B.PADSEL = 1;*/
	
	GPIO_ALT_MODE_1(PORTC8); 
	GPIO_AS_INPUT(PORTC9);
/*	SIU.PCR[18].R = 0x0400; */        /* MPC56xxB: Configure port B2 as LIN0TX */
  	/*SIU.PCR[19].R = 0x0103;   */      /* MPC56xxB: Configure port B3 as LIN0RX */
  	GPIO_ALT_MODE_1(PORTB2);
	GPIO_AS_INPUT(PORTB3);
	/*GPIO_ALT_MODE_1(PORTE10);
	GPIO_AS_INPUT(PORTE11);*/
 }