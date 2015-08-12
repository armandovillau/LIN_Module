/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         SchM.c
* version:          1.0
* created_by:       Gilberto Ochoa
* %date_created:    Mon Jul  13  2015
*=============================================================================*/
/* DESCRIPTION : Provides main functionality of the scheduler                 */
/*============================================================================*/
/* FUNCTION COMMENT : OS Tick callback shall be allocated on those files      */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 13/07/2015  |                               | Gilberto Ochoa   */
/*                                                                            */
/*============================================================================*/

/* Includes */
/* -------- */
#include "SchM.h"
#include "PIT.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */

const SchedulerConfigType *SchedulerConfigGlobal;

/* WORD constants */

/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */

static T_UBYTE rub_index=POSITION_ZERO;


SchedulerControlType SchedulerControl=
{
	ZERO_SECONDS,TASK_BKG,SCHEDULER_UNINIT
};


/* WORD RAM variables */

SchedulerTCB *SchedulerTCB_Task;

/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */

void SchM_OsTick(void);
void SchM_Background(void);

/* Exported functions prototypes */
/* ----------------------------- */




/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	SchM_Init
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 void SchM_Init(const SchedulerConfigType *SchM_Config)
 {
 	T_UBYTE lub_index;
 	
 	SchedulerConfigGlobal=SchM_Config;
 	
 	SchedulerControl.SchedulerStatus=SCHEDULER_INIT;
 	 
 	SchedulerTCB_Task = (SchedulerTCB*)MemAlloc(SchedulerConfigGlobal->SchedulerNumberOfTasks*sizeof(SchedulerTCB));
 	 
 	for(lub_index=0;lub_index<SchedulerConfigGlobal->SchedulerNumberOfTasks;lub_index++)
 	{
 		SchedulerTCB_Task[lub_index].SchedulerTaskState=TASK_STATE_SUSPENDED;
 		SchedulerTCB_Task[lub_index].TaskFunctionControlPtr=SchM_Config->SchedulerTaskDescriptor[lub_index].TaskFunctionPtr;
 	}
 	
 	PIT_device_init();
 	PIT_channel_configure(PIT_CHANNEL_0 , &SchM_OsTick);
 	
 }
 
 
 	
 /* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	SchM_DeInit
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 void SchM_Stop(void)
 {
 	PIT_channel_stop(PIT_CHANNEL_0);
 	SchedulerControl.SchedulerStatus=SCHEDULER_HALTED;
 }
 
 
 
 /* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	SchM_Start
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 void SchM_Start(void)
 {
 	SchedulerControl.SchedulerStatus=SCHEDULER_RUNNING;
 	PIT_channel_start(PIT_CHANNEL_0);
 	enableIrq();   /* Enable External Interrupts*/
 	SchM_Background();
 }
 
 
 
/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : SchM_OsTick
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 void SchM_OsTick(void)
 {
 	T_UBYTE lub_index;
 	SchedulerControl.SchedulerCounter++;
 	
 	for(lub_index=0;lub_index<SchedulerConfigGlobal->SchedulerNumberOfTasks;lub_index++)
 	{
 		if(((SchedulerConfigGlobal->SchedulerTaskDescriptor[lub_index].SchedulerTaskMask) & (SchedulerControl.SchedulerCounter)) == SchedulerConfigGlobal->SchedulerTaskDescriptor[lub_index].SchedulerTaskOffset)
 		{
 			SchedulerTCB_Task[lub_index].SchedulerTaskState=TASK_STATE_READY;
 		}
 		
 		else
 		{
 			//Do nothing
 		}
 	}
 	
 }
 
 
 
/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 :	SchM_Background
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 void SchM_Background(void)
 {
 	for(;;)
 	{
 		for(rub_index=0;rub_index<SchedulerConfigGlobal->SchedulerNumberOfTasks;rub_index++)
 		{
 			if(SchedulerTCB_Task[rub_index].SchedulerTaskState==TASK_STATE_READY)
 			{
 				SchedulerTCB_Task[rub_index].SchedulerTaskState=TASK_STATE_RUNNING;
 				SchedulerTCB_Task[rub_index].TaskFunctionControlPtr();
 				SchedulerTCB_Task[rub_index].SchedulerTaskState=TASK_STATE_SUSPENDED;
 				
 		    }
 		    
 		    else
 		    {
 		    	//Do nothing
 		    }
 		}
 	}  /* infinity for*/
 }