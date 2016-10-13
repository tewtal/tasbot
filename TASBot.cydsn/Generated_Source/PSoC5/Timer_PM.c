/*******************************************************************************
* File Name: Timer_PM.c
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

#include "Timer.h"

/* Check for removal by optimization */
#if !defined(Timer_Sync_ctrl_reg__REMOVED)

static Timer_BACKUP_STRUCT  Timer_backup = {0u};

    
/*******************************************************************************
* Function Name: Timer_SaveConfig
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
void Timer_SaveConfig(void) 
{
    Timer_backup.controlState = Timer_Control;
}


/*******************************************************************************
* Function Name: Timer_RestoreConfig
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
void Timer_RestoreConfig(void) 
{
     Timer_Control = Timer_backup.controlState;
}


/*******************************************************************************
* Function Name: Timer_Sleep
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
void Timer_Sleep(void) 
{
    Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Wakeup
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
void Timer_Wakeup(void)  
{
    Timer_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
