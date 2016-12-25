/*******************************************************************************
* File Name: ClockCounter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
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

static ClockCounter_backupStruct ClockCounter_backup;


/*******************************************************************************
* Function Name: ClockCounter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ClockCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ClockCounter_SaveConfig(void) 
{
    #if (!ClockCounter_UsingFixedFunction)

        ClockCounter_backup.CounterUdb = ClockCounter_ReadCounter();

        #if(!ClockCounter_ControlRegRemoved)
            ClockCounter_backup.CounterControlRegister = ClockCounter_ReadControlRegister();
        #endif /* (!ClockCounter_ControlRegRemoved) */

    #endif /* (!ClockCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ClockCounter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ClockCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ClockCounter_RestoreConfig(void) 
{      
    #if (!ClockCounter_UsingFixedFunction)

       ClockCounter_WriteCounter(ClockCounter_backup.CounterUdb);

        #if(!ClockCounter_ControlRegRemoved)
            ClockCounter_WriteControlRegister(ClockCounter_backup.CounterControlRegister);
        #endif /* (!ClockCounter_ControlRegRemoved) */

    #endif /* (!ClockCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ClockCounter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ClockCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ClockCounter_Sleep(void) 
{
    #if(!ClockCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(ClockCounter_CTRL_ENABLE == (ClockCounter_CONTROL & ClockCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            ClockCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            ClockCounter_backup.CounterEnableState = 0u;
        }
    #else
        ClockCounter_backup.CounterEnableState = 1u;
        if(ClockCounter_backup.CounterEnableState != 0u)
        {
            ClockCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!ClockCounter_ControlRegRemoved) */
    
    ClockCounter_Stop();
    ClockCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: ClockCounter_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ClockCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ClockCounter_Wakeup(void) 
{
    ClockCounter_RestoreConfig();
    #if(!ClockCounter_ControlRegRemoved)
        if(ClockCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            ClockCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!ClockCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
