/*******************************************************************************
* File Name: P1_Clock.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_P1_Clock_H) /* Pins P1_Clock_H */
#define CY_PINS_P1_Clock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P1_Clock_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P1_Clock__PORT == 15 && ((P1_Clock__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P1_Clock_Write(uint8 value);
void    P1_Clock_SetDriveMode(uint8 mode);
uint8   P1_Clock_ReadDataReg(void);
uint8   P1_Clock_Read(void);
void    P1_Clock_SetInterruptMode(uint16 position, uint16 mode);
uint8   P1_Clock_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P1_Clock_SetDriveMode() function.
     *  @{
     */
        #define P1_Clock_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P1_Clock_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P1_Clock_DM_RES_UP          PIN_DM_RES_UP
        #define P1_Clock_DM_RES_DWN         PIN_DM_RES_DWN
        #define P1_Clock_DM_OD_LO           PIN_DM_OD_LO
        #define P1_Clock_DM_OD_HI           PIN_DM_OD_HI
        #define P1_Clock_DM_STRONG          PIN_DM_STRONG
        #define P1_Clock_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P1_Clock_MASK               P1_Clock__MASK
#define P1_Clock_SHIFT              P1_Clock__SHIFT
#define P1_Clock_WIDTH              1u

/* Interrupt constants */
#if defined(P1_Clock__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P1_Clock_SetInterruptMode() function.
     *  @{
     */
        #define P1_Clock_INTR_NONE      (uint16)(0x0000u)
        #define P1_Clock_INTR_RISING    (uint16)(0x0001u)
        #define P1_Clock_INTR_FALLING   (uint16)(0x0002u)
        #define P1_Clock_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P1_Clock_INTR_MASK      (0x01u) 
#endif /* (P1_Clock__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P1_Clock_PS                     (* (reg8 *) P1_Clock__PS)
/* Data Register */
#define P1_Clock_DR                     (* (reg8 *) P1_Clock__DR)
/* Port Number */
#define P1_Clock_PRT_NUM                (* (reg8 *) P1_Clock__PRT) 
/* Connect to Analog Globals */                                                  
#define P1_Clock_AG                     (* (reg8 *) P1_Clock__AG)                       
/* Analog MUX bux enable */
#define P1_Clock_AMUX                   (* (reg8 *) P1_Clock__AMUX) 
/* Bidirectional Enable */                                                        
#define P1_Clock_BIE                    (* (reg8 *) P1_Clock__BIE)
/* Bit-mask for Aliased Register Access */
#define P1_Clock_BIT_MASK               (* (reg8 *) P1_Clock__BIT_MASK)
/* Bypass Enable */
#define P1_Clock_BYP                    (* (reg8 *) P1_Clock__BYP)
/* Port wide control signals */                                                   
#define P1_Clock_CTL                    (* (reg8 *) P1_Clock__CTL)
/* Drive Modes */
#define P1_Clock_DM0                    (* (reg8 *) P1_Clock__DM0) 
#define P1_Clock_DM1                    (* (reg8 *) P1_Clock__DM1)
#define P1_Clock_DM2                    (* (reg8 *) P1_Clock__DM2) 
/* Input Buffer Disable Override */
#define P1_Clock_INP_DIS                (* (reg8 *) P1_Clock__INP_DIS)
/* LCD Common or Segment Drive */
#define P1_Clock_LCD_COM_SEG            (* (reg8 *) P1_Clock__LCD_COM_SEG)
/* Enable Segment LCD */
#define P1_Clock_LCD_EN                 (* (reg8 *) P1_Clock__LCD_EN)
/* Slew Rate Control */
#define P1_Clock_SLW                    (* (reg8 *) P1_Clock__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P1_Clock_PRTDSI__CAPS_SEL       (* (reg8 *) P1_Clock__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P1_Clock_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P1_Clock__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P1_Clock_PRTDSI__OE_SEL0        (* (reg8 *) P1_Clock__PRTDSI__OE_SEL0) 
#define P1_Clock_PRTDSI__OE_SEL1        (* (reg8 *) P1_Clock__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P1_Clock_PRTDSI__OUT_SEL0       (* (reg8 *) P1_Clock__PRTDSI__OUT_SEL0) 
#define P1_Clock_PRTDSI__OUT_SEL1       (* (reg8 *) P1_Clock__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P1_Clock_PRTDSI__SYNC_OUT       (* (reg8 *) P1_Clock__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P1_Clock__SIO_CFG)
    #define P1_Clock_SIO_HYST_EN        (* (reg8 *) P1_Clock__SIO_HYST_EN)
    #define P1_Clock_SIO_REG_HIFREQ     (* (reg8 *) P1_Clock__SIO_REG_HIFREQ)
    #define P1_Clock_SIO_CFG            (* (reg8 *) P1_Clock__SIO_CFG)
    #define P1_Clock_SIO_DIFF           (* (reg8 *) P1_Clock__SIO_DIFF)
#endif /* (P1_Clock__SIO_CFG) */

/* Interrupt Registers */
#if defined(P1_Clock__INTSTAT)
    #define P1_Clock_INTSTAT            (* (reg8 *) P1_Clock__INTSTAT)
    #define P1_Clock_SNAP               (* (reg8 *) P1_Clock__SNAP)
    
	#define P1_Clock_0_INTTYPE_REG 		(* (reg8 *) P1_Clock__0__INTTYPE)
#endif /* (P1_Clock__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P1_Clock_H */


/* [] END OF FILE */
