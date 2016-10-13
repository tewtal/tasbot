/*******************************************************************************
* File Name: P1_2_PM.c
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

#include "P1_2.h"

static P1_2_BACKUP_STRUCT P1_2_backup =
{
    P1_2_DISABLED,

    ((uint16) P1_2_DEFAULT_A0),
    ((uint16) P1_2_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint16) P1_2_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: P1_2_SaveConfig
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
void P1_2_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    P1_2_backup.saveSrA0Reg   = CY_GET_REG16(P1_2_SHIFT_REG_LSB_PTR);
    P1_2_backup.saveSrA1Reg   = CY_GET_REG16(P1_2_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        P1_2_backup.saveSrIntMask = P1_2_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: P1_2_RestoreConfig
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
void P1_2_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG16(P1_2_SHIFT_REG_LSB_PTR, P1_2_backup.saveSrA0Reg);
    CY_SET_REG16(P1_2_SHIFT_REG_VALUE_LSB_PTR, P1_2_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        P1_2_SR_STATUS_MASK = ((uint8) P1_2_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: P1_2_Sleep
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
void P1_2_Sleep(void) 
{
    P1_2_backup.enableState = ((uint8) P1_2_IS_ENABLED);

    P1_2_Stop();
    P1_2_SaveConfig();
}


/*******************************************************************************
* Function Name: P1_2_Wakeup
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
void P1_2_Wakeup(void) 
{
    P1_2_RestoreConfig();

    if(0u != P1_2_backup.enableState)
    {
        P1_2_Enable();
    }
}


/* [] END OF FILE */
