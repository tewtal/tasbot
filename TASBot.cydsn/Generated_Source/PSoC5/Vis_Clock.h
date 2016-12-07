/*******************************************************************************
* File Name: Vis_Clock.h  
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

#if !defined(CY_PINS_Vis_Clock_H) /* Pins Vis_Clock_H */
#define CY_PINS_Vis_Clock_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vis_Clock_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vis_Clock__PORT == 15 && ((Vis_Clock__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vis_Clock_Write(uint8 value);
void    Vis_Clock_SetDriveMode(uint8 mode);
uint8   Vis_Clock_ReadDataReg(void);
uint8   Vis_Clock_Read(void);
void    Vis_Clock_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vis_Clock_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vis_Clock_SetDriveMode() function.
     *  @{
     */
        #define Vis_Clock_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vis_Clock_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vis_Clock_DM_RES_UP          PIN_DM_RES_UP
        #define Vis_Clock_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vis_Clock_DM_OD_LO           PIN_DM_OD_LO
        #define Vis_Clock_DM_OD_HI           PIN_DM_OD_HI
        #define Vis_Clock_DM_STRONG          PIN_DM_STRONG
        #define Vis_Clock_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vis_Clock_MASK               Vis_Clock__MASK
#define Vis_Clock_SHIFT              Vis_Clock__SHIFT
#define Vis_Clock_WIDTH              1u

/* Interrupt constants */
#if defined(Vis_Clock__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vis_Clock_SetInterruptMode() function.
     *  @{
     */
        #define Vis_Clock_INTR_NONE      (uint16)(0x0000u)
        #define Vis_Clock_INTR_RISING    (uint16)(0x0001u)
        #define Vis_Clock_INTR_FALLING   (uint16)(0x0002u)
        #define Vis_Clock_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vis_Clock_INTR_MASK      (0x01u) 
#endif /* (Vis_Clock__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vis_Clock_PS                     (* (reg8 *) Vis_Clock__PS)
/* Data Register */
#define Vis_Clock_DR                     (* (reg8 *) Vis_Clock__DR)
/* Port Number */
#define Vis_Clock_PRT_NUM                (* (reg8 *) Vis_Clock__PRT) 
/* Connect to Analog Globals */                                                  
#define Vis_Clock_AG                     (* (reg8 *) Vis_Clock__AG)                       
/* Analog MUX bux enable */
#define Vis_Clock_AMUX                   (* (reg8 *) Vis_Clock__AMUX) 
/* Bidirectional Enable */                                                        
#define Vis_Clock_BIE                    (* (reg8 *) Vis_Clock__BIE)
/* Bit-mask for Aliased Register Access */
#define Vis_Clock_BIT_MASK               (* (reg8 *) Vis_Clock__BIT_MASK)
/* Bypass Enable */
#define Vis_Clock_BYP                    (* (reg8 *) Vis_Clock__BYP)
/* Port wide control signals */                                                   
#define Vis_Clock_CTL                    (* (reg8 *) Vis_Clock__CTL)
/* Drive Modes */
#define Vis_Clock_DM0                    (* (reg8 *) Vis_Clock__DM0) 
#define Vis_Clock_DM1                    (* (reg8 *) Vis_Clock__DM1)
#define Vis_Clock_DM2                    (* (reg8 *) Vis_Clock__DM2) 
/* Input Buffer Disable Override */
#define Vis_Clock_INP_DIS                (* (reg8 *) Vis_Clock__INP_DIS)
/* LCD Common or Segment Drive */
#define Vis_Clock_LCD_COM_SEG            (* (reg8 *) Vis_Clock__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vis_Clock_LCD_EN                 (* (reg8 *) Vis_Clock__LCD_EN)
/* Slew Rate Control */
#define Vis_Clock_SLW                    (* (reg8 *) Vis_Clock__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vis_Clock_PRTDSI__CAPS_SEL       (* (reg8 *) Vis_Clock__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vis_Clock_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vis_Clock__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vis_Clock_PRTDSI__OE_SEL0        (* (reg8 *) Vis_Clock__PRTDSI__OE_SEL0) 
#define Vis_Clock_PRTDSI__OE_SEL1        (* (reg8 *) Vis_Clock__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vis_Clock_PRTDSI__OUT_SEL0       (* (reg8 *) Vis_Clock__PRTDSI__OUT_SEL0) 
#define Vis_Clock_PRTDSI__OUT_SEL1       (* (reg8 *) Vis_Clock__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vis_Clock_PRTDSI__SYNC_OUT       (* (reg8 *) Vis_Clock__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vis_Clock__SIO_CFG)
    #define Vis_Clock_SIO_HYST_EN        (* (reg8 *) Vis_Clock__SIO_HYST_EN)
    #define Vis_Clock_SIO_REG_HIFREQ     (* (reg8 *) Vis_Clock__SIO_REG_HIFREQ)
    #define Vis_Clock_SIO_CFG            (* (reg8 *) Vis_Clock__SIO_CFG)
    #define Vis_Clock_SIO_DIFF           (* (reg8 *) Vis_Clock__SIO_DIFF)
#endif /* (Vis_Clock__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vis_Clock__INTSTAT)
    #define Vis_Clock_INTSTAT            (* (reg8 *) Vis_Clock__INTSTAT)
    #define Vis_Clock_SNAP               (* (reg8 *) Vis_Clock__SNAP)
    
	#define Vis_Clock_0_INTTYPE_REG 		(* (reg8 *) Vis_Clock__0__INTTYPE)
#endif /* (Vis_Clock__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vis_Clock_H */


/* [] END OF FILE */
