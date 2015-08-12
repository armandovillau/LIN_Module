#include "MPC5606B.h"
#include "conti_typedefs.h"
#include "MPC5606B_GPIO_lib.h"
#include "MPC5606B_ClkInit.h"
#include "MPC5606B_INTERRUPTS_lib.h"

#define BUTTON0 SIU.GPDI[64].R
#define BUTTON1 SIU.GPDI[65].R
#define BUTTON2 SIU.GPDI[66].R
#define BUTTON3 SIU.GPDI[67].R

#define LED0 SIU.GPDO[68].R
#define LED1 SIU.GPDO[69].R
#define LED2 SIU.GPDO[70].R
#define LED3 SIU.GPDO[71].R

#define on 0
#define off 1
#define frec 9000000

T_UBYTE bla=0;

void delay_ms(int sec){		/* Delay fucntion that evaluate the delays in mili seconds units */
	int n;
	for(n = 0; n<(sec*(frec/1000)); n++){
		//do nothing just wait
	}
}

void LIN2_Error(void){
	LINFLEX_2.LINESR.B.BEF=1;
}

void LIN0_TXCompleted(void){
	if(LINFLEX_0.LINSR.B.DTF==1){
		bla=1;
		
		LINFLEX_0.LINSR.B.DTF=1;
	}else{
		LINFLEX_0.LINCR2.B.DTRQ=1;
	}
}

void LIN0_RXCompleted(void){
	if(LINFLEX_0.LINSR.B.RMB==1){
		bla=1;
		LINFLEX_0.LINSR.B.RMB=1;
		LINFLEX_0.LINSR.B.DRF=1;
	}
}

void LIN2_TXCompleted(void){
	if(LINFLEX_2.LINSR.B.DTF==1){
		bla=1;
		
		LINFLEX_2.LINSR.B.DTF=1;
	}
}

void LIN2_RXCompleted(void){
	if(LINFLEX_2.LINSR.B.RMB==1){
		bla=1;
		LINFLEX_2.LINSR.B.RMB=1;
		LINFLEX_2.LINSR.B.DRF=1;
	}	
}

void transmitLINframe_send_data(T_UBYTE ID, T_UBYTE CMD) {
  LINFLEX_2.BDRM.R = 0x00000000;  /* Load buffer data most significant bytes */
  LINFLEX_2.BDRL.R = CMD;  /* Load buffer data least significant bytes */   /*  CMD */
  LINFLEX_2.BIDR.B.DFL = 0x0;	  /* 1 byte data transmission */
  LINFLEX_2.BIDR.B.DIR = 1;
  LINFLEX_2.BIDR.B.ID = ID;      /* ID */
  LINFLEX_2.LINCR2.B.HTRQ = 1;    /* Request header transmission */
}

void transmitLINframe_ask_data(void) {
  /*LINFLEX_2.BDRM.R = 0x00000000;*/  /* Load buffer data most significant bytes */
  /*LINFLEX_2.BDRL.R = 0x000000A8; */ /* Load buffer data least significant bytes */
  LINFLEX_2.BIDR.B.DFL = 0x1;	  /* 1+1 byte data transmission */
  LINFLEX_2.BIDR.B.DIR = 0;
  LINFLEX_2.BIDR.B.ID = 0x20;
  LINFLEX_2.LINCR2.B.HTRQ = 1;    /* Request header transmission */
}

