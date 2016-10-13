/*******************************************************************************
* File Name: WinTimer_PM.c
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

#include "WinTimer.h"

static WinTimer_backupStruct WinTimer_backup;


/*******************************************************************************
* Function Name: WinTimer_SaveConfig
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
*  WinTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void WinTimer_SaveConfig(void) 
{
    #if (!WinTimer_UsingFixedFunction)
        WinTimer_backup.TimerUdb = WinTimer_ReadCounter();
        WinTimer_backup.InterruptMaskValue = WinTimer_STATUS_MASK;
        #if (WinTimer_UsingHWCaptureCounter)
            WinTimer_backup.TimerCaptureCounter = WinTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!WinTimer_UDB_CONTROL_REG_REMOVED)
            WinTimer_backup.TimerControlRegister = WinTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: WinTimer_RestoreConfig
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
*  WinTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void WinTimer_RestoreConfig(void) 
{   
    #if (!WinTimer_UsingFixedFunction)

        WinTimer_WriteCounter(WinTimer_backup.TimerUdb);
        WinTimer_STATUS_MASK =WinTimer_backup.InterruptMaskValue;
        #if (WinTimer_UsingHWCaptureCounter)
            WinTimer_SetCaptureCount(WinTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!WinTimer_UDB_CONTROL_REG_REMOVED)
            WinTimer_WriteControlRegister(WinTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: WinTimer_Sleep
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
*  WinTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void WinTimer_Sleep(void) 
{
    #if(!WinTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(WinTimer_CTRL_ENABLE == (WinTimer_CONTROL & WinTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            WinTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            WinTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    WinTimer_Stop();
    WinTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: WinTimer_Wakeup
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
*  WinTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void WinTimer_Wakeup(void) 
{
    WinTimer_RestoreConfig();
    #if(!WinTimer_UDB_CONTROL_REG_REMOVED)
        if(WinTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                WinTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
