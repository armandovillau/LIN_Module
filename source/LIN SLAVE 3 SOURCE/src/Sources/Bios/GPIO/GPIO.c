/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        GPIO.c
* Instance:         RPL_1
* %version:         1
* %created_by:      Diego Flores
* %date_created:    monday July  13 08:26:50 2015
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : General purpose IO functions                                                */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 13/07/2015  |                               | Diego Flores     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */

/****************************************************************************************************/


/** MCU derivative information */
#include "MCU_derivative.h"
/** Variable types and common definitions */
#include "typedefs.h"

/** Own headers */
/* GPIO routines prototypes */ 
#include "GPIO.h"

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
#define GPIO_INPUT					0
#define GPIO_OUTPUT					1
#define GPIO_OPEN_DRAIN_DISABLE		0
#define GPIO_OPEN_DRAIN_ENABLE		1

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
 *  Name                 : 	vfnGPIO_Output
 *  Description          : 	Drive the logical output value to the pin
 *  Parameters           :  uint8_t channel - GPIO channel to be configured
 							uint8_t logical_value - select the output value
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/

void vfnGPIO_Output(uint8_t channel, uint8_t logical_value)
{
    SIU.GPDO[channel].B.PDO  = logical_value;  		/* Drive the logical output value to the pin */

}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	vfnGPIO_Init_channel
 *  Description          :  Configures individual GPIO pins to either input or output functionality.
 *  Parameters           :  uint8_t channel - GPIO channel to be configured
 							uint8_t input_output - selection of input/output functionality (has impact on output impedance selection)
 							uint8_t Open_drain - Push pull or open drain selection modes	
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/

void vfnGPIO_Init_channel(uint8_t channel, uint8_t input_output, uint8_t Open_drain)
{
    if (input_output == GPIO_OUTPUT)
    {
    	SIU.PCR[channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[channel].B.OBE = 1;					/* Output buffer enable */
    	if (Open_drain == GPIO_OPEN_DRAIN_ENABLE)
    	{
    		SIU.PCR[channel].B.ODE = 1;				/* Open drain option enable */	
    	}
    	else
    	{	
    		SIU.PCR[channel].B.ODE = 0;				/* Push-pull option enable */	
    	}
    }
    else if (input_output == GPIO_INPUT)
    {
    	SIU.PCR[channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[channel].B.IBE = 1;					/* Input buffer enable */	
    }

}

/**************************************************************
 *  Name                 :	vfnGPIO_LED_Init
 *  Description          :  Initialize GPIO port connected to LEDs
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/

void vfnGPIO_LED_Init(void)
{
T_SBYTE lsb_PortAinit=0; 		/* variable that controls the bar led */

    /* Data Port E initialization */
	vfnGPIO_Init_channel(LED1,GPIO_OUTPUT,GPIO_OPEN_DRAIN_ENABLE);  /* PE4 --> LED1*/
	vfnGPIO_Output (LED1, 1);
	vfnGPIO_Init_channel(LED2,GPIO_OUTPUT,GPIO_OPEN_DRAIN_ENABLE);  /* PE5 --> LED2*/
	vfnGPIO_Output (LED2, 1);
	vfnGPIO_Init_channel(LED3,GPIO_OUTPUT,GPIO_OPEN_DRAIN_ENABLE);  /* PE6 --> LED3*/
	vfnGPIO_Output (LED3, 1);
	vfnGPIO_Init_channel(LED4,GPIO_OUTPUT,GPIO_OPEN_DRAIN_ENABLE);  /* PE7 --> LED4*/
	vfnGPIO_Output (LED4, 1);
	
	/* Data Port A initialization */
	vfnGPIO_Init_channel(PORTA10,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  /* PE6 --> LED5*/
	vfnGPIO_Output (PORTA10, 0);
	vfnGPIO_Init_channel(PORTA11,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  /* PE7 --> LED6*/
	vfnGPIO_Output (PORTA11, 0);
	
    for(lsb_PortAinit=0; lsb_PortAinit<10; lsb_PortAinit++)  /* PA0 - PA9 --> Bar led */
    {
    	vfnGPIO_Init_channel(lsb_PortAinit,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  
        vfnGPIO_Output (lsb_PortAinit, 1);
    }
}


/**************************************************************
 *  Name                 :	vfnGPIO_BUTTON_Init
 *  Description          :  Initialize GPIO port connected to buttons
 *  Parameters           :  none
 *  Return               :	none
 *  Critical/explanation :  no
 **************************************************************/

void vfnGPIO_BUTTON_Init(void)
{
	vfnGPIO_Init_channel(BUTTON1,GPIO_INPUT,GPIO_OPEN_DRAIN_DISABLE); /* PE0 --> Button1 */
	vfnGPIO_Init_channel(BUTTON2,GPIO_INPUT,GPIO_OPEN_DRAIN_DISABLE); /* PE1 --> Button2 */
	vfnGPIO_Init_channel(BUTTON3,GPIO_INPUT,GPIO_OPEN_DRAIN_DISABLE); /* PE2 --> Button3 */
	vfnGPIO_Init_channel(BUTTON4,GPIO_INPUT,GPIO_OPEN_DRAIN_DISABLE); /* PE3 --> Button4 */	
}