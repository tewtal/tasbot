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
volatile uint16 data[6];
volatile uint16 input[6][INPUT_BUF_SIZE];
volatile int ready;
volatile int timer_ready;
volatile int use_timer;
volatile int disable_timer;
volatile int bytes;
volatile int window_off;
volatile int latches;
volatile int ports;
volatile int lines;
volatile int request;
volatile int async;
volatile int autolatch;
volatile int autofilled;
volatile int autobits;

/* [] END OF FILE */
