/*******************************************************************************
* File Name: P1.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the Shift Register component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "P1.h"

uint8 P1_initVar = 0u;


/*******************************************************************************
* Function Name: P1_Start
********************************************************************************
*
* Summary:
*  Starts the Shift Register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  P1_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void P1_Start(void) 
{
    if(0u == P1_initVar)
    {
        P1_Init();
        P1_initVar = 1u; /* Component initialized */
    }

    P1_Enable();
}


/*******************************************************************************
* Function Name: P1_Enable
********************************************************************************
*
* Summary:
*  Enables the Shift Register.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void P1_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    P1_SR_CONTROL |= P1_CLK_EN;

    P1_EnableInt();
}


/*******************************************************************************
* Function Name: P1_Init
********************************************************************************
*
* Summary:
*  Initializes Tx and/or Rx interrupt sources with initial values.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void P1_Init(void) 
{
    P1_SetIntMode(P1_INT_SRC);
}


/*******************************************************************************
* Function Name: P1_Stop
********************************************************************************
*
* Summary:
*  Disables the Shift Register
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void P1_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    P1_SR_CONTROL &= ((uint8) ~P1_CLK_EN);
    P1_DisableInt();
}


/*******************************************************************************
* Function Name: P1_EnableInt
********************************************************************************
*
* Summary:
*  Enables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void P1_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    P1_SR_AUX_CONTROL |= P1_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: P1_DisableInt
********************************************************************************
*
* Summary:
*  Disables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void P1_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    P1_SR_AUX_CONTROL &= ((uint8) ~P1_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: P1_GetFIFOStatus
********************************************************************************
*
* Summary:
*  Returns current status of input or output FIFO.
*
* Parameters:
*  fifoId.
*
* Return:
*  FIFO status.
*
*******************************************************************************/
uint8 P1_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = P1_RET_FIFO_NOT_DEFINED;

    #if(0u != P1_USE_INPUT_FIFO)
        if(P1_IN_FIFO == fifoId)
        {
            switch(P1_GET_IN_FIFO_STS)
            {
                case P1_IN_FIFO_FULL :
                    result = P1_RET_FIFO_FULL;
                    break;

                case P1_IN_FIFO_EMPTY :
                    result = P1_RET_FIFO_EMPTY;
                    break;

                case P1_IN_FIFO_PARTIAL:
                    result = P1_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = P1_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != P1_USE_INPUT_FIFO) */

    if(P1_OUT_FIFO == fifoId)
    {
        switch(P1_GET_OUT_FIFO_STS)
        {
            case P1_OUT_FIFO_FULL :
                result = P1_RET_FIFO_FULL;
                break;

            case P1_OUT_FIFO_EMPTY :
                result = P1_RET_FIFO_EMPTY;
                break;

            case P1_OUT_FIFO_PARTIAL :
                result = P1_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = P1_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: P1_SetIntMode
********************************************************************************
*
* Summary:
*  Sets the Interrupt Source for the Shift Register interrupt. Multiple
*  sources may be ORed together
*
* Parameters:
*  interruptSource: Byte containing the constant for the selected interrupt
*  source/s.
*
* Return:
*  None.
*
*******************************************************************************/
void P1_SetIntMode(uint8 interruptSource) 
{
    P1_SR_STATUS_MASK &= ((uint8) ~P1_INTS_EN_MASK);          /* Clear existing int */
    P1_SR_STATUS_MASK |= (interruptSource & P1_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: P1_GetIntStatus
********************************************************************************
*
* Summary:
*  Gets the Shift Register Interrupt status.
*
* Parameters:
*  None.
*
* Return:
*  Byte containing the constant for the selected interrupt source/s.
*
*******************************************************************************/
uint8 P1_GetIntStatus(void) 
{
    return(P1_SR_STATUS & P1_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: P1_WriteRegValue
********************************************************************************
*
* Summary:
*  Send state directly to shift register
*
* Parameters:
*  shiftData: containing shift register state.
*
* Return:
*  None.
*
*******************************************************************************/
void P1_WriteRegValue(uint16 shiftData)
                                                                     
{
    CY_SET_REG16(P1_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != P1_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: P1_WriteData
    ********************************************************************************
    *
    * Summary:
    *  Send state to FIFO for later transfer to shift register based on the Load
    *  input
    *
    * Parameters:
    *  shiftData: containing shift register state.
    *
    * Return:
    *  Indicates: successful execution of function
    *  when FIFO is empty; and error when FIFO is full.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    cystatus P1_WriteData(uint16 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(P1_RET_FIFO_FULL != (P1_GetFIFOStatus(P1_IN_FIFO)))
        {
            CY_SET_REG16(P1_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != P1_USE_INPUT_FIFO) */


#if(0u != P1_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: P1_ReadData
    ********************************************************************************
    *
    * Summary:
    *  Returns state in FIFO due to Store input.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Shift Register state
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 P1_ReadData(void) 
    {
        return(CY_GET_REG16(P1_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != P1_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: P1_ReadRegValue
********************************************************************************
*
* Summary:
*  Directly returns current state in shift register, not data in FIFO due
*  to Store input.
*
* Parameters:
*  None.
*
* Return:
*  Shift Register state. Clears output FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint16 P1_ReadRegValue(void) 
{
    uint16 result;

    /* Clear FIFO before software capture */
    while(P1_RET_FIFO_EMPTY != P1_GetFIFOStatus(P1_OUT_FIFO))
    {
        (void) CY_GET_REG16(P1_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(P1_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG16(P1_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (P1_SR_SIZE % 8u))
        result &= ((uint16) P1_SR_MASK);
    #endif /* (0u != (P1_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
