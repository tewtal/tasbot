/*******************************************************************************
* File Name: ConsolePort_1_RegD2.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_ConsolePort_1_RegD2_H)
#define CY_SHIFTREG_ConsolePort_1_RegD2_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ShiftReg_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define ConsolePort_1_RegD2_FIFO_SIZE          (4u)
#define ConsolePort_1_RegD2_USE_INPUT_FIFO     (0u)
#define ConsolePort_1_RegD2_USE_OUTPUT_FIFO    (0u)
#define ConsolePort_1_RegD2_SR_SIZE            (16u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint16 saveSrA0Reg;
    uint16 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint16 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} ConsolePort_1_RegD2_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  ConsolePort_1_RegD2_Start(void)                              ;
void  ConsolePort_1_RegD2_Stop(void)                               ;
void  ConsolePort_1_RegD2_Init(void)                               ;
void  ConsolePort_1_RegD2_Enable(void)                             ;
void  ConsolePort_1_RegD2_RestoreConfig(void)                      ;
void  ConsolePort_1_RegD2_SaveConfig(void)                         ;
void  ConsolePort_1_RegD2_Sleep(void)                              ;
void  ConsolePort_1_RegD2_Wakeup(void)                             ;
void  ConsolePort_1_RegD2_EnableInt(void)                          ;
void  ConsolePort_1_RegD2_DisableInt(void)                         ;
void  ConsolePort_1_RegD2_SetIntMode(uint8 interruptSource)        ;
uint8 ConsolePort_1_RegD2_GetIntStatus(void)                       ;
void  ConsolePort_1_RegD2_WriteRegValue(uint16 shiftData) \
                                                                ;
uint16 ConsolePort_1_RegD2_ReadRegValue(void) ;
uint8    ConsolePort_1_RegD2_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != ConsolePort_1_RegD2_USE_INPUT_FIFO)
    cystatus ConsolePort_1_RegD2_WriteData(uint16 shiftData) \
                                                                ;
#endif /* (0u != ConsolePort_1_RegD2_USE_INPUT_FIFO) */

#if(0u != ConsolePort_1_RegD2_USE_OUTPUT_FIFO)
    uint16 ConsolePort_1_RegD2_ReadData(void) ;
#endif /* (0u != ConsolePort_1_RegD2_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 ConsolePort_1_RegD2_initVar;


/***************************************
*           API Constants
***************************************/

#define ConsolePort_1_RegD2_LOAD                   (0x01u)
#define ConsolePort_1_RegD2_STORE                  (0x02u)
#define ConsolePort_1_RegD2_RESET                  (0x04u)

#define ConsolePort_1_RegD2_IN_FIFO                (0x01u)
#define ConsolePort_1_RegD2_OUT_FIFO               (0x02u)

#define ConsolePort_1_RegD2_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define ConsolePort_1_RegD2_RET_FIFO_NOT_EMPTY     (0x01u)

