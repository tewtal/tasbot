/*******************************************************************************
* File Name: Vis_H_PM.c
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

#include "Vis_H.h"

/* Check for removal by optimization */
#if !defined(Vis_H_Sync_ctrl_reg__REMOVED)

static Vis_H_BACKUP_STRUCT  Vis_H_backup = {0u};

    
/*******************************************************************************
* Function Name: Vis_H_SaveConfig
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
void Vis_H_SaveConfig(void) 
{
    Vis_H_backup.controlState = Vis_H_Control;
}


/*******************************************************************************
* Function Name: Vis_H_RestoreConfig
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
void Vis_H_RestoreConfig(void) 
{
     Vis_H_Control = Vis_H_backup.controlState;
}


/*******************************************************************************
* Function Name: Vis_H_Sleep
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
void Vis_H_Sleep(void) 
{
    Vis_H_SaveConfig();
}


/*******************************************************************************
* Function Name: Vis_H_Wakeup
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
void Vis_H_Wakeup(void)  
{
    Vis_H_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
