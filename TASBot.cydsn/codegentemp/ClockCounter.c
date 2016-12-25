/*******************************************************************************
* File Name: ClockCounter.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ClockCounter.h"

uint8 ClockCounter_initVar = 0u;


/*******************************************************************************
* Function Name: ClockCounter_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void ClockCounter_Init(void) 
{
        #if (!ClockCounter_UsingFixedFunction && !ClockCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!ClockCounter_UsingFixedFunction && !ClockCounter_ControlRegRemoved) */
        
        #if(!ClockCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 ClockCounter_interruptState;
        #endif /* (!ClockCounter_UsingFixedFunction) */
        
        #if (ClockCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            ClockCounter_CONTROL &= ClockCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                ClockCounter_CONTROL2 &= ((uint8)(~ClockCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                ClockCounter_CONTROL3 &= ((uint8)(~ClockCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (ClockCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                ClockCounter_CONTROL |= ClockCounter_ONESHOT;
            #endif /* (ClockCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            ClockCounter_CONTROL2 |= ClockCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            ClockCounter_RT1 &= ((uint8)(~ClockCounter_RT1_MASK));
            ClockCounter_RT1 |= ClockCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            ClockCounter_RT1 &= ((uint8)(~ClockCounter_SYNCDSI_MASK));
            ClockCounter_RT1 |= ClockCounter_SYNCDSI_EN;

        #else
            #if(!ClockCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = ClockCounter_CONTROL & ((uint8)(~ClockCounter_CTRL_CMPMODE_MASK));
            ClockCounter_CONTROL = ctrl | ClockCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = ClockCounter_CONTROL & ((uint8)(~ClockCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != ClockCounter_CAPTURE_MODE_CONF)
                ClockCounter_CONTROL = ctrl | ClockCounter_DEFAULT_CAPTURE_MODE;
            #else
                ClockCounter_CONTROL = ctrl;
            #endif /* 0 != ClockCounter_CAPTURE_MODE */ 
            
            #endif /* (!ClockCounter_ControlRegRemoved) */
        #endif /* (ClockCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!ClockCounter_UsingFixedFunction)
            ClockCounter_ClearFIFO();
        #endif /* (!ClockCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        ClockCounter_WritePeriod(ClockCounter_INIT_PERIOD_VALUE);
        #if (!(ClockCounter_UsingFixedFunction && (CY_PSOC5A)))
            ClockCounter_WriteCounter(ClockCounter_INIT_COUNTER_VALUE);
        #endif /* (!(ClockCounter_UsingFixedFunction && (CY_PSOC5A))) */
        ClockCounter_SetInterruptMode(ClockCounter_INIT_INTERRUPTS_MASK);
        
        #if (!ClockCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)ClockCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            ClockCounter_WriteCompare(ClockCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ClockCounter_interruptState = CyEnterCriticalSection();
            
            ClockCounter_STATUS_AUX_CTRL |= ClockCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(ClockCounter_interruptState);
            
        #endif /* (!ClockCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ClockCounter_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void ClockCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ClockCounter_UsingFixedFunction)
        ClockCounter_GLOBAL_ENABLE |= ClockCounter_BLOCK_EN_MASK;
        ClockCounter_GLOBAL_STBY_ENABLE |= ClockCounter_BLOCK_STBY_EN_MASK;
    #endif /* (ClockCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!ClockCounter_ControlRegRemoved || ClockCounter_UsingFixedFunction)
        ClockCounter_CONTROL |= ClockCounter_CTRL_ENABLE;                
    #endif /* (!ClockCounter_ControlRegRemoved || ClockCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: ClockCounter_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  ClockCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ClockCounter_Start(void) 
{
    if(ClockCounter_initVar == 0u)
    {
        ClockCounter_Init();
        
        ClockCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    ClockCounter_Enable();        
}


/*******************************************************************************
* Function Name: ClockCounter_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void ClockCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!ClockCounter_ControlRegRemoved || ClockCounter_UsingFixedFunction)
        ClockCounter_CONTROL &= ((uint8)(~ClockCounter_CTRL_ENABLE));        
    #endif /* (!ClockCounter_ControlRegRemoved || ClockCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (ClockCounter_UsingFixedFunction)
        ClockCounter_GLOBAL_ENABLE &= ((uint8)(~ClockCounter_BLOCK_EN_MASK));
        ClockCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~ClockCounter_BLOCK_STBY_EN_MASK));
    #endif /* (ClockCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ClockCounter_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void ClockCounter_SetInterruptMode(uint8 interruptsMask) 
{
    ClockCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: ClockCounter_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   ClockCounter_ReadStatusRegister(void) 
{
    return ClockCounter_STATUS;
}


#if(!ClockCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: ClockCounter_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   ClockCounter_ReadControlRegister(void) 
{
    return ClockCounter_CONTROL;
}


/*******************************************************************************
* Function Name: ClockCounter_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    ClockCounter_WriteControlRegister(uint8 control) 
{
    ClockCounter_CONTROL = control;
}

#endif  /* (!ClockCounter_ControlRegRemoved) */


#if (!(ClockCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: ClockCounter_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void ClockCounter_WriteCounter(uint8 counter) \
                                   
{
    #if(ClockCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (ClockCounter_GLOBAL_ENABLE & ClockCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        ClockCounter_GLOBAL_ENABLE |= ClockCounter_BLOCK_EN_MASK;
        CY_SET_REG16(ClockCounter_COUNTER_LSB_PTR, (uint16)counter);
        ClockCounter_GLOBAL_ENABLE &= ((uint8)(~ClockCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(ClockCounter_COUNTER_LSB_PTR, counter);
    #endif /* (ClockCounter_UsingFixedFunction) */
}
#endif /* (!(ClockCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: ClockCounter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 ClockCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(ClockCounter_UsingFixedFunction)
		(void)CY_GET_REG16(ClockCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(ClockCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (ClockCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(ClockCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ClockCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(ClockCounter_STATICCOUNT_LSB_PTR));
    #endif /* (ClockCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ClockCounter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 ClockCounter_ReadCapture(void) 
{
    #if(ClockCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ClockCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(ClockCounter_STATICCOUNT_LSB_PTR));
    #endif /* (ClockCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ClockCounter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void ClockCounter_WritePeriod(uint8 period) 
{
    #if(ClockCounter_UsingFixedFunction)
        CY_SET_REG16(ClockCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(ClockCounter_PERIOD_LSB_PTR, period);
    #endif /* (ClockCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ClockCounter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 ClockCounter_ReadPeriod(void) 
{
    #if(ClockCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ClockCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(ClockCounter_PERIOD_LSB_PTR));
    #endif /* (ClockCounter_UsingFixedFunction) */
}


#if (!ClockCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: ClockCounter_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void ClockCounter_WriteCompare(uint8 compare) \
                                   
{
    #if(ClockCounter_UsingFixedFunction)
        CY_SET_REG16(ClockCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(ClockCounter_COMPARE_LSB_PTR, compare);
    #endif /* (ClockCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ClockCounter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 ClockCounter_ReadCompare(void) 
{
    return (CY_GET_REG8(ClockCounter_COMPARE_LSB_PTR));
}


#if (ClockCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ClockCounter_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ClockCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    ClockCounter_CONTROL &= ((uint8)(~ClockCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    ClockCounter_CONTROL |= compareMode;
}
#endif  /* (ClockCounter_COMPARE_MODE_SOFTWARE) */


#if (ClockCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ClockCounter_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void ClockCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    ClockCounter_CONTROL &= ((uint8)(~ClockCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    ClockCounter_CONTROL |= ((uint8)((uint8)captureMode << ClockCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (ClockCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: ClockCounter_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void ClockCounter_ClearFIFO(void) 
{

    while(0u != (ClockCounter_ReadStatusRegister() & ClockCounter_STATUS_FIFONEMP))
    {
        (void)ClockCounter_ReadCapture();
    }

}
#endif  /* (!ClockCounter_UsingFixedFunction) */


/* [] END OF FILE */

