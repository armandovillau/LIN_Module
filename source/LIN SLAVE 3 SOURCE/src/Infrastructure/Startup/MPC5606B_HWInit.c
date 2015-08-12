
/*
 *
 * FILE : MPC5606B_HWInit.c
 *
 * DESCRIPTION:
 *  This file contains all MPC5606B derivative needed initializations, 
 *  and all initializations for the MPC5606B boards which are supported.
 *  This includes setting up the External Bus Interface to allow access
 *  to memory on the external bus, and ensuring there is a valid entry in
 *  the MMU for the external memory access.
 */

/*---------------------------------------------------------------------------*/
/* Includes                                                                  */
/*---------------------------------------------------------------------------*/

#include "MPC5606B.h"      /* MPC56xx platform development header            */
#include "MPC5606B_HWInit.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************/
/* MPC5606B derivative specific hardware initialization */
/*******************************************************/

/* Symbol L2SRAM_LOCATION is defined in the application linker command 
   file (.lcf)  It is defined to the start of the internal SRAM in the 
   MPC5606B. 
*/
/*lint -esym(752, L2SRAM_LOCATION) */
extern long L2SRAM_LOCATION;  


__asm void INIT_Derivative(void) 
{
nofralloc
    /* Disable WatchDog*/
    // *(volatile unsigned int*)0xfff38010 = 0x0000c520; 
    e_lis r9,0x0001
    e_add16i r9,r9,-15072
    e_lis r8,0xfff4
    e_stw r9,-32752(r8)

    //  *(volatile unsigned int*) 0xfff38010 = 0x0000d928; 
    e_lis r9,0x0001
    e_add16i r9,r9,-9944
    e_lis r8,0xfff4
    e_stw r9,-32752(r8)
    // *(volatile unsigned int*) 0xfff38000 = 0xff00000A; 
    e_lis r3,0xff00
    se_addi r3,0x000a
    e_lis r8,0xfff4
    e_stw r3,-32768(r8)
    
    /* SRAM initialization code*/
    lis r11,L2SRAM_LOCATION@h
    ori r11,r11,L2SRAM_LOCATION@l

    li r12,640        				/* Loops to cover 80K SRAM; 80k/4 bytes/32 GPRs = 640 */
    mtctr r12

    init_l2sram_loop:
        stmw r0,0(r11)        /* Write 32 GPRs to SRAM                     */
        addi r11,r11,128      /* Inc the ram ptr; 32 GPRs * 4 bytes = 128B */
        bdnz init_l2sram_loop /* Loop for 80k of SRAM                      */

    blr
}


#ifdef __cplusplus
}
#endif
