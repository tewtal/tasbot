/*******************************************************************************
* File Name: P4_D0.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_P4_D0_ALIASES_H) /* Pins P4_D0_ALIASES_H */
#define CY_PINS_P4_D0_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define P4_D0_0			(P4_D0__0__PC)
#define P4_D0_0_INTR	((uint16)((uint16)0x0001u << P4_D0__0__SHIFT))

#define P4_D0_1			(P4_D0__1__PC)
#define P4_D0_1_INTR	((uint16)((uint16)0x0001u << P4_D0__1__SHIFT))

#define P4_D0_INTR_ALL	 ((uint16)(P4_D0_0_INTR| P4_D0_1_INTR))

#endif /* End Pins P4_D0_ALIASES_H */


/* [] END OF FILE */
