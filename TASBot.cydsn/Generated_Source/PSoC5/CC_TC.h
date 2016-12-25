/*******************************************************************************
* File Name: CC_TC.h  
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

#if !defined(CY_PINS_CC_TC_H) /* Pins CC_TC_H */
#define CY_PINS_CC_TC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CC_TC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CC_TC__PORT == 15 && ((CC_TC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CC_TC_Write(uint8 value);
void    CC_TC_SetDriveMode(uint8 mode);
uint8   CC_TC_ReadDataReg(void);
uint8   CC_TC_Read(void);
void    CC_TC_SetInterruptMode(uint16 position, uint16 mode);
uint8   CC_TC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CC_TC_SetDriveMode() function.
     *  @{
     */
        #define CC_TC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CC_TC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CC_TC_DM_RES_UP          PIN_DM_RES_UP
        #define CC_TC_DM_RES_DWN         PIN_DM_RES_DWN
        #define CC_TC_DM_OD_LO           PIN_DM_OD_LO
        #define CC_TC_DM_OD_HI           PIN_DM_OD_HI
        #define CC_TC_DM_STRONG          PIN_DM_STRONG
        #define CC_TC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CC_TC_MASK               CC_TC__MASK
#define CC_TC_SHIFT              CC_TC__SHIFT
#define CC_TC_WIDTH              1u

/* Interrupt constants */
#if defined(CC_TC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CC_TC_SetInterruptMode() function.
     *  @{
     */
        #define CC_TC_INTR_NONE      (uint16)(0x0000u)
        #define CC_TC_INTR_RISING    (uint16)(0x0001u)
        #define CC_TC_INTR_FALLING   (uint16)(0x0002u)
        #define CC_TC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CC_TC_INTR_MASK      (0x01u) 
#endif /* (CC_TC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CC_TC_PS                     (* (reg8 *) CC_TC__PS)
/* Data Register */
#define CC_TC_DR                     (* (reg8 *) CC_TC__DR)
/* Port Number */
#define CC_TC_PRT_NUM                (* (reg8 *) CC_TC__PRT) 
/* Connect to Analog Globals */                                                  
#define CC_TC_AG                     (* (reg8 *) CC_TC__AG)                       
/* Analog MUX bux enable */
#define CC_TC_AMUX                   (* (reg8 *) CC_TC__AMUX) 
/* Bidirectional Enable */                                                        
#define CC_TC_BIE                    (* (reg8 *) CC_TC__BIE)
/* Bit-mask for Aliased Register Access */
#define CC_TC_BIT_MASK               (* (reg8 *) CC_TC__BIT_MASK)
/* Bypass Enable */
#define CC_TC_BYP                    (* (reg8 *) CC_TC__BYP)
/* Port wide control signals */                                                   
#define CC_TC_CTL                    (* (reg8 *) CC_TC__CTL)
/* Drive Modes */
#define CC_TC_DM0                    (* (reg8 *) CC_TC__DM0) 
#define CC_TC_DM1                    (* (reg8 *) CC_TC__DM1)
#define CC_TC_DM2                    (* (reg8 *) CC_TC__DM2) 
/* Input Buffer Disable Override */
#define CC_TC_INP_DIS                (* (reg8 *) CC_TC__INP_DIS)
/* LCD Common or Segment Drive */
#define CC_TC_LCD_COM_SEG            (* (reg8 *) CC_TC__LCD_COM_SEG)
/* Enable Segment LCD */
#define CC_TC_LCD_EN                 (* (reg8 *) CC_TC__LCD_EN)
/* Slew Rate Control */
#define CC_TC_SLW                    (* (reg8 *) CC_TC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CC_TC_PRTDSI__CAPS_SEL       (* (reg8 *) CC_TC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CC_TC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CC_TC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CC_TC_PRTDSI__OE_SEL0        (* (reg8 *) CC_TC__PRTDSI__OE_SEL0) 
#define CC_TC_PRTDSI__OE_SEL1        (* (reg8 *) CC_TC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CC_TC_PRTDSI__OUT_SEL0       (* (reg8 *) CC_TC__PRTDSI__OUT_SEL0) 
#define CC_TC_PRTDSI__OUT_SEL1       (* (reg8 *) CC_TC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CC_TC_PRTDSI__SYNC_OUT       (* (reg8 *) CC_TC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CC_TC__SIO_CFG)
    #define CC_TC_SIO_HYST_EN        (* (reg8 *) CC_TC__SIO_HYST_EN)
    #define CC_TC_SIO_REG_HIFREQ     (* (reg8 *) CC_TC__SIO_REG_HIFREQ)
    #define CC_TC_SIO_CFG            (* (reg8 *) CC_TC__SIO_CFG)
    #define CC_TC_SIO_DIFF           (* (reg8 *) CC_TC__SIO_DIFF)
#endif /* (CC_TC__SIO_CFG) */

/* Interrupt Registers */
#if defined(CC_TC__INTSTAT)
    #define CC_TC_INTSTAT            (* (reg8 *) CC_TC__INTSTAT)
    #define CC_TC_SNAP               (* (reg8 *) CC_TC__SNAP)
    
	#define CC_TC_0_INTTYPE_REG 		(* (reg8 *) CC_TC__0__INTTYPE)
#endif /* (CC_TC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CC_TC_H */


/* [] END OF FILE */
