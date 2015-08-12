/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        GPIO.h
* Instance:         RPL_1
* %version:         1 
* %created_by:      Diego Flores
* %date_created:    Wendsday July 01 10:55:01 2015
*=============================================================================*/
/* DESCRIPTION :  Macro definitions for registers access and I/O handling                                        */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 01/07/2015  | SAR/SIF/SCN_xxx               | Diego Flores     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef _GPIO_H                               /* To avoid double inclusion */
#define _GPIO_H

/* Includes */
/* -------- */

/** MCU derivative information */
#include "MCU_derivative.h"
/** Variable types and common definitions */
#include "typedefs.h"

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
extern void vfnGPIO_Init_channel(uint8_t channel, uint8_t input_output, uint8_t Open_drain);
extern void vfnGPIO_LED_Init(void);
extern void vfnGPIO_BUTTON_Init(void);

void vfnGPIO_Output(uint8_t channel, uint8_t logical_value);

/* Functions macros */

/** Reed button*/
#define BOTTON_PRESS(channel)				(SIU.GPDI[channel].B.PDI)
/** Set LED */ 
#define LED_ON(channel)                     (SIU.GPDO[channel].B.PDO =  0)
/** Clear LED */ 
#define LED_OFF(channel)                    (SIU.GPDO[channel].B.PDO =  1)
/** Toggle LED */ 
#define LED_TOGGLE(channel)                 (SIU.GPDO[channel].B.PDO ^= 1) 

/* Exported defines */
#define LED1      					68
#define LED2       					69
#define LED3       					70
#define LED4        				71
#define PORTA10						10
#define PORTA11						11
#define BUTTON1						64
#define BUTTON2						65
#define BUTTON3						66
#define BUTTON4						67

#endif
