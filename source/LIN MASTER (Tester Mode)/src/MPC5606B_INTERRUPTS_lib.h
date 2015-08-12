/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %MPC5606B_INTERRUPTS_lib.h%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    08 July 2015 %
*=============================================================================*/
/* DESCRIPTION : Provides needed defines and macros to manage interrupts.     */
/*============================================================================*/
/* FUNCTION COMMENT : The INTERRUPTS library makes it easier to configure and */  
/*					  use the interrupts.                                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 08/07/2015  |                               | Michele Balbi    */
/* First Draft of file.                                          			  */
/*============================================================================*/

#ifndef MPC5606B_INTERRUPTS_LIB
#define MPC5606B_INTERRUPTS_LIB

#include "MPC5606B.h"

/* Interrupt Vectors */

#define RTC_Vector 	38
#define API_Vector 	39

#define EXT0_Vector 41
#define EXT1_Vector 42
#define EXT2_Vector 43

#define WAKEUP0_Vector 	46
#define WAKEUP1_Vector 	47
#define WAKEUP2_Vector 	48
#define WAKEUP3_Vector 	49

#define PIT0_Vector 59
#define PIT1_Vector 60
#define PIT2_Vector 61
#define PIT3_Vector 127
#define PIT4_Vector 128
#define PIT5_Vector 129
#define PIT6_Vector 130
#define PIT7_Vector 131

#define LINFLEX0_RX_Vector 	79
#define LINFLEX0_TX_Vector 	80
#define LINFLEX0_ERR_Vector 81

#define LINFLEX1_RX_Vector 	99
#define LINFLEX1_TX_Vector 	100
#define LINFLEX1_ERR_Vector 101

#define LINFLEX2_RX_Vector 	119
#define LINFLEX2_TX_Vector 	120
#define LINFLEX2_ERR_Vector 121

#define LINFLEX3_RX_Vector 	122
#define LINFLEX3_TX_Vector 	123
#define LINFLEX3_ERR_Vector 124

#define ADC0_EOC_Vector 	62
#define ADC0_WD_Vector 		64
#define ADC1_EOC_Vector 	82
#define ADC1_WD_Vector 		84


/* Interrupt Macros and Defines */

#define	EXTINT0		0
#define	EXTINT1		1
#define	EXTINT2		2
#define	EXTINT3		3
#define	EXTINT4		4
#define	EXTINT5		5
#define	EXTINT6		6
#define	EXTINT7		7
#define	EXTINT8		8
#define	EXTINT9		9
#define	EXTINT10	10
#define	EXTINT11	11
#define	EXTINT12	12
#define	EXTINT13	13
#define	EXTINT14	14
#define	EXTINT15	15
#define	EXTINT16	16
#define	EXTINT17	17
#define	EXTINT18	18
#define	EXTINT19	19
#define	EXTINT20	20
#define	EXTINT21	21
#define	EXTINT22	22
#define	EXTINT23	23

#define	PRIORITY0	0
#define	PRIORITY1	1
#define	PRIORITY2	2
#define	PRIORITY3	3
#define	PRIORITY4	4
#define	PRIORITY5	5
#define	PRIORITY6	6
#define	PRIORITY7	7
#define	PRIORITY8	8
#define	PRIORITY9	9
#define	PRIORITY10	10
#define	PRIORITY11	11
#define	PRIORITY12	12
#define	PRIORITY13	13
#define	PRIORITY14	14
#define	PRIORITY15	15

#define INT_SW_VECTOR_MODE()			(INTC.MCR.R = 0x00000000u)
#define INT_SET_CPR(priority)			(INTC.CPR.R = (priority))
#define INT_ENABLE_INTS()				(INTC.CPR.R = 0)
#define INT_DISABLE_INTS()				(INTC.CPR.R = 15)

#define EXTINT_ENABLE(int_num)			(SIU.IRER.B.IRE##int_num = 1)
#define EXTINT_FALLING_EDGE(int_num)	(SIU.IFEER.B.IFEE##int_num = 1)
#define EXTINT_RISING_EDGE(int_num)		(SIU.IFEER.B.IREE##int_num = 1)
#define EXTINT_CLEAR_INT_FLAG(int_num)	(SIU.ISR.B.EIF##int_num = 1)
#define EXTINT_GET_FLAG(int_num)		(SIU.ISR.B.EIF##int_num)



#endif
