/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         SchM_Cfg.c
* version:          1.0
* created_by:       Gilberto Ochoa
* %date_created:    Mon Jul  13  2015
*=============================================================================*/
/* DESCRIPTION : Provides the general scheduler configuration and tasks       */
/*               descriptor table                                             */
/*=================================	==========================================*/
/* FUNCTION COMMENT : Here is the table to configure the tasks of the system  */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 13/07/2015  |                               | Gilberto Ochoa   */
/* This file is created based on mw_schm_cfg module from the old version of   */
/* this scheduler.                                                            */
/*============================================================================*/

/* Includes */
/* -------- */
#include "SchM_Cfg.h"
#include "SchM_Tasks.h"


const SchedulerTaskDescriptorType SchedulerTaskDescConfig [] =
{
	/* Offset,        MASK,           Task ID,       Function Pointer*/
	{   ZERO,      MASK_1P25MS,    TASK_1P25MS,      &SchM_1p25ms_Task   },
	{   ONE,       MASK_2P5MS,     TASK_2P5MS,       &SchM_2p5ms_Task    },
	{   TWO,       MASK_5MS,       TASK_5MS,         &SchM_5ms_Task      },
	{   THREE,     MASK_10MS,      TASK_10MS,        &SchM_10ms_Task     },
	{   FIVE,      MASK_20MS,      TASK_20MS,        &SchM_20ms_Task     },
	{   SIX,       MASK_40MS,      TASK_40MS,        &SchM_40ms_Task     }
};

const SchedulerConfigType SchedulerConfig = 
{
	(sizeof(SchedulerTaskDescConfig)/sizeof(SchedulerTaskDescConfig[0])),
	SchedulerTaskDescConfig
};



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


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/

