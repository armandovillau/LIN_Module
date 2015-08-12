/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %LIN_Driver.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      uid02495 %
* %date_created:    Fri Jan  9 14:38:03 2004 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "App.h"
#include "GPIO.h"
#include "LIN_Driver.h"


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
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void LED (void)
{
	static T_UBYTE lub_ToggleCounter=0; 
	T_UBYTE lub_Comand=GetLinData();
	static T_UBYTE lub_LedState=cmd_NONE;
	switch (lub_LedState)
	{
		case cmd_NONE: 
						lub_LedState=lub_Comand;
						break;
	 	case cmd_LED_on:
	 	 				lub_LedState=lub_Comand;
	 	 				LED_ON(LED1);
						break;
	 	case cmd_LED_off:
	 					lub_LedState=lub_Comand;
	 					LED_OFF(LED1);
						break;
	 	case cmd_LED_toggling:
	 					lub_LedState=lub_Comand;
	 					lub_ToggleCounter++;
	 					if(lub_ToggleCounter >= 167)
	 					{
	 						LED_TOGGLE(LED1);
	 						lub_ToggleCounter=0;
	 					}
						break;
	 	case cmd_disable_slv:
	 					if(cmd_enable_slv == lub_Comand)
	 					{
	 						lub_LedState=lub_Comand;
	 					}
	 					else
	 					{
	 						/* Do nothing */
	 					}
						break;
	    case cmd_enable_slv:
	    				lub_LedState=lub_Comand;
						break;
		default:		
						lub_LedState=lub_Comand;
				break;
	}
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
