/*******************************************************************************
* File Name: ConsolePort_4_RegD0_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ConsolePort_4_RegD0.h"

static ConsolePort_4_RegD0_BACKUP_STRUCT ConsolePort_4_RegD0_backup =
{
    ConsolePort_4_RegD0_DISABLED,

    ((uint16) ConsolePort_4_RegD0_DEFAULT_A0),
    ((uint16) ConsolePort_4_RegD0_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint16) ConsolePort_4_RegD0_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ConsolePort_4_RegD0_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    ConsolePort_4_RegD0_backup.saveSrA0Reg   = CY_GET_REG16(ConsolePort_4_RegD0_SHIFT_REG_LSB_PTR);
    ConsolePort_4_RegD0_backup.saveSrA1Reg   = CY_GET_REG16(ConsolePort_4_RegD0_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        ConsolePort_4_RegD0_backup.saveSrIntMask = ConsolePort_4_RegD0_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_4_RegD0_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG16(ConsolePort_4_RegD0_SHIFT_REG_LSB_PTR, ConsolePort_4_RegD0_backup.saveSrA0Reg);
    CY_SET_REG16(ConsolePort_4_RegD0_SHIFT_REG_VALUE_LSB_PTR, ConsolePort_4_RegD0_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        ConsolePort_4_RegD0_SR_STATUS_MASK = ((uint8) ConsolePort_4_RegD0_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ConsolePort_4_RegD0_Sleep(void) 
{
    ConsolePort_4_RegD0_backup.enableState = ((uint8) ConsolePort_4_RegD0_IS_ENABLED);

    ConsolePort_4_RegD0_Stop();
    ConsolePort_4_RegD0_SaveConfig();
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_4_RegD0_Wakeup(void) 
{
    ConsolePort_4_RegD0_RestoreConfig();

    if(0u != ConsolePort_4_RegD0_backup.enableState)
    {
        ConsolePort_4_RegD0_Enable();
    }
}


/* [] END OF FILE */
