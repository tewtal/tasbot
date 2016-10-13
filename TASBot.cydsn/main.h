/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#define INPUT_BUF_SIZE 2048

volatile int sent;
volatile int playing;
volatile int input_ptr;
volatile int buf_ptr;
volatile uint16 data;
volatile uint16 input[8][INPUT_BUF_SIZE];
volatile int ready;
volatile int timer_ready;
volatile int use_timer;
volatile int disable_timer;
volatile int bytes;
volatile int window_off;
volatile int latches;


/* [] END OF FILE */
