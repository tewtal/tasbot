/*******************************************************************************
* File Name: VisClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_VisClock_H)
#define CY_CLOCK_VisClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void VisClock_Start(void) ;
void VisClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void VisClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void VisClock_StandbyPower(uint8 state) ;
void VisClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 VisClock_GetDividerRegister(void) ;
void VisClock_SetModeRegister(uint8 modeBitMask) ;
void VisClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 VisClock_GetModeRegister(void) ;
void VisClock_SetSourceRegister(uint8 clkSource) ;
uint8 VisClock_GetSourceRegister(void) ;
#if defined(VisClock__CFG3)
void VisClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 VisClock_GetPhaseRegister(void) ;
#endif /* defined(VisClock__CFG3) */

#define VisClock_Enable()                       VisClock_Start()
#define VisClock_Disable()                      VisClock_Stop()
#define VisClock_SetDivider(clkDivider)         VisClock_SetDividerRegister(clkDivider, 1u)
#define VisClock_SetDividerValue(clkDivider)    VisClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define VisClock_SetMode(clkMode)               VisClock_SetModeRegister(clkMode)
#define VisClock_SetSource(clkSource)           VisClock_SetSourceRegister(clkSource)
#if defined(VisClock__CFG3)
#define VisClock_SetPhase(clkPhase)             VisClock_SetPhaseRegister(clkPhase)
#define VisClock_SetPhaseValue(clkPhase)        VisClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(VisClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define VisClock_CLKEN              (* (reg8 *) VisClock__PM_ACT_CFG)
#define VisClock_CLKEN_PTR          ((reg8 *) VisClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define VisClock_CLKSTBY            (* (reg8 *) VisClock__PM_STBY_CFG)
#define VisClock_CLKSTBY_PTR        ((reg8 *) VisClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define VisClock_DIV_LSB            (* (reg8 *) VisClock__CFG0)
#define VisClock_DIV_LSB_PTR        ((reg8 *) VisClock__CFG0)
#define VisClock_DIV_PTR            ((reg16 *) VisClock__CFG0)

/* Clock MSB divider configuration register. */
#define VisClock_DIV_MSB            (* (reg8 *) VisClock__CFG1)
#define VisClock_DIV_MSB_PTR        ((reg8 *) VisClock__CFG1)

/* Mode and source configuration register */
#define VisClock_MOD_SRC            (* (reg8 *) VisClock__CFG2)
#define VisClock_MOD_SRC_PTR        ((reg8 *) VisClock__CFG2)

#if defined(VisClock__CFG3)
/* Analog clock phase configuration register */
#define VisClock_PHASE              (* (reg8 *) VisClock__CFG3)
#define VisClock_PHASE_PTR          ((reg8 *) VisClock__CFG3)
#endif /* defined(VisClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define VisClock_CLKEN_MASK         VisClock__PM_ACT_MSK
#define VisClock_CLKSTBY_MASK       VisClock__PM_STBY_MSK

/* CFG2 field masks */
#define VisClock_SRC_SEL_MSK        VisClock__CFG2_SRC_SEL_MASK
#define VisClock_MODE_MASK          (~(VisClock_SRC_SEL_MSK))

#if defined(VisClock__CFG3)
/* CFG3 phase mask */
#define VisClock_PHASE_MASK         VisClock__CFG3_PHASE_DLY_MASK
#endif /* defined(VisClock__CFG3) */

#endif /* CY_CLOCK_VisClock_H */


/* [] END OF FILE */