int main(void) {
	
	initModesAndClock();    /* Initialize mode entries and system clock */
	disableWatchdog();      /* Disable watchdog */
	initPeriClkGen();       /* Initialize peripheral clock generation for DSPIs */
	
	GPIO_Init();
	
	INT_SW_VECTOR_MODE();
	
	INTC_InstallINTCInterruptHandler(&LIN0_TXCompleted, LINFLEX0_TX_Vector, PRIORITY10);
	INTC_InstallINTCInterruptHandler(&LIN0_RXCompleted, LINFLEX0_RX_Vector, PRIORITY10);
	INTC_InstallINTCInterruptHandler(&LIN2_TXCompleted, LINFLEX2_TX_Vector, PRIORITY10);
	INTC_InstallINTCInterruptHandler(&LIN2_RXCompleted, LINFLEX2_RX_Vector, PRIORITY10);	
	INTC_InstallINTCInterruptHandler(&LIN2_Error, LINFLEX2_ERR_Vector, PRIORITY10);	
	
	
	INTC_InitINTCInterrupts();
 	INT_ENABLE_INTS();
 	
 	
 	
 	/* LINFLEX2 will be master */
 	/* LINFLEX0 will be slave  */
 	LINFLEX_0.LINCR1.B.SLEEP = 0;
 	LINFLEX_0.LINCR1.B.INIT = 1;
 	LINFLEX_2.LINCR1.B.SLEEP = 0;
 	LINFLEX_2.LINCR1.B.INIT = 1;
 	LINFLEX_0.UARTCR.B.UART = 0;
 	LINFLEX_0.LINCR1.B.BF = 1; 		/* Generate RX int even if no matched filters */
 	LINFLEX_0.LINCR1.B.MME = 0;
 	LINFLEX_0.LINCR1.B.SBDT = 0;
 	LINFLEX_0.LINCR2.B.IOBE = 0;
 	LINFLEX_0.LINTCSR.B.IOT = 0;
 	
 	LINFLEX_2.UARTCR.B.UART = 0;
 	LINFLEX_2.LINCR1.B.MME = 1;
 	LINFLEX_2.LINCR1.B.MBL = 0x3; 	/* 13-bit master break */
 	LINFLEX_2.LINCR1.B.BF = 0; 		/* Generate RX int even if no matched filters */
  	LINFLEX_2.LINCR2.B.IOBE = 0;
  	LINFLEX_2.LINTCSR.B.IOT = 0;
  	
 	
 	LINFLEX_2.LINIER.B.DRIE = 1;	/* Data reception */
	LINFLEX_2.LINIER.B.DTIE = 1;	/* Data transmission */
	LINFLEX_2.LINIER.B.HRIE = 1;	/*  */	
	LINFLEX_2.LINIER.B.CEIE = 1;	/*  */	
	LINFLEX_2.LINIER.B.HEIE = 1;	/*  */
	LINFLEX_2.LINIER.B.BEIE = 1;	/*  */
	
	LINFLEX_0.LINIER.B.DRIE = 1;	/* Data reception */
	LINFLEX_0.LINIER.B.DTIE = 1;	/* Data transmission */
	LINFLEX_0.LINIER.B.HRIE = 1;	/*  */	
	LINFLEX_0.LINIER.B.CEIE = 1;	/*  */	
	LINFLEX_0.LINIER.B.HEIE = 1;	/*  */	
	LINFLEX_0.LINIER.B.BEIE = 0;	/*  */
 	
 	/* 4 filters are configured for the IDs 0xCF, 0x50, 0x20 and 0xF0 */
 	
 	LINFLEX_0.IFER.R = 0x0; 		/* Deactivate filters 0, 1, 2 and 3 */
 	LINFLEX_0.IFMR.R = 0x0;			/* List mode selected */
 	
 	LINFLEX_0.IFCR[0].B.DFL = 0;	/* 0+1 bytes data field */
 	LINFLEX_0.IFCR[0].B.DIR = 0;	/* RX */
 	LINFLEX_0.IFCR[0].B.CCS = 0;	/* Enhaced checksum */
 	LINFLEX_0.IFCR[0].B.ID = 0x0F;	/* 0x50 w/o parity bits */
 	
 	LINFLEX_0.IFCR[1].B.DFL = 0;	/* 0+1 bytes data field */
 	LINFLEX_0.IFCR[1].B.DIR = 0;	/* RX */
 	LINFLEX_0.IFCR[1].B.CCS = 0;	/* Enhaced checksum */
 	LINFLEX_0.IFCR[1].B.ID = 0x10;	/* 0x50 w/o parity bits */
 	
 	LINFLEX_0.IFCR[2].B.DFL = 1;	/* 0+1 bytes data field */
 	LINFLEX_0.IFCR[2].B.DIR = 1;	/* TX */
 	LINFLEX_0.IFCR[2].B.CCS = 0;	/* Enhaced checksum */
 	LINFLEX_0.IFCR[2].B.ID = 0x20;	/* 0x20 w/o parity bits */
 	
 	LINFLEX_0.IFCR[3].B.DFL = 0x6;	/* 0+1 bytes data field */
 	LINFLEX_0.IFCR[3].B.DIR = 1;	/* TX */
 	LINFLEX_0.IFCR[3].B.CCS = 0;	/* Enhaced checksum */
 	LINFLEX_0.IFCR[3].B.ID = 0x30;	/* 0xF0 w/o parity bits */
 	
 	LINFLEX_0.IFER.B.FACT = 0xFF; 		/* Active filters 0, 1, 2 and 3 */
 		
 	LINFLEX_0.BDRM.R = 0x00000000;  /* Load buffer data most significant bytes */
  	LINFLEX_0.BDRL.R = 0x00000DAAD;  /* Load buffer data least significant bytes */
 	
 	
 	/* Setting LIN baudrate */
 	LINFLEX_2.LINFBRR.R = 3u;
	LINFLEX_2.LINIBRR.R = 104u;
	LINFLEX_0.LINFBRR.R = 3u;
	LINFLEX_0.LINIBRR.R = 104u;
 	
 	LINFLEX_2.LINCR1.B.INIT = 0; 	/* LINFLEX normal mode */
 	LINFLEX_0.LINCR1.B.INIT = 0; 	/* LINFLEX normal mode */
 	
 	
  	while(1){
  		
  		if(BUTTON0 == !on){
    		transmitLINframe_send_data(0x0F,1);		/* Command All, ON*/
    		delay_ms(250);
    	}
    	
    	else if(BUTTON1 == !on){	//
    		transmitLINframe_send_data(0x0F,2);		/* Command All, OFF */
    		delay_ms(250);
    	}
    	
    	else if(BUTTON2 == !on){
    		transmitLINframe_send_data(0x0F,3);		/* Command All, Toggle*/
    		delay_ms(250);
    	}
    	
    	else if(BUTTON3 == !on){
    		transmitLINframe_send_data(0x12,3);		/* Slave 3, All */
    		delay_ms(250);
    	}
    	else{
    		//Do nothing
    	}
  		
  	}
}