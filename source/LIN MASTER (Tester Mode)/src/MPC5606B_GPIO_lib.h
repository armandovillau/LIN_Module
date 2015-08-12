/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %MPC5606B_GPIO_lib.h%
* Instance:         1
* %version:         1.3 %
* %created_by:      Michele Balbi %
* %date_created:    02 July 2015 %
*=============================================================================*/
/* DESCRIPTION : Provides needed defines and macros to manage GPIO pins and   */
/*               ports.                                                       */
/*============================================================================*/
/* FUNCTION COMMENT : The GPIO library makes it easier to configure GPIOs.    */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 02/07/2015  |                               | Michele Balbi    */
/* First Draft of file.                                          			  */
/*----------------------------------------------------------------------------*/
/*  1.1      | 06/07/2015  |                               | Michele Balbi    */
/* Added GPIO macros to control alt functions and parallel writes.            */
/*----------------------------------------------------------------------------*/
/*  1.2      | 17/07/2015  |                               | Michele Balbi    */
/* Added GPIO_Init() function prototype to export it.                         */
/*----------------------------------------------------------------------------*/
/*  1.3      | 04/08/2015  |                               | Michele Balbi    */
/* Added GPIO_ENABLE_IBE(port) macro.				                          */
/*----------------------------------------------------------------------------*/
/*  1.4      | 05/08/2015  |                               | Michele Balbi    */
/* Changed pin defines since they were substituting other defines in MCU .h   */
/*============================================================================*/

#ifndef MPC5606B_GPIO_LIB
#define MPC5606B_GPIO_LIB

/* Includes */
/* -------- */
#include "MPC5606B.h"

/* Mappping pin number to GPIO[n] */

#define PORTA0 0
#define PORTA1 1
#define PORTA2 2
#define PORTA3 3
#define PORTA4 4
#define PORTA5 5
#define PORTA6 6
#define PORTA7 7
#define PORTA8 8
#define PORTA9 9
#define PORTA10 10
#define PORTA11 11
#define PORTA12 12
#define PORTA13 13
#define PORTA14 14
#define PORTA15 15

#define PORTB0 16
#define PORTB1 17
#define PORTB2 18
#define PORTB3 19
#define PORTB4 20
#define PORTB5 21
#define PORTB6 22
#define PORTB7 23
#define PORTB8 24
#define PORTB9 25
#define PORTB10 26
#define PORTB11 27
#define PORTB12 28
#define PORTB13 29
#define PORTB14 30
#define PORTB15 31

#define PORTC0 32
#define PORTC1 33
#define PORTC2 34
#define PORTC3 35
#define PORTC4 36
#define PORTC5 37
#define PORTC6 38
#define PORTC7 39
#define PORTC8 40
#define PORTC9 41
#define PORTC10 42
#define PORTC11 43
#define PORTC12 44
#define PORTC13 45
#define PORTC14 46
#define PORTC15 47

#define PORTD0 48
#define PORTD1 49
#define PORTD2 50
#define PORTD3 51
#define PORTD4 52
#define PORTD5 53
#define PORTD6 54
#define PORTD7 55
#define PORTD8 56
#define PORTD9 57
#define PORTD10 58
#define PORTD11 59
#define PORTD12 60
#define PORTD13 61
#define PORTD14 62
#define PORTD15 63

#define PORTE0 64
#define PORTE1 65
#define PORTE2 66
#define PORTE3 67
#define PORTE4 68
#define PORTE5 69
#define PORTE6 70
#define PORTE7 71
#define PORTE8 72
#define PORTE9 73
#define PORTE10 74
#define PORTE11 75
#define PORTE12 76
#define PORTE13 77
#define PORTE14 78
#define PORTE15 79

#define PORTF0 80
#define PORTF1 81
#define PORTF2 82
#define PORTF3 83
#define PORTF4 84
#define PORTF5 85
#define PORTF6 86
#define PORTF7 87
#define PORTF8 88
#define PORTF9 89
#define PORTF10 90
#define PORTF11 91
#define PORTF12 92
#define PORTF13 93
#define PORTF14 94
#define PORTF15 95

#define PORTG0 96
#define PORTG1 97
#define PORTG2 98
#define PORTG3 99
#define PORTG4 100
#define PORTG5 101
#define PORTG6 102
#define PORTG7 103
#define PORTG8 104
#define PORTG9 105
#define PORTG10 106
#define PORTG11 107
#define PORTG12 108
#define PORTG13 109
#define PORTG14 110
#define PORTG15 111

#define PORTH0 112
#define PORTH1 113
#define PORTH2 114
#define PORTH3 115
#define PORTH4 116
#define PORTH5 117
#define PORTH6 118
#define PORTH7 119
#define PORTH8 120
#define PORTH9 121
#define PORTH10 122
#define PORTH11 123


