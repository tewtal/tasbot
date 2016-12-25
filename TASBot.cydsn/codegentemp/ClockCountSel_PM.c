/*******************************************************************************
* File Name: ClockCountSel_PM.c
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

#include "ClockCountSel.h"

/* Check for removal by optimization */
#if !defined(ClockCountSel_Sync_ctrl_reg__REMOVED)

static ClockCountSel_BACKUP_STRUCT  ClockCountSel_backup = {0u};

    
/*******************************************************************************
* Function Name: ClockCountSel_SaveConfig
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
void ClockCountSel_SaveConfig(void) 
{
    ClockCountSel_backup.controlState = ClockCountSel_Control;
}


/*******************************************************************************
* Function Name: ClockCountSel_RestoreConfig
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
void ClockCountSel_RestoreConfig(void) 
{
     ClockCountSel_Control = ClockCountSel_backup.controlState;
}


/*******************************************************************************
* Function Name: ClockCountSel_Sleep
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
void ClockCountSel_Sleep(void) 
{
    ClockCountSel_SaveConfig();
}


/*******************************************************************************
* Function Name: ClockCountSel_Wakeup
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
void ClockCountSel_Wakeup(void)  
{
    ClockCountSel_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
