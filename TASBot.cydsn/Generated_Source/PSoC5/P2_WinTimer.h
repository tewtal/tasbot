/*******************************************************************************
* File Name: P2_WinTimer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_P2_WinTimer_H)
#define CY_Timer_v2_60_P2_WinTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 P2_WinTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define P2_WinTimer_Resolution                 16u
#define P2_WinTimer_UsingFixedFunction         0u
#define P2_WinTimer_UsingHWCaptureCounter      0u
#define P2_WinTimer_SoftwareCaptureMode        0u
#define P2_WinTimer_SoftwareTriggerMode        0u
#define P2_WinTimer_UsingHWEnable              0u
#define P2_WinTimer_EnableTriggerMode          0u
#define P2_WinTimer_InterruptOnCaptureCount    0u
#define P2_WinTimer_RunModeUsed                1u
#define P2_WinTimer_ControlRegRemoved          0u

#if defined(P2_WinTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define P2_WinTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (P2_WinTimer_UsingFixedFunction)
    #define P2_WinTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define P2_WinTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End P2_WinTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!P2_WinTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (P2_WinTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!P2_WinTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}P2_WinTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    P2_WinTimer_Start(void) ;
void    P2_WinTimer_Stop(void) ;

void    P2_WinTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   P2_WinTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define P2_WinTimer_GetInterruptSource() P2_WinTimer_ReadStatusRegister()

#if(!P2_WinTimer_UDB_CONTROL_REG_REMOVED)
    uint8   P2_WinTimer_ReadControlRegister(void) ;
    void    P2_WinTimer_WriteControlRegister(uint8 control) ;
#endif /* (!P2_WinTimer_UDB_CONTROL_REG_REMOVED) */

uint16  P2_WinTimer_ReadPeriod(void) ;
void    P2_WinTimer_WritePeriod(uint16 period) ;
uint16  P2_WinTimer_ReadCounter(void) ;
void    P2_WinTimer_WriteCounter(uint16 counter) ;
uint16  P2_WinTimer_ReadCapture(void) ;
void    P2_WinTimer_SoftwareCapture(void) ;

#if(!P2_WinTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (P2_WinTimer_SoftwareCaptureMode)
        void    P2_WinTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!P2_WinTimer_UsingFixedFunction) */

    #if (P2_WinTimer_SoftwareTriggerMode)
        void    P2_WinTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (P2_WinTimer_SoftwareTriggerMode) */

    #if (P2_WinTimer_EnableTriggerMode)
        void    P2_WinTimer_EnableTrigger(void) ;
        void    P2_WinTimer_DisableTrigger(void) ;
    #endif /* (P2_WinTimer_EnableTriggerMode) */


    #if(P2_WinTimer_InterruptOnCaptureCount)
        void    P2_WinTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (P2_WinTimer_InterruptOnCaptureCount) */

    #if (P2_WinTimer_UsingHWCaptureCounter)
        void    P2_WinTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   P2_WinTimer_ReadCaptureCount(void) ;
    #endif /* (P2_WinTimer_UsingHWCaptureCounter) */

    void P2_WinTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void P2_WinTimer_Init(void)          ;
void P2_WinTimer_Enable(void)        ;
void P2_WinTimer_SaveConfig(void)    ;
void P2_WinTimer_RestoreConfig(void) ;
void P2_WinTimer_Sleep(void)         ;
void P2_WinTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define P2_WinTimer__B_TIMER__CM_NONE 0
#define P2_WinTimer__B_TIMER__CM_RISINGEDGE 1
#define P2_WinTimer__B_TIMER__CM_FALLINGEDGE 2
#define P2_WinTimer__B_TIMER__CM_EITHEREDGE 3
#define P2_WinTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define P2_WinTimer__B_TIMER__TM_NONE 0x00u
#define P2_WinTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define P2_WinTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define P2_WinTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define P2_WinTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define P2_WinTimer_INIT_PERIOD             2499u
#define P2_WinTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << P2_WinTimer_CTRL_CAP_MODE_SHIFT))
#define P2_WinTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << P2_WinTimer_CTRL_TRIG_MODE_SHIFT))
#if (P2_WinTimer_UsingFixedFunction)
    #define P2_WinTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << P2_WinTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << P2_WinTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define P2_WinTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << P2_WinTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << P2_WinTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << P2_WinTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (P2_WinTimer_UsingFixedFunction) */