/*#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7
#define PA8 8
#define PA9 9
#define PA10 10
#define PA11 11
#define PA12 12
#define PA13 13
#define PA14 14
#define PA15 15

#define PB0 16
#define PB1 17
#define PB2 18
#define PB3 19
#define PB4 20
#define PB5 21
#define PB6 22
#define PB7 23
#define PB8 24
#define PB9 25
#define PB10 26
#define PB11 27
#define PB12 28
#define PB13 29
#define PB14 30
#define PB15 31

#define PC0 32
#define PC1 33
#define PC2 34
#define PC3 35
#define PC4 36
#define PC5 37
#define PC6 38
#define PC7 39
#define PC8 40
#define PC9 41
#define PC10 42
#define PC11 43
#define PC12 44
#define PC13 45
#define PC14 46
#define PC15 47

#define PD0 48
#define PD1 49
#define PD2 50
#define PD3 51
#define PD4 52
#define PD5 53
#define PD6 54
#define PD7 55
#define PD8 56
#define PD9 57
#define PD10 58
#define PD11 59
#define PD12 60
#define PD13 61
#define PD14 62
#define PD15 63

#define PE0 64
#define PE1 65
#define PE2 66
#define PE3 67
#define PE4 68
#define PE5 69
#define PE6 70
#define PE7 71
#define PE8 72
#define PE9 73
#define PE10 74
#define PE11 75
#define PE12 76
#define PE13 77
#define PE14 78
#define PE15 79

#define PF0 80
#define PF1 81
#define PF2 82
#define PF3 83
#define PF4 84
#define PF5 85
#define PF6 86
#define PF7 87
#define PF8 88
#define PF9 89
#define PF10 90
#define PF11 91
#define PF12 92
#define PF13 93
#define PF14 94
#define PF15 95

#define PG0 96
#define PG1 97
#define PG2 98
#define PG3 99
#define PG4 100
#define PG5 101
#define PG6 102
#define PG7 103
#define PG8 104
#define PG9 105
#define PG10 106
#define PG11 107
#define PG12 108
#define PG13 109
#define PG14 110
#define PG15 111

#define PH0 112
#define PH1 113
#define PH2 114
#define PH3 115
#define PH4 116
#define PH5 117
#define PH6 118
#define PH7 119
#define PH8 120
#define PH9 121
#define PH10 122
#define PH11 123*/

/* Map peripherals */

/* Defines for GPIO configurations */


/* Macros for GPIO config */

/* PCR[x] register

- 1 bit
- 1 bit. SMC. Safe Mode Control.
- 1 bit. APC. Analog Pad Control.
- 1 bit.
- 2 bits. PA. Pad Output Assignement.
- 1 bit. OBE. Output Buffer Enable.
- 1 bit. IBE. Input Buffer Enable.

- 2 bits.
- 1 bit. ODE. Open Drain Output Enable.
- 2 bits.
- 1 bit. SRC. Slew-rate Control.
- 1 bit. WPE. Weak Pull Up/Down Enable.
- 1 bit. WPS. Weak Pull Up/Down Select.

*/

#define GPIO_AS_OUTPUT(port)			(SIU.PCR[(port)].R = 0x0200)
#define GPIO_ALT_MODE_0(port)			(SIU.PCR[(port)].B.PA = 0)
#define GPIO_ALT_MODE_1(port)			(SIU.PCR[(port)].B.PA = 1)
#define GPIO_ALT_MODE_2(port)			(SIU.PCR[(port)].B.PA = 2)
#define GPIO_ALT_MODE_3(port)			(SIU.PCR[(port)].B.PA = 3)
#define OUTPUT_HIGH(port)				(SIU.GPDO[(port)].B.PDO = 1)
#define OUTPUT_LOW(port)				(SIU.GPDO[(port)].B.PDO = 0)
#define GPIO_IBE_ENABLE(port)			(SIU.PCR[(port)].B.IBE = 1)

#define GPIO_AS_INPUT(port)				(SIU.PCR[(port)].R = 0x0103)
#define INPUT_STATE(port)				(SIU.GPDI[(port)].B.PDI)

#define GPIO_AS_ANALOG(port)			(SIU.PCR[(port)].R = 0x2000)

/*#define GPIO_PORTA_OUTPUT(value)		(SIU.MPGPDO[0].R = (0xFFFF|value))
#define GPIO_PORTA_OUTPUT(value)		(SIU.MPGPDO[0].R = (0xFFFF|value))
#define GPIO_PORTA_OUTPUT(value)		(SIU.MPGPDO[0].R = (0xFFFF|value))
#define GPIO_PORTA_OUTPUT(value)		(SIU.MPGPDO[0].R = (0xFFFF|value))*/

/* LED Macros */

#define LED_ON(channel)				(SIU.GPDO[(channel)].B.PDO = 0)
#define LED_OFF(channel)            (SIU.GPDO[(channel)].B.PDO = 1)
#define LED_TOGGLE(channel)         (SIU.GPDO[(channel)].B.PDO ^= 1) 


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
extern void GPIO_Init(void);

/* Functions macros */


/* Exported defines */




#endif
