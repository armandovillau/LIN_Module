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
#include "LIN_Driver.h"
#include "MPC5606B.h"
#include "IntcInterrupts.h" 


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
T_UBYTE rub_Data_Rx=0;

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */
#define LINFLEX0_RX_Vector 	79
#define LINFLEX0_TX_Vector 	80
#define LINFLEX0_ERR_Vector 81
#define PRIORITY10		    10

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
void initPeriClkGen(void) 
{
  CGM.SC_DC[0].R = 0x80;           /* MPC56xxB/S: Enable peri set 1 sysclk divided by 1 */
 // CGM.SC_DC[2].R = 0x80;          	/* MPC56xxB: Enable peri set 3 sysclk divided by 1 */

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

/*Interrupt function when data is received*/
void Intc_LINFLEX_Rx(void)
{ 
/*If slave linflex 0 receives data*/
	if(LINFLEX_0.LINSR.B.RMB == 1)
	{
		LINFLEX_0.LINSR.B.RMB=0;
	}
	
	if((LINFLEX_0.BIDR.B.ID == 0x0F) || (LINFLEX_0.BIDR.B.ID == 0x12))
	{
		rub_Data_Rx=(T_UBYTE) LINFLEX_0.BDRL.B.DATA0;
	}
	else if((LINFLEX_0.BIDR.B.ID == 0x22) || (LINFLEX_0.BIDR.B.ID == 0x32))
	{
		
	}
	else
	{
		/* Do nothing */
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

/*Interrupt function when data is received*/
T_UBYTE GetLinData(void)
{ 
	return rub_Data_Rx;
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
 
 /*Interrupt function when data is tranferred*/

void Intc_LINFLEX_Tx(void)
{

/*if slave linflex 0 transfers data*/
	if(LINFLEX_0.LINSR.B.DTF == 1)
	{
		LINFLEX_0.LINSR.B.DTF=0;
	}
	if(LINFLEX_0.LINSR.B.RMB == 1)
	{
		LINFLEX_0.LINSR.B.RMB=0;
	}
	
	if((LINFLEX_0.BIDR.B.ID == 0x21) || (LINFLEX_0.BIDR.B.ID == 0x31))
	{
		
	}
	else if((LINFLEX_0.BIDR.B.ID == 0x0F) || (LINFLEX_0.BIDR.B.ID == 0x11))
	{
		
	}
	else
	{
		/* Do nothing */
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
 

/*interrupt function when error detected*/
void Intc_LINFLEX_Err(void)
{
	LINFLEX_0.LINESR.B.BEF=1;

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

/*Initializes registers for LINFLEX 0 as slave*/
void initLINFlex_0 (T_ULONG lul_BaudRate) 
{
  
    T_ULONG lul_LINIBRR=0;
	T_ULONG lul_LINFBRR=0;
	T_ULONG lul_CalculateBaud_Matisa=0;
	T_ULONG lul_CalculateBaud_Counter=0;
	T_ULONG crystal=16000000;
	T_UBYTE lub_Counter=0;
		
  /*Sleep Mode Request Off*/
  LINFLEX_0.LINCR1.B.SLEEP = 0;
  /* Put LINFlex hardware in init mode */
  LINFLEX_0.LINCR1.B.INIT = 1;    
  
  /*sets UART as LIN Mode*/
  LINFLEX_0.UARTCR.B.UART = 0;
  
  /*LIN master lenght break 13 bits*/ 
  LINFLEX_0.LINCR1.B.MBL= 0x03; 
  /*bypass filter, An RX interrupt is generated on identifier not matching any filter*/
  LINFLEX_0.LINCR1.B.BF= 1;
  /*Slave mode ON*/
  LINFLEX_0.LINCR1.B.MME=0;
  /*sets as 11 bit break*/
  LINFLEX_0.LINCR1.B.SBDT=0;
  /*Receive buffer not locked on overrun */
  LINFLEX_0.LINCR1.B.RBLM=0;
  /*Idle on bit error, Bit error does not reset state machine*/
  LINFLEX_0.LINCR2.B.IOBE= 0;
  
  /*With the following lines, matissa and fractional part of Baudrate are calculated*/
  
  lul_LINIBRR=(crystal/(lul_BaudRate*16));
  lul_CalculateBaud_Counter=lul_LINIBRR*100;
  lul_CalculateBaud_Matisa=((crystal*100)/(lul_BaudRate*16));
  lul_CalculateBaud_Matisa=(lul_CalculateBaud_Matisa-lul_CalculateBaud_Counter)*16;
  lul_CalculateBaud_Counter=0;
		
		while(lul_CalculateBaud_Matisa>5)
		{
		    if(lul_CalculateBaud_Matisa>100)
			{
			    lul_CalculateBaud_Matisa=lul_CalculateBaud_Matisa-100;
                lul_CalculateBaud_Counter++;
			}
			else
            {
                lul_CalculateBaud_Matisa=lul_CalculateBaud_Matisa-1;
                lub_Counter++;
                if(lub_Counter>=50)
                {
                    lul_CalculateBaud_Counter++;
                    lul_CalculateBaud_Matisa=0;
                }
            }
		}
		if(lul_CalculateBaud_Counter>15)
		{
			lul_LINIBRR++;
			lul_LINFBRR=0;
			
		}
		else
		{
            
			lul_LINFBRR=lul_CalculateBaud_Counter;
		}
  
  
  
  
  
  
  
  
  
  /* Fraction baud rate divider component */ 
  LINFLEX_0.LINFBRR.R=(T_UBYTE)(lul_LINFBRR);
  /* Mantissa baud rate divider component */
  LINFLEX_0.LINIBRR.R=(T_UWORD)(lul_LINIBRR); 
  
 
  /*deactivate filters to be able to set them manually*/ 
   LINFLEX_0.IFER.R=0x00;
   LINFLEX_0.IFMR.R=0x00;
  
 /*Idle timeout , not reset to idle in tome out event*/
  LINFLEX_0.LINTCSR.B.IOT=0;
  
 
 
 /*Interrupt generated when data received flag (DRF) in LINSR or UARTSR is set.*/
  	LINFLEX_0.LINIER.B.DRIE = 1;	
  /*Interrupt generated when data transmitted flag (DTF) is set in LINSR or UARTSR.*/
	LINFLEX_0.LINIER.B.DTIE = 1;
 /*Interrupt generated when a valid LIN header has been received, that is, HRF bit in LINSR is set.*/
	LINFLEX_0.LINIER.B.HRIE = 1;
	/*Checksum error, Interrupt generated when checksum error flag (CEF) in LINESR is set.  */	
	LINFLEX_0.LINIER.B.CEIE = 1;	
	/* Header error, Interrupt generated on Break Delimiter error, Synch Field error, Identifier field error. */	
	LINFLEX_0.LINIER.B.HEIE = 1;
	/*Bit error Interrupt generated when BEF bit in LINESR is set.  */	
	LINFLEX_0.LINIER.B.BEIE = 0;	/*  */
  
   
    
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[5].B.DFL=0;
  /*Direction set as Receiver*/
	  LINFLEX_0.IFCR[5].B.DIR=0;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[5].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[5].B.ID=0x0F;
  
  
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[4].B.DFL=0;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[4].B.DIR=1;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[4].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[4].B.ID=0x21;
  
  
  
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[2].B.DFL=1;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[2].B.DIR=0;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[2].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[2].B.ID=0x11;
  
  
  
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[3].B.DFL=6;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[3].B.DIR=1;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[3].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[3].B.ID=0x31;
  
  
  
  /*Activate Filters*/
  LINFLEX_0.IFER.R=0x3;

	SIU.PCR[18].R = 0x0400;         /* MPC56xxB: Configure port B2 as LIN0TX */
  SIU.PCR[19].R = 0x0103;         /* MPC56xxB: Configure port B3 as LIN0RX */ 
  
  LINFLEX_0.LINCR1.B.SLEEP = 0;
	
  LINFLEX_0.LINCR1.B.INIT = 0; /* Configure module as LIN master & header */
  
}




 void	IntcInterruptLINFLEXHandlers(void)
 {
  
  /* Configure options of the INTC */
  INTC.MCR.R=0;
  /* Defines interruption function  */
  INTC_InstallINTCInterruptHandler(&Intc_LINFLEX_Rx, LINFLEX0_RX_Vector, 1);
  INTC_InstallINTCInterruptHandler(&Intc_LINFLEX_Tx, LINFLEX0_TX_Vector, 2);
  INTC_InstallINTCInterruptHandler(&Intc_LINFLEX_Err, LINFLEX0_ERR_Vector, 3);
  /* Masking Priority to Zero*/
  INTC.CPR.R = 0;
 }