#define P2_WinTimer_INIT_CAPTURE_COUNT      (2u)
#define P2_WinTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << P2_WinTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (P2_WinTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define P2_WinTimer_STATUS         (*(reg8 *) P2_WinTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define P2_WinTimer_STATUS_MASK    (*(reg8 *) P2_WinTimer_TimerHW__SR0 )
    #define P2_WinTimer_CONTROL        (*(reg8 *) P2_WinTimer_TimerHW__CFG0)
    #define P2_WinTimer_CONTROL2       (*(reg8 *) P2_WinTimer_TimerHW__CFG1)
    #define P2_WinTimer_CONTROL2_PTR   ( (reg8 *) P2_WinTimer_TimerHW__CFG1)
    #define P2_WinTimer_RT1            (*(reg8 *) P2_WinTimer_TimerHW__RT1)
    #define P2_WinTimer_RT1_PTR        ( (reg8 *) P2_WinTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define P2_WinTimer_CONTROL3       (*(reg8 *) P2_WinTimer_TimerHW__CFG2)
        #define P2_WinTimer_CONTROL3_PTR   ( (reg8 *) P2_WinTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define P2_WinTimer_GLOBAL_ENABLE  (*(reg8 *) P2_WinTimer_TimerHW__PM_ACT_CFG)
    #define P2_WinTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) P2_WinTimer_TimerHW__PM_STBY_CFG)

    #define P2_WinTimer_CAPTURE_LSB         (* (reg16 *) P2_WinTimer_TimerHW__CAP0 )
    #define P2_WinTimer_CAPTURE_LSB_PTR       ((reg16 *) P2_WinTimer_TimerHW__CAP0 )
    #define P2_WinTimer_PERIOD_LSB          (* (reg16 *) P2_WinTimer_TimerHW__PER0 )
    #define P2_WinTimer_PERIOD_LSB_PTR        ((reg16 *) P2_WinTimer_TimerHW__PER0 )
    #define P2_WinTimer_COUNTER_LSB         (* (reg16 *) P2_WinTimer_TimerHW__CNT_CMP0 )
    #define P2_WinTimer_COUNTER_LSB_PTR       ((reg16 *) P2_WinTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define P2_WinTimer_BLOCK_EN_MASK                     P2_WinTimer_TimerHW__PM_ACT_MSK
    #define P2_WinTimer_BLOCK_STBY_EN_MASK                P2_WinTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define P2_WinTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define P2_WinTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define P2_WinTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define P2_WinTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define P2_WinTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define P2_WinTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << P2_WinTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define P2_WinTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define P2_WinTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << P2_WinTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define P2_WinTimer_CTRL_MODE_SHIFT                 0x01u
        #define P2_WinTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << P2_WinTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define P2_WinTimer_CTRL_RCOD_SHIFT        0x02u
        #define P2_WinTimer_CTRL_ENBL_SHIFT        0x00u
        #define P2_WinTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define P2_WinTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << P2_WinTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define P2_WinTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << P2_WinTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define P2_WinTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << P2_WinTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define P2_WinTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << P2_WinTimer_CTRL_RCOD_SHIFT))
        #define P2_WinTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << P2_WinTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define P2_WinTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define P2_WinTimer_RT1_MASK                        ((uint8)((uint8)0x03u << P2_WinTimer_RT1_SHIFT))
    #define P2_WinTimer_SYNC                            ((uint8)((uint8)0x03u << P2_WinTimer_RT1_SHIFT))
    #define P2_WinTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define P2_WinTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << P2_WinTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define P2_WinTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << P2_WinTimer_SYNCDSI_SHIFT))

    #define P2_WinTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << P2_WinTimer_CTRL_MODE_SHIFT))
    #define P2_WinTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << P2_WinTimer_CTRL_MODE_SHIFT))
    #define P2_WinTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << P2_WinTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define P2_WinTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define P2_WinTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define P2_WinTimer_STATUS_TC_INT_MASK_SHIFT        (P2_WinTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define P2_WinTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (P2_WinTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define P2_WinTimer_STATUS_TC                       ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_TC_SHIFT))
    #define P2_WinTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define P2_WinTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define P2_WinTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define P2_WinTimer_STATUS              (* (reg8 *) P2_WinTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define P2_WinTimer_STATUS_MASK         (* (reg8 *) P2_WinTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define P2_WinTimer_STATUS_AUX_CTRL     (* (reg8 *) P2_WinTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define P2_WinTimer_CONTROL             (* (reg8 *) P2_WinTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(P2_WinTimer_Resolution <= 8u) /* 8-bit Timer */
        #define P2_WinTimer_CAPTURE_LSB         (* (reg8 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define P2_WinTimer_CAPTURE_LSB_PTR       ((reg8 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define P2_WinTimer_PERIOD_LSB          (* (reg8 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define P2_WinTimer_PERIOD_LSB_PTR        ((reg8 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define P2_WinTimer_COUNTER_LSB         (* (reg8 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define P2_WinTimer_COUNTER_LSB_PTR       ((reg8 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(P2_WinTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define P2_WinTimer_CAPTURE_LSB         (* (reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define P2_WinTimer_CAPTURE_LSB_PTR       ((reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define P2_WinTimer_PERIOD_LSB          (* (reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define P2_WinTimer_PERIOD_LSB_PTR        ((reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define P2_WinTimer_COUNTER_LSB         (* (reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define P2_WinTimer_COUNTER_LSB_PTR       ((reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define P2_WinTimer_CAPTURE_LSB         (* (reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define P2_WinTimer_CAPTURE_LSB_PTR       ((reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define P2_WinTimer_PERIOD_LSB          (* (reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define P2_WinTimer_PERIOD_LSB_PTR        ((reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define P2_WinTimer_COUNTER_LSB         (* (reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define P2_WinTimer_COUNTER_LSB_PTR       ((reg16 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(P2_WinTimer_Resolution <= 24u)/* 24-bit Timer */
        #define P2_WinTimer_CAPTURE_LSB         (* (reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define P2_WinTimer_CAPTURE_LSB_PTR       ((reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define P2_WinTimer_PERIOD_LSB          (* (reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define P2_WinTimer_PERIOD_LSB_PTR        ((reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define P2_WinTimer_COUNTER_LSB         (* (reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define P2_WinTimer_COUNTER_LSB_PTR       ((reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define P2_WinTimer_CAPTURE_LSB         (* (reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define P2_WinTimer_CAPTURE_LSB_PTR       ((reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define P2_WinTimer_PERIOD_LSB          (* (reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define P2_WinTimer_PERIOD_LSB_PTR        ((reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define P2_WinTimer_COUNTER_LSB         (* (reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define P2_WinTimer_COUNTER_LSB_PTR       ((reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define P2_WinTimer_CAPTURE_LSB         (* (reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define P2_WinTimer_CAPTURE_LSB_PTR       ((reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define P2_WinTimer_PERIOD_LSB          (* (reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define P2_WinTimer_PERIOD_LSB_PTR        ((reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define P2_WinTimer_COUNTER_LSB         (* (reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define P2_WinTimer_COUNTER_LSB_PTR       ((reg32 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define P2_WinTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) P2_WinTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (P2_WinTimer_UsingHWCaptureCounter)
        #define P2_WinTimer_CAP_COUNT              (*(reg8 *) P2_WinTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define P2_WinTimer_CAP_COUNT_PTR          ( (reg8 *) P2_WinTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define P2_WinTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) P2_WinTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define P2_WinTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) P2_WinTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (P2_WinTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define P2_WinTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define P2_WinTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define P2_WinTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define P2_WinTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define P2_WinTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define P2_WinTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << P2_WinTimer_CTRL_INTCNT_SHIFT))
    #define P2_WinTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << P2_WinTimer_CTRL_TRIG_MODE_SHIFT))
    #define P2_WinTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << P2_WinTimer_CTRL_TRIG_EN_SHIFT))
    #define P2_WinTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << P2_WinTimer_CTRL_CAP_MODE_SHIFT))
    #define P2_WinTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << P2_WinTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define P2_WinTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define P2_WinTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define P2_WinTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define P2_WinTimer_STATUS_TC_INT_MASK_SHIFT       P2_WinTimer_STATUS_TC_SHIFT
    #define P2_WinTimer_STATUS_CAPTURE_INT_MASK_SHIFT  P2_WinTimer_STATUS_CAPTURE_SHIFT
    #define P2_WinTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define P2_WinTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define P2_WinTimer_STATUS_FIFOFULL_INT_MASK_SHIFT P2_WinTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define P2_WinTimer_STATUS_TC                      ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define P2_WinTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define P2_WinTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define P2_WinTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define P2_WinTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define P2_WinTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define P2_WinTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << P2_WinTimer_STATUS_FIFOFULL_SHIFT))

    #define P2_WinTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define P2_WinTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define P2_WinTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define P2_WinTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define P2_WinTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define P2_WinTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_P2_WinTimer_H */


/* [] END OF FILE */
