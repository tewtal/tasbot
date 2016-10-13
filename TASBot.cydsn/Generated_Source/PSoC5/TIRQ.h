/*******************************************************************************
* File Name: TIRQ.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_TIRQ_H)
#define CY_ISR_TIRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TIRQ_Start(void);
void TIRQ_StartEx(cyisraddress address);
void TIRQ_Stop(void);

CY_ISR_PROTO(TIRQ_Interrupt);

void TIRQ_SetVector(cyisraddress address);
cyisraddress TIRQ_GetVector(void);

void TIRQ_SetPriority(uint8 priority);
uint8 TIRQ_GetPriority(void);

void TIRQ_Enable(void);
uint8 TIRQ_GetState(void);
void TIRQ_Disable(void);

void TIRQ_SetPending(void);
void TIRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TIRQ ISR. */
#define TIRQ_INTC_VECTOR            ((reg32 *) TIRQ__INTC_VECT)

/* Address of the TIRQ ISR priority. */
#define TIRQ_INTC_PRIOR             ((reg8 *) TIRQ__INTC_PRIOR_REG)

/* Priority of the TIRQ interrupt. */
#define TIRQ_INTC_PRIOR_NUMBER      TIRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TIRQ interrupt. */
#define TIRQ_INTC_SET_EN            ((reg32 *) TIRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TIRQ interrupt. */
#define TIRQ_INTC_CLR_EN            ((reg32 *) TIRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TIRQ interrupt state to pending. */
#define TIRQ_INTC_SET_PD            ((reg32 *) TIRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TIRQ interrupt. */
#define TIRQ_INTC_CLR_PD            ((reg32 *) TIRQ__INTC_CLR_PD_REG)


#endif /* CY_ISR_TIRQ_H */


/* [] END OF FILE */
