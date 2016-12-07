/*******************************************************************************
* File Name: Vis_D0.h  
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

#if !defined(CY_PINS_Vis_D0_H) /* Pins Vis_D0_H */
#define CY_PINS_Vis_D0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vis_D0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vis_D0__PORT == 15 && ((Vis_D0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vis_D0_Write(uint8 value);
void    Vis_D0_SetDriveMode(uint8 mode);
uint8   Vis_D0_ReadDataReg(void);
uint8   Vis_D0_Read(void);
void    Vis_D0_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vis_D0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vis_D0_SetDriveMode() function.
     *  @{
     */
        #define Vis_D0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vis_D0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vis_D0_DM_RES_UP          PIN_DM_RES_UP
        #define Vis_D0_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vis_D0_DM_OD_LO           PIN_DM_OD_LO
        #define Vis_D0_DM_OD_HI           PIN_DM_OD_HI
        #define Vis_D0_DM_STRONG          PIN_DM_STRONG
        #define Vis_D0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vis_D0_MASK               Vis_D0__MASK
#define Vis_D0_SHIFT              Vis_D0__SHIFT
#define Vis_D0_WIDTH              1u

/* Interrupt constants */
#if defined(Vis_D0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vis_D0_SetInterruptMode() function.
     *  @{
     */
        #define Vis_D0_INTR_NONE      (uint16)(0x0000u)
        #define Vis_D0_INTR_RISING    (uint16)(0x0001u)
        #define Vis_D0_INTR_FALLING   (uint16)(0x0002u)
        #define Vis_D0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vis_D0_INTR_MASK      (0x01u) 
#endif /* (Vis_D0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vis_D0_PS                     (* (reg8 *) Vis_D0__PS)
/* Data Register */
#define Vis_D0_DR                     (* (reg8 *) Vis_D0__DR)
/* Port Number */
#define Vis_D0_PRT_NUM                (* (reg8 *) Vis_D0__PRT) 
/* Connect to Analog Globals */                                                  
#define Vis_D0_AG                     (* (reg8 *) Vis_D0__AG)                       
/* Analog MUX bux enable */
#define Vis_D0_AMUX                   (* (reg8 *) Vis_D0__AMUX) 
/* Bidirectional Enable */                                                        
#define Vis_D0_BIE                    (* (reg8 *) Vis_D0__BIE)
/* Bit-mask for Aliased Register Access */
#define Vis_D0_BIT_MASK               (* (reg8 *) Vis_D0__BIT_MASK)
/* Bypass Enable */
#define Vis_D0_BYP                    (* (reg8 *) Vis_D0__BYP)
/* Port wide control signals */                                                   
#define Vis_D0_CTL                    (* (reg8 *) Vis_D0__CTL)
/* Drive Modes */
#define Vis_D0_DM0                    (* (reg8 *) Vis_D0__DM0) 
#define Vis_D0_DM1                    (* (reg8 *) Vis_D0__DM1)
#define Vis_D0_DM2                    (* (reg8 *) Vis_D0__DM2) 
/* Input Buffer Disable Override */
#define Vis_D0_INP_DIS                (* (reg8 *) Vis_D0__INP_DIS)
/* LCD Common or Segment Drive */
#define Vis_D0_LCD_COM_SEG            (* (reg8 *) Vis_D0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vis_D0_LCD_EN                 (* (reg8 *) Vis_D0__LCD_EN)
/* Slew Rate Control */
#define Vis_D0_SLW                    (* (reg8 *) Vis_D0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vis_D0_PRTDSI__CAPS_SEL       (* (reg8 *) Vis_D0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vis_D0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vis_D0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vis_D0_PRTDSI__OE_SEL0        (* (reg8 *) Vis_D0__PRTDSI__OE_SEL0) 
#define Vis_D0_PRTDSI__OE_SEL1        (* (reg8 *) Vis_D0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vis_D0_PRTDSI__OUT_SEL0       (* (reg8 *) Vis_D0__PRTDSI__OUT_SEL0) 
#define Vis_D0_PRTDSI__OUT_SEL1       (* (reg8 *) Vis_D0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vis_D0_PRTDSI__SYNC_OUT       (* (reg8 *) Vis_D0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vis_D0__SIO_CFG)
    #define Vis_D0_SIO_HYST_EN        (* (reg8 *) Vis_D0__SIO_HYST_EN)
    #define Vis_D0_SIO_REG_HIFREQ     (* (reg8 *) Vis_D0__SIO_REG_HIFREQ)
    #define Vis_D0_SIO_CFG            (* (reg8 *) Vis_D0__SIO_CFG)
    #define Vis_D0_SIO_DIFF           (* (reg8 *) Vis_D0__SIO_DIFF)
#endif /* (Vis_D0__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vis_D0__INTSTAT)
    #define Vis_D0_INTSTAT            (* (reg8 *) Vis_D0__INTSTAT)
    #define Vis_D0_SNAP               (* (reg8 *) Vis_D0__SNAP)
    
	#define Vis_D0_0_INTTYPE_REG 		(* (reg8 *) Vis_D0__0__INTTYPE)
#endif /* (Vis_D0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vis_D0_H */


/* [] END OF FILE */
