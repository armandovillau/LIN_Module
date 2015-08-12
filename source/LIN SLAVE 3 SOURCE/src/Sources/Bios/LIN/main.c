#include "MPC5606B.h"
#include "IntcInterrupts.h" 

/* main.c: LINFlex program for MPC56xxB */
/* Description: Transmit one message from FlexCAN 0 buf. 0 to FlexCAN C buf. 1 */
/* Oct 30 2009 S Mihalik - initial version */
/* Mar 14 2010 SM - modified initModesAndClock, updated header file */

//#include "MPC5604B_0M27V_0102.h" /* Use proper header file */

void initModesAndClks(void) {
  ME.MER.R = 0x0000001D;          /* Enable DRUN, RUN0, SAFE, RESET modes */
                                  /* Initialize PLL before turning it on: */
/* Use 1 of the next 2 lines depending on crystal frequency: */
  CGM.FMPLL_CR.R = 0x02400100;    /* 8 MHz xtal: Set PLL0 to 64 MHz */   
/*CGM.FMPLL_CR.R = 0x12400100;*/  /* 40 MHz xtal: Set PLL0 to 64 MHz */   
  ME.RUN[0].R = 0x001F0074;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL */
  ME.RUNPC[1].R = 0x00000010; 	  /* Peri. Cfg. 1 settings: only run in RUN0 mode */
  ME.PCTL[48].R = 0x01;           /* MPC56xxB/P/S LINFlex 0: select ME.RUNPC[1] */	
  ME.PCTL[68].R = 0x01;           /* MPC56xxB/S SIUL:  select ME.RUNPC[0] */	
                                  /* Mode Transition to enter RUN0 mode: */
  ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
  ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
  while (ME.GS.B.S_MTRANS) {}     /* Wait for mode transition to complete */    
                                  /* Note: could wait here using timer and/or I_TC IRQ */
  while(ME.GS.B.S_CURRENTMODE != 4) {} /* Verify RUN0 is the current mode */
}

/*Interrupt function when data is received*/
void Intc_LINFLEX_Rx(void)
{ 
/*If slave linflex 0 receives data*/
	if(LINFLEX_0.LINSR.B.RMB == 1)
	{
		LINFLEX_0.LINSR.B.RMB=1;
	}
}

/*Interrupt function when data is tranferred*/

void Intc_LINFLEX_Tx(void)
{

/*if slave linflex 0 transfers data*/
	if(LINFLEX_0.LINSR.B.DTF == 1)
	{
		LINFLEX_0.LINSR.B.DTF=1;
	}
}
/*interrupt function when error detected*/
void Intc_LINFLEX_Err(void)
{
	LINFLEX_0.LINESR.B.BEF=1;
/*	if(LINFLEX_0.LINESR.B.BEF == 1)
	{
		
	}*/
}


void initPeriClkGen(void) 
{
  CGM.SC_DC[0].R = 0x80;           /* MPC56xxB/S: Enable peri set 1 sysclk divided by 1 */
}

   

/*Initializes registers for LINFLEX 0 as slave*/
void initLINFlex_0 (T_ULONG lul_BaudRate) {
 
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
  LINFLEX_0.IFER.R=0x0;
  LINFLEX_0.IFMR.R=0x0	;
  
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
  LINFLEX_0.IFCR[0].B.DFL=0;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[0].B.DIR=0;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[0].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[0].B.ID=0x0F;
  
  
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[0].B.DFL=0;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[0].B.DIR=0;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[0].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[0].B.ID=0x11;
  
  
  
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[0].B.DFL=1;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[0].B.DIR=1;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[0].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[0].B.ID=0x21;
  
  
  
  /*Data Field Lenght*/  
  LINFLEX_0.IFCR[0].B.DFL=6;
  /*Direction set as Receiver*/
  LINFLEX_0.IFCR[0].B.DIR=1;
  /*Set as Classic Checksum*/
  LINFLEX_0.IFCR[0].B.CCS=1;
  /*ID*/
  LINFLEX_0.IFCR[0].B.ID=0x31;
  
  	SIU.PCR[18].R = 0x0400;         /* MPC56xxB: Configure port B2 as LIN0TX */
  SIU.PCR[19].R = 0x0103;         /* MPC56xxB: Configure port B3 as LIN0RX */
  
	
	LINFLEX_0.LINCR1.B.SLEEP = 0;
	
  LINFLEX_0.LINCR1.B.INIT = 0; /* Configure module as LIN master & header */
  
  /*Activate Filters*/
  LINFLEX_0.IFER.R=0xFF;
  
  
}



void transmitLINframe (void) {
  /* Load buffer data most significant bytes */
  LINFLEX_0.BDRM.R = 0x2020206F; 
   /* Load buffer data least significant bytes */
  LINFLEX_0.BDRL.R = 0x6C6C6548;  
  /* Init header:  ID=0x35, 8 B, Tx, enh. cksum*/ 
  LINFLEX_0.BIDR.R = 0x00001E35;  
  /* Request header transmission */
  LINFLEX_0.LINCR2.B.HTRQ = 1;    
}

void main(void) {
  volatile uint32_t IdleCtr = 0; 
  
  initModesAndClks();      /* Initialize mode entries */
  initPeriClkGen();        /* Initialize peripheral clock generation for LINFlex */
  disableWatchdog();       /* Disable watchdog */
  
  INTC_InitINTCInterrupts();
  EXCEP_InitExceptionHandlers();
  
  INTC.MCR.R=0;
  INTC_InstallINTCInterruptHandler(&Intc_LINFLEX_Rx, 79, 10);
  INTC_InstallINTCInterruptHandler(&Intc_LINFLEX_Tx, 80, 10);
  INTC_InstallINTCInterruptHandler(&Intc_LINFLEX_Err, 81, 10);
  
  
  INTC.CPR.R = 0;
  
  initLINFlex_0(9600);         /* Initialize FLEXCAN 0 as master */
  NormalModeLINFLEX_2();
  
  //transmitLINframe();     /* Transmit one frame from master */
  while (1) {IdleCtr++;}   /* Idle loop: increment counter */
}

