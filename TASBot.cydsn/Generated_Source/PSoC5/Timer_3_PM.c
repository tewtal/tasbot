/*******************************************************************************
* File Name: Timer_3_PM.c
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

#include "Timer_3.h"

/* Check for removal by optimization */
#if !defined(Timer_3_Sync_ctrl_reg__REMOVED)

static Timer_3_BACKUP_STRUCT  Timer_3_backup = {0u};

    
/*******************************************************************************
* Function Name: Timer_3_SaveConfig
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
void Timer_3_SaveConfig(void) 
{
    Timer_3_backup.controlState = Timer_3_Control;
}


/*******************************************************************************
* Function Name: Timer_3_RestoreConfig
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
void Timer_3_RestoreConfig(void) 
{
     Timer_3_Control = Timer_3_backup.controlState;
}


/*******************************************************************************
* Function Name: Timer_3_Sleep
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
void Timer_3_Sleep(void) 
{
    Timer_3_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_3_Wakeup
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
void Timer_3_Wakeup(void)  
{
    Timer_3_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
