/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %stdtypedef.h%
* Instance:
* %version:         5 %
* %created_by:      uidl6560 %
* %date_created:    Tue Oct 12 16:40:52 2010 %
*=============================================================================*/
/* DESCRIPTION : Platform software type definitions                           */
/*============================================================================*/
/* FUNCTION COMMENT : supported controller: NEC 78k0 all                      */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/* COPYRIGHT (C) SIEMENS VDO Automotive AG 2004                               */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/* REVISION |   DATE      |                          |      AUTHOR            */
/*--------------------------------------------------------------------------- */
/*
/*============================================================================*/

#ifndef STDTYPEDEF_H                               /* To avoid double inclusion */
#define STDTYPEDEF_H

typedef unsigned char       T_UBYTE;
typedef unsigned short int  T_UWORD;
typedef unsigned long int   T_ULONG;
typedef signed char         T_SBYTE;
typedef signed short int    T_SWORD;
typedef signed long int     T_SLONG;
typedef unsigned short int  T_FLAG_ARRAY;
typedef unsigned int        T_BIT_STRUCT;


/* basic type pointers */
typedef T_UBYTE * PTR_UBYTE ;
typedef T_UWORD * PTR_UWORD;
typedef T_ULONG * PTR_ULONG;
typedef T_SBYTE * PTR_SBYTE ;
typedef T_SWORD * PTR_SWORD;
typedef T_SLONG * PTR_SLONG;


/* Carrier of 8 bits */
/* #pragma pack(1) */
typedef struct {
  unsigned char	bit0:1;
  unsigned char	bit1:1;
  unsigned char	bit2:1;
  unsigned char	bit3:1;
  unsigned char	bit4:1;
  unsigned char	bit5:1;
  unsigned char	bit6:1;
  unsigned char	bit7:1;
}T_BITFLD8;
/* #pragma pack() */


/* Carrier of 16 bits */
/* #pragma pack(2) */
typedef struct {
  unsigned char	bit0:1;
  unsigned char	bit1:1;
  unsigned char	bit2:1;
  unsigned char	bit3:1;
  unsigned char	bit4:1;
  unsigned char	bit5:1;
  unsigned char	bit6:1;
  unsigned char	bit7:1;
  unsigned char	bit8:1;
  unsigned char	bit9:1;
  unsigned char	bit10:1;
  unsigned char	bit11:1;
  unsigned char	bit12:1;
  unsigned char	bit13:1;
  unsigned char	bit14:1;
  unsigned char	bit15:1;
}T_BITFLD16;
/* #pragma pack() */


/* Carrier of 32 bits */
typedef struct {
  unsigned char	bit0:1;
  unsigned char	bit1:1;
  unsigned char	bit2:1;
  unsigned char	bit3:1;
  unsigned char	bit4:1;
  unsigned char	bit5:1;
  unsigned char	bit6:1;
  unsigned char	bit7:1;
  unsigned char	bit8:1;
  unsigned char	bit9:1;
  unsigned char	bit10:1;
  unsigned char	bit11:1;
  unsigned char	bit12:1;
  unsigned char	bit13:1;
  unsigned char	bit14:1;
  unsigned char	bit15:1;
  unsigned char	bit16:1;
  unsigned char	bit17:1;
  unsigned char	bit18:1;
  unsigned char	bit19:1;
  unsigned char	bit20:1;
  unsigned char	bit21:1;
  unsigned char	bit22:1;
  unsigned char	bit23:1;
  unsigned char	bit24:1;
  unsigned char	bit25:1;
  unsigned char	bit26:1;
  unsigned char	bit27:1;
  unsigned char	bit28:1;
  unsigned char	bit29:1;
  unsigned char	bit30:1;
  unsigned char	bit31:1;
}T_BITFLD32;


/* Word with msb and lsb handling */
/* NEC78K0R: Little Endian, LSB first*/
typedef union{
  T_UWORD  wo;
  struct{
    T_UBYTE  lsb;
    T_UBYTE  msb;
  }by;
}T_BYTEFLD;


/* Long with word and byte handling */
typedef union{
  T_ULONG lo;
  struct {
    T_UBYTE lowword_lsb;
    T_UBYTE lowword_msb;
    T_UBYTE highword_lsb;
    T_UBYTE highword_msb;
  } by;

  struct {
    T_UWORD lowword;
    T_UWORD highword;
  } wo;

}T_BYTEFLD32;

/* Carrier of 8 bits with byte handling */
typedef union {
  T_UBYTE by;
  T_BITFLD8 bi;
}T_FLAG8;


/* Carrier of 16 bits with word or byte (msb & lsb) carrier handling */
typedef union {
  T_BYTEFLD cr;
  T_BITFLD16 bi;
}T_FLAG16;


/* Carrier of 32 bits with word or byte (msb & lsb) carrier handling */
typedef union {
  T_BYTEFLD32 cr;
  T_BITFLD32 bi;
}T_FLAG32;


/* Error code type definition */
typedef enum
{
  E_SWP_OK,
  E_ADC_BUSY,
  E_INVALID_TIMER,
  E_TIMER_ALREADY_RUNNING,
  E_TIMER_ALREADY_STOPPED,
  E_EEP_BUSY,
  E_EEP_INIT_FAIL,
  E_EEP_COMP,
  E_EEP_ERROR,
  E_SPI_BUSY,
  E_SPI_NOK,
  E_FORCE_MINDELAY,
  E_FORCE_MAXDELAY,
  E_INVALID_PARAMETER,
  E_CTLRAM_OK,
  E_CTLRAM_NOK
}T_ERROR_CODE;

typedef enum
{
  E_IS_UNDER = 0U,
  E_IS_OVER = 1U
} T_BAT_THRD;

/* register monitoring variables */
/* TAG : SWR_C_CORE_09_005 Covers_SWR_D_CORE_09_005
*/

/* Timer type definitions */

typedef T_UWORD T_FAST_TIMER_DELAY;
typedef T_UBYTE TimerType;
typedef T_UBYTE T_SLOW_TIMER_DELAY;


/* Macros definition */
#define TRUE 1U
#define FALSE 0U
#ifndef NULL
#define NULL 0U
#endif

/* Compiler customization */
/* Memory macros definition */
#define IRAM                             /* RAM declaration into internal RAM */

#define NEAR __near                      /* RAM declaration into near RAM */

#define FAR __far                        /* RAM declaration into far RAM */

#define PRIVATE_DATA static              /* static data definition */

#define PRIVATE_FCT static               /* private function definition */

#define NEAR_FCT __near_func            /* near function definition */

#define FAR_FCT                         /* far function definition */

#define INLINE_FCT                       /* inline function definition */



#endif