#define ConsolePort_1_RegD2_RET_FIFO_PARTIAL       (0x01u)
#define ConsolePort_1_RegD2_RET_FIFO_EMPTY         (0x02u)
#define ConsolePort_1_RegD2_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ConsolePort_1_RegD2__LEFT 0
#define ConsolePort_1_RegD2__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define ConsolePort_1_RegD2_SR_MASK    (0xFFFFu) /* Unsigned is added to parameter */
#define ConsolePort_1_RegD2_INT_SRC    (1u)
#define ConsolePort_1_RegD2_DIRECTION  (0u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define ConsolePort_1_RegD2_SR_CONTROL_REG (* (reg8 *) \
                                           ConsolePort_1_RegD2_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define ConsolePort_1_RegD2_SR_CONTROL_PTR (  (reg8 *) \
                                           ConsolePort_1_RegD2_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define ConsolePort_1_RegD2_SR_STATUS_REG      (* (reg8 *) ConsolePort_1_RegD2_bSR_StsReg__STATUS_REG)
#define ConsolePort_1_RegD2_SR_STATUS_PTR      (  (reg8 *) ConsolePort_1_RegD2_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define ConsolePort_1_RegD2_SR_STATUS_MASK_REG (* (reg8 *) ConsolePort_1_RegD2_bSR_StsReg__MASK_REG)
#define ConsolePort_1_RegD2_SR_STATUS_MASK_PTR (  (reg8 *) ConsolePort_1_RegD2_bSR_StsReg__MASK_REG)

/* Aux control register */
#define ConsolePort_1_RegD2_SR_AUX_CONTROL_REG (* (reg8 *) ConsolePort_1_RegD2_bSR_StsReg__STATUS_AUX_CTL_REG)
#define ConsolePort_1_RegD2_SR_AUX_CONTROL_PTR (  (reg8 *) ConsolePort_1_RegD2_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define ConsolePort_1_RegD2_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define ConsolePort_1_RegD2_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__F0_REG )

    #define ConsolePort_1_RegD2_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__A0_REG )

    #define ConsolePort_1_RegD2_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__A1_REG )

    #define ConsolePort_1_RegD2_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__F1_REG )

#else
    #if(ConsolePort_1_RegD2_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define ConsolePort_1_RegD2_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__F0_REG )

        #define ConsolePort_1_RegD2_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__A0_REG )

        #define ConsolePort_1_RegD2_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__A1_REG )

        #define ConsolePort_1_RegD2_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__F1_REG )

    #elif(ConsolePort_1_RegD2_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define ConsolePort_1_RegD2_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__16BIT_F0_REG )

        #define ConsolePort_1_RegD2_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__16BIT_A0_REG )

        #define ConsolePort_1_RegD2_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__16BIT_A1_REG )

        #define ConsolePort_1_RegD2_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(ConsolePort_1_RegD2_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define ConsolePort_1_RegD2_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__F0_REG )

        #define ConsolePort_1_RegD2_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__A0_REG )

        #define ConsolePort_1_RegD2_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__A1_REG )

        #define ConsolePort_1_RegD2_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define ConsolePort_1_RegD2_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__32BIT_F0_REG )

        #define ConsolePort_1_RegD2_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__32BIT_A0_REG )

        #define ConsolePort_1_RegD2_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__32BIT_A1_REG )

        #define ConsolePort_1_RegD2_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  ConsolePort_1_RegD2_bSR_sC16_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (ConsolePort_1_RegD2_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define ConsolePort_1_RegD2_INTERRUPTS_ENABLE      (0x10u)
#define ConsolePort_1_RegD2_LOAD_INT_EN            (0x01u)
#define ConsolePort_1_RegD2_STORE_INT_EN           (0x02u)
#define ConsolePort_1_RegD2_RESET_INT_EN           (0x04u)
#define ConsolePort_1_RegD2_CLK_EN                 (0x01u)

#define ConsolePort_1_RegD2_RESET_INT_EN_MASK      (0xFBu)
#define ConsolePort_1_RegD2_LOAD_INT_EN_MASK       (0xFEu)
#define ConsolePort_1_RegD2_STORE_INT_EN_MASK      (0xFDu)
#define ConsolePort_1_RegD2_INTS_EN_MASK           (0x07u)

#define ConsolePort_1_RegD2_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != ConsolePort_1_RegD2_USE_INPUT_FIFO)

    #define ConsolePort_1_RegD2_IN_FIFO_MASK       (0x18u)

    #define ConsolePort_1_RegD2_IN_FIFO_FULL       (0x00u)
    #define ConsolePort_1_RegD2_IN_FIFO_EMPTY      (0x01u)
    #define ConsolePort_1_RegD2_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define ConsolePort_1_RegD2_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != ConsolePort_1_RegD2_USE_INPUT_FIFO) */

#define ConsolePort_1_RegD2_OUT_FIFO_MASK          (0x60u)

#define ConsolePort_1_RegD2_OUT_FIFO_EMPTY         (0x00u)
#define ConsolePort_1_RegD2_OUT_FIFO_FULL          (0x01u)
#define ConsolePort_1_RegD2_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define ConsolePort_1_RegD2_OUT_FIFO_NOT_EMPTY     (0x02u)

#define ConsolePort_1_RegD2_IN_FIFO_SHIFT_MASK     (0x03u)
#define ConsolePort_1_RegD2_OUT_FIFO_SHIFT_MASK    (0x05u)

#define ConsolePort_1_RegD2_DISABLED               (0u)
#define ConsolePort_1_RegD2_DEFAULT_A0             (0u)
#define ConsolePort_1_RegD2_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define ConsolePort_1_RegD2_IS_ENABLED         (0u != (ConsolePort_1_RegD2_SR_CONTROL & ConsolePort_1_RegD2_CLK_EN))

#define ConsolePort_1_RegD2_GET_OUT_FIFO_STS   ((ConsolePort_1_RegD2_SR_STATUS & ConsolePort_1_RegD2_OUT_FIFO_MASK) >> \
                                              ConsolePort_1_RegD2_OUT_FIFO_SHIFT_MASK)

#define ConsolePort_1_RegD2_GET_IN_FIFO_STS    ((ConsolePort_1_RegD2_SR_STATUS & ConsolePort_1_RegD2_IN_FIFO_MASK)  >> \
                                              ConsolePort_1_RegD2_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define ConsolePort_1_RegD2_SR_CONTROL     (ConsolePort_1_RegD2_SR_CONTROL_REG)
#define ConsolePort_1_RegD2_SR_STATUS      (ConsolePort_1_RegD2_SR_STATUS_REG)
#define ConsolePort_1_RegD2_SR_STATUS_MASK (ConsolePort_1_RegD2_SR_STATUS_MASK_REG)
#define ConsolePort_1_RegD2_SR_AUX_CONTROL (ConsolePort_1_RegD2_SR_AUX_CONTROL_REG)

#define ConsolePort_1_RegD2_IN_FIFO_SHFT_MASK  (ConsolePort_1_RegD2_IN_FIFO_SHIFT_MASK)
#define ConsolePort_1_RegD2_OUT_FIFO_SHFT_MASK (ConsolePort_1_RegD2_OUT_FIFO_SHFIT_MASK)

#define ConsolePort_1_RegD2_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_ConsolePort_1_RegD2_H) */


/* [] END OF FILE */
