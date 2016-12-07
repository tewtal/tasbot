/*******************************************************************************
* File Name: Vis_Latch.h  
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

#if !defined(CY_PINS_Vis_Latch_H) /* Pins Vis_Latch_H */
#define CY_PINS_Vis_Latch_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vis_Latch_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vis_Latch__PORT == 15 && ((Vis_Latch__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vis_Latch_Write(uint8 value);
void    Vis_Latch_SetDriveMode(uint8 mode);
uint8   Vis_Latch_ReadDataReg(void);
uint8   Vis_Latch_Read(void);
void    Vis_Latch_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vis_Latch_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vis_Latch_SetDriveMode() function.
     *  @{
     */
        #define Vis_Latch_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vis_Latch_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vis_Latch_DM_RES_UP          PIN_DM_RES_UP
        #define Vis_Latch_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vis_Latch_DM_OD_LO           PIN_DM_OD_LO
        #define Vis_Latch_DM_OD_HI           PIN_DM_OD_HI
        #define Vis_Latch_DM_STRONG          PIN_DM_STRONG
        #define Vis_Latch_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vis_Latch_MASK               Vis_Latch__MASK
#define Vis_Latch_SHIFT              Vis_Latch__SHIFT
#define Vis_Latch_WIDTH              1u

/* Interrupt constants */
#if defined(Vis_Latch__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vis_Latch_SetInterruptMode() function.
     *  @{
     */
        #define Vis_Latch_INTR_NONE      (uint16)(0x0000u)
        #define Vis_Latch_INTR_RISING    (uint16)(0x0001u)
        #define Vis_Latch_INTR_FALLING   (uint16)(0x0002u)
        #define Vis_Latch_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vis_Latch_INTR_MASK      (0x01u) 
#endif /* (Vis_Latch__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vis_Latch_PS                     (* (reg8 *) Vis_Latch__PS)
/* Data Register */
#define Vis_Latch_DR                     (* (reg8 *) Vis_Latch__DR)
/* Port Number */
#define Vis_Latch_PRT_NUM                (* (reg8 *) Vis_Latch__PRT) 
/* Connect to Analog Globals */                                                  
#define Vis_Latch_AG                     (* (reg8 *) Vis_Latch__AG)                       
/* Analog MUX bux enable */
#define Vis_Latch_AMUX                   (* (reg8 *) Vis_Latch__AMUX) 
/* Bidirectional Enable */                                                        
#define Vis_Latch_BIE                    (* (reg8 *) Vis_Latch__BIE)
/* Bit-mask for Aliased Register Access */
#define Vis_Latch_BIT_MASK               (* (reg8 *) Vis_Latch__BIT_MASK)
/* Bypass Enable */
#define Vis_Latch_BYP                    (* (reg8 *) Vis_Latch__BYP)
/* Port wide control signals */                                                   
#define Vis_Latch_CTL                    (* (reg8 *) Vis_Latch__CTL)
/* Drive Modes */
#define Vis_Latch_DM0                    (* (reg8 *) Vis_Latch__DM0) 
#define Vis_Latch_DM1                    (* (reg8 *) Vis_Latch__DM1)
#define Vis_Latch_DM2                    (* (reg8 *) Vis_Latch__DM2) 
/* Input Buffer Disable Override */
#define Vis_Latch_INP_DIS                (* (reg8 *) Vis_Latch__INP_DIS)
/* LCD Common or Segment Drive */
#define Vis_Latch_LCD_COM_SEG            (* (reg8 *) Vis_Latch__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vis_Latch_LCD_EN                 (* (reg8 *) Vis_Latch__LCD_EN)
/* Slew Rate Control */
#define Vis_Latch_SLW                    (* (reg8 *) Vis_Latch__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vis_Latch_PRTDSI__CAPS_SEL       (* (reg8 *) Vis_Latch__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vis_Latch_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vis_Latch__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vis_Latch_PRTDSI__OE_SEL0        (* (reg8 *) Vis_Latch__PRTDSI__OE_SEL0) 
#define Vis_Latch_PRTDSI__OE_SEL1        (* (reg8 *) Vis_Latch__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vis_Latch_PRTDSI__OUT_SEL0       (* (reg8 *) Vis_Latch__PRTDSI__OUT_SEL0) 
#define Vis_Latch_PRTDSI__OUT_SEL1       (* (reg8 *) Vis_Latch__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vis_Latch_PRTDSI__SYNC_OUT       (* (reg8 *) Vis_Latch__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vis_Latch__SIO_CFG)
    #define Vis_Latch_SIO_HYST_EN        (* (reg8 *) Vis_Latch__SIO_HYST_EN)
    #define Vis_Latch_SIO_REG_HIFREQ     (* (reg8 *) Vis_Latch__SIO_REG_HIFREQ)
    #define Vis_Latch_SIO_CFG            (* (reg8 *) Vis_Latch__SIO_CFG)
    #define Vis_Latch_SIO_DIFF           (* (reg8 *) Vis_Latch__SIO_DIFF)
#endif /* (Vis_Latch__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vis_Latch__INTSTAT)
    #define Vis_Latch_INTSTAT            (* (reg8 *) Vis_Latch__INTSTAT)
    #define Vis_Latch_SNAP               (* (reg8 *) Vis_Latch__SNAP)
    
	#define Vis_Latch_0_INTTYPE_REG 		(* (reg8 *) Vis_Latch__0__INTTYPE)
#endif /* (Vis_Latch__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vis_Latch_H */


/* [] END OF FILE */
