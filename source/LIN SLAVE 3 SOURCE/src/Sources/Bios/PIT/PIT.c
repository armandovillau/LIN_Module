/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/* MCU-specific derivative */
#include "MCU_derivative.h" 
/* Data types */
#include "typedefs.h"

#include "IntcInterrupts.h"

/* Own Headers */
#include "PIT.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* PIT_Callback, function to be called upon timeout of PIT channel N */
tCallbackFunction PIT_Callback[8];

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    PIT device - Low level initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void PIT_device_init(void) 
{
    PIT.PITMCR.R = 0x00000001;       /* Enable PIT and configure timers to stop in debug mode */
}

/****************************************************************************************************/
/**
* \brief    PIT Channel Low level configuration
* \author   Abraham Tezmol
* \param    uint8_t channel - Channel to be configured
* \param    tCallbackFunction Callback - Function to invoke upon PIT count to zero event
* \return   void
*/
void PIT_channel_configure(uint8_t channel, tCallbackFunction Callback) 
{
    PIT.CH[channel].LDVAL.R = PIT_CHANNEL_VALUE;      /* PIT1 timeout --> Refer to PIT.h file for calculations */
    PIT_Callback[channel]   = Callback;               /* Initialize callback function */
    
    /* Install Interrupt routine for this specific channel */
    INTC_InstallINTCInterruptHandler(PIT_channel_0_isr,59,5);
}

/****************************************************************************************************/
/**
* \brief    PIT channel Low level Start procedure
* \author   Abraham Tezmol
* \param    uint8_t channel - PIT channel to start
* \return   void
*/
void PIT_channel_start(uint8_t channel)
{
    PIT.CH[channel].TCTRL.R = 0x000000003;            /* Enable PIT1 interrupt and make PIT active to count */
}


/****************************************************************************************************/
/**
* \brief    PIT channel Low level Stop procedure
* \author   Abraham Tezmol
* \param    uint8_t channel - PIT channel to stop
* \return   void
*/
void PIT_channel_stop(uint8_t channel)
{
	PIT.CH[channel].TCTRL.R = 0x000000000;            /* Disable PIT channel interrupt and make PIT inactive to count */
}


/***************************************************************************************************/
/**
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
void PIT_channel_0_isr(void)
{
  if (PIT.CH[0].TFLG.B.TIF)
  {
    /* Clear the time-base interrupt flag */
    PIT.CH[0].TFLG.B.TIF = 1;
    
    /*call callback function, if initialized*/
        if( PIT_Callback[0] != NULL )
        {
            PIT_Callback[0]();
        }
  }
}
