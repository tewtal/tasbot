/*******************************************************************************
* File Name: ConsolePort_4_WinTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "ConsolePort_4_WinTimer.h"

static ConsolePort_4_WinTimer_backupStruct ConsolePort_4_WinTimer_backup;


/*******************************************************************************
* Function Name: ConsolePort_4_WinTimer_SaveConfig
********************************************************************************
*
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
*  ConsolePort_4_WinTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ConsolePort_4_WinTimer_SaveConfig(void) 
{
    #if (!ConsolePort_4_WinTimer_UsingFixedFunction)
        ConsolePort_4_WinTimer_backup.TimerUdb = ConsolePort_4_WinTimer_ReadCounter();
        ConsolePort_4_WinTimer_backup.InterruptMaskValue = ConsolePort_4_WinTimer_STATUS_MASK;
        #if (ConsolePort_4_WinTimer_UsingHWCaptureCounter)
            ConsolePort_4_WinTimer_backup.TimerCaptureCounter = ConsolePort_4_WinTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!ConsolePort_4_WinTimer_UDB_CONTROL_REG_REMOVED)
            ConsolePort_4_WinTimer_backup.TimerControlRegister = ConsolePort_4_WinTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: ConsolePort_4_WinTimer_RestoreConfig
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
*  ConsolePort_4_WinTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ConsolePort_4_WinTimer_RestoreConfig(void) 
{   
    #if (!ConsolePort_4_WinTimer_UsingFixedFunction)

        ConsolePort_4_WinTimer_WriteCounter(ConsolePort_4_WinTimer_backup.TimerUdb);
        ConsolePort_4_WinTimer_STATUS_MASK =ConsolePort_4_WinTimer_backup.InterruptMaskValue;
        #if (ConsolePort_4_WinTimer_UsingHWCaptureCounter)
            ConsolePort_4_WinTimer_SetCaptureCount(ConsolePort_4_WinTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!ConsolePort_4_WinTimer_UDB_CONTROL_REG_REMOVED)
            ConsolePort_4_WinTimer_WriteControlRegister(ConsolePort_4_WinTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: ConsolePort_4_WinTimer_Sleep
********************************************************************************
*
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
*  ConsolePort_4_WinTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void ConsolePort_4_WinTimer_Sleep(void) 
{
    #if(!ConsolePort_4_WinTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(ConsolePort_4_WinTimer_CTRL_ENABLE == (ConsolePort_4_WinTimer_CONTROL & ConsolePort_4_WinTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            ConsolePort_4_WinTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            ConsolePort_4_WinTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    ConsolePort_4_WinTimer_Stop();
    ConsolePort_4_WinTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: ConsolePort_4_WinTimer_Wakeup
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
*  ConsolePort_4_WinTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ConsolePort_4_WinTimer_Wakeup(void) 
{
    ConsolePort_4_WinTimer_RestoreConfig();
    #if(!ConsolePort_4_WinTimer_UDB_CONTROL_REG_REMOVED)
        if(ConsolePort_4_WinTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                ConsolePort_4_WinTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
