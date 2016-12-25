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
volatile int input_ptr[2];
volatile int buf_ptr[2];
volatile uint16 data[6];
volatile uint16 input[6][INPUT_BUF_SIZE];
volatile int ready;
volatile int timer_ready[2];
volatile int use_timer[2];
volatile int disable_timer[2];
volatile int bytes;
volatile int window_off[2];
volatile int latches[2];
volatile int ports;
volatile int lines;
volatile int request[2];
volatile int async;
volatile int autolatch;
volatile int autofilled;
volatile int autobits;

/* [] END OF FILE */
