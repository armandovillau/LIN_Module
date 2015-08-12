/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        SchM.h
* version:          1.0
* created_by:       Gilberto Ochoa
* date_created:     Mon Jul 13 2015
*=============================================================================*/
/* DESCRIPTION : Exports the public scheduler interfaces                      */
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
/* This file is created based on mw_schm_cfg module from the old version of   */
/* this scheduler.                                                            */
/*============================================================================*/

#ifndef SCHM_H
#define SCHM_H

/* Includes */
/* -------- */

#include "SchM_Types.h"


/*-- Defines -----------------------------------------------------------------*/
#define ZERO_SECONDS    0
#define POSITION_ZERO   0

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void SchM_Init(const SchedulerConfigType *SchM_Config);
extern void SchM_Stop(void);
extern void SchM_Start(void);


/* Functions macros */


/* Exported defines */


#endif