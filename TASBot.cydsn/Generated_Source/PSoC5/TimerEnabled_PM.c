/*******************************************************************************
* File Name: TimerEnabled_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TimerEnabled.h"

/* Check for removal by optimization */
#if !defined(TimerEnabled_Sync_ctrl_reg__REMOVED)

static TimerEnabled_BACKUP_STRUCT  TimerEnabled_backup = {0u};

    
/*******************************************************************************
* Function Name: TimerEnabled_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TimerEnabled_SaveConfig(void) 
{
    TimerEnabled_backup.controlState = TimerEnabled_Control;
}


/*******************************************************************************
* Function Name: TimerEnabled_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void TimerEnabled_RestoreConfig(void) 
{
     TimerEnabled_Control = TimerEnabled_backup.controlState;
}


/*******************************************************************************
* Function Name: TimerEnabled_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TimerEnabled_Sleep(void) 
{
    TimerEnabled_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerEnabled_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TimerEnabled_Wakeup(void)  
{
    TimerEnabled_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
