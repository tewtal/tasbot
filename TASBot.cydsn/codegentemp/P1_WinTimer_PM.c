/*******************************************************************************
* File Name: P1_WinTimer_PM.c
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

#include "P1_WinTimer.h"

static P1_WinTimer_backupStruct P1_WinTimer_backup;


/*******************************************************************************
* Function Name: P1_WinTimer_SaveConfig
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
*  P1_WinTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void P1_WinTimer_SaveConfig(void) 
{
    #if (!P1_WinTimer_UsingFixedFunction)
        P1_WinTimer_backup.TimerUdb = P1_WinTimer_ReadCounter();
        P1_WinTimer_backup.InterruptMaskValue = P1_WinTimer_STATUS_MASK;
        #if (P1_WinTimer_UsingHWCaptureCounter)
            P1_WinTimer_backup.TimerCaptureCounter = P1_WinTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!P1_WinTimer_UDB_CONTROL_REG_REMOVED)
            P1_WinTimer_backup.TimerControlRegister = P1_WinTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: P1_WinTimer_RestoreConfig
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
*  P1_WinTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void P1_WinTimer_RestoreConfig(void) 
{   
    #if (!P1_WinTimer_UsingFixedFunction)

        P1_WinTimer_WriteCounter(P1_WinTimer_backup.TimerUdb);
        P1_WinTimer_STATUS_MASK =P1_WinTimer_backup.InterruptMaskValue;
        #if (P1_WinTimer_UsingHWCaptureCounter)
            P1_WinTimer_SetCaptureCount(P1_WinTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!P1_WinTimer_UDB_CONTROL_REG_REMOVED)
            P1_WinTimer_WriteControlRegister(P1_WinTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: P1_WinTimer_Sleep
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
*  P1_WinTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void P1_WinTimer_Sleep(void) 
{
    #if(!P1_WinTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(P1_WinTimer_CTRL_ENABLE == (P1_WinTimer_CONTROL & P1_WinTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            P1_WinTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            P1_WinTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    P1_WinTimer_Stop();
    P1_WinTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: P1_WinTimer_Wakeup
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
*  P1_WinTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void P1_WinTimer_Wakeup(void) 
{
    P1_WinTimer_RestoreConfig();
    #if(!P1_WinTimer_UDB_CONTROL_REG_REMOVED)
        if(P1_WinTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                P1_WinTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
