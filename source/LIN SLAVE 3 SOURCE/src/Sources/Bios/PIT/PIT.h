/****************************************************************************************************/
/**
\file       PIT.h
\brief      Periodic Interrupt Timer initialization and low-level functions and prototypes
\author     Abraham Tezmol
\version    1.0
\date       03/May/2013
*/
/****************************************************************************************************/
#ifndef __PIT_H        /*prevent duplicated includes*/
#define __PIT_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core Modules */
/** Variable types and common definitions */
    #include    "typedefs.h"

/** Used Modules */

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* PIT_Callback[], function to be called upon event trigger on PIT channels */
extern tCallbackFunction PIT_Callback[8];
	

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/** Periodic Interrupt Timer definitions */
#define    PIT_CHANNEL_0					0

#define    PIT_DEVICE_FREQUENCY           (uint32_t)64000000
#define    PIT_CHANNEL_TARGET_FREQUENCY   (uint32_t)1600

/** Periodic Interrupt Timer macros */
#define    PIT_CHANNEL_VALUE            	( ( PIT_DEVICE_FREQUENCY / PIT_CHANNEL_TARGET_FREQUENCY ) - 1 )


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** PIT Low level initialization */
void PIT_device_init(void);

/* PIT Low level channel configuration */
void PIT_channel_configure(uint8_t channel, tCallbackFunction Callback);

/** PIT Low level Start procedure */
void PIT_channel_start(uint8_t channel);

/** PIT Low level Stop procedure */
void PIT_channel_stop(uint8_t channel);

/** PIT Channel 0 ISR  */
void PIT_channel_0_isr( void  );


/*******************************************************************************/

#endif /* __PIT_H */
