/*******************************************************************************
* File Name: ClockCountSel.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_ClockCountSel_H) /* CY_CONTROL_REG_ClockCountSel_H */
#define CY_CONTROL_REG_ClockCountSel_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} ClockCountSel_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    ClockCountSel_Write(uint8 control) ;
uint8   ClockCountSel_Read(void) ;

void ClockCountSel_SaveConfig(void) ;
void ClockCountSel_RestoreConfig(void) ;
void ClockCountSel_Sleep(void) ; 
void ClockCountSel_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define ClockCountSel_Control        (* (reg8 *) ClockCountSel_Sync_ctrl_reg__CONTROL_REG )
#define ClockCountSel_Control_PTR    (  (reg8 *) ClockCountSel_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_ClockCountSel_H */


/* [] END OF FILE */
