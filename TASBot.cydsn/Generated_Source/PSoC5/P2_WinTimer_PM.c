/*******************************************************************************
* File Name: P2_WinTimer_PM.c
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

#include "P2_WinTimer.h"

static P2_WinTimer_backupStruct P2_WinTimer_backup;


/*******************************************************************************
* Function Name: P2_WinTimer_SaveConfig
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
*  P2_WinTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void P2_WinTimer_SaveConfig(void) 
{
    #if (!P2_WinTimer_UsingFixedFunction)
        P2_WinTimer_backup.TimerUdb = P2_WinTimer_ReadCounter();
        P2_WinTimer_backup.InterruptMaskValue = P2_WinTimer_STATUS_MASK;
        #if (P2_WinTimer_UsingHWCaptureCounter)
            P2_WinTimer_backup.TimerCaptureCounter = P2_WinTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!P2_WinTimer_UDB_CONTROL_REG_REMOVED)
            P2_WinTimer_backup.TimerControlRegister = P2_WinTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: P2_WinTimer_RestoreConfig
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
*  P2_WinTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void P2_WinTimer_RestoreConfig(void) 
{   
    #if (!P2_WinTimer_UsingFixedFunction)

        P2_WinTimer_WriteCounter(P2_WinTimer_backup.TimerUdb);
        P2_WinTimer_STATUS_MASK =P2_WinTimer_backup.InterruptMaskValue;
        #if (P2_WinTimer_UsingHWCaptureCounter)
            P2_WinTimer_SetCaptureCount(P2_WinTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!P2_WinTimer_UDB_CONTROL_REG_REMOVED)
            P2_WinTimer_WriteControlRegister(P2_WinTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: P2_WinTimer_Sleep
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
*  P2_WinTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void P2_WinTimer_Sleep(void) 
{
    #if(!P2_WinTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(P2_WinTimer_CTRL_ENABLE == (P2_WinTimer_CONTROL & P2_WinTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            P2_WinTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            P2_WinTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    P2_WinTimer_Stop();
    P2_WinTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: P2_WinTimer_Wakeup
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
*  P2_WinTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void P2_WinTimer_Wakeup(void) 
{
    P2_WinTimer_RestoreConfig();
    #if(!P2_WinTimer_UDB_CONTROL_REG_REMOVED)
        if(P2_WinTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                P2_WinTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
