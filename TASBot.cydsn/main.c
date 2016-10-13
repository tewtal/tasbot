/* ========================================
 * TAS NES/NES Replay Device for CY8CKIT-059
 * ========================================
 */

#include <main.h>
#define USBUART_BUFFER_SIZE (64u)

volatile int sent = 0;
volatile int playing = 0;
volatile uint16 data = 0;
volatile uint16 input[8][INPUT_BUF_SIZE];
volatile int input_ptr;
volatile int buf_ptr = 0;
volatile int count = 0;
volatile int ready = 0;
volatile int timer_ready = 0;
volatile int use_timer = 0;
volatile int controllers = 0;
volatile int databits = 0;
volatile int request = 0;
volatile int disable_timer = 0;
volatile int bytes = 0;
volatile int window_off = -1;
volatile int latches = 0;

int main()
{
    uint8 buffer[USBUART_BUFFER_SIZE];
    uint8 cmd;
    uint16 tmp = 0;
    int i = 0, j = 0, k = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    USBUART_Start(0, USBUART_5V_OPERATION);
    
    ConsolePort_1_RegD0_Start();
    ConsolePort_1_RegD1_Start();
    
    P1_IRQ_Start();
    
    Timer_1_Write(0);
    
    ConsolePort_1_WinTimer_Start();
    
   
    for(;;)
    {           
        if(playing && request == 0)
		{
        	i = (INPUT_BUF_SIZE - 1) - ((buf_ptr - input_ptr)&(INPUT_BUF_SIZE - 1));
			if(i != (INPUT_BUF_SIZE - 1) && i > 65)
			{
                if (0u != USBUART_GetConfiguration())
                {
                    while (0u == USBUART_CDCIsReady()) { }
                    USBUART_PutChar(0xF);
                    request = 1;
                }
          }
        }
        
        if (0u != USBUART_IsConfigurationChanged())
        {
            if (0u != USBUART_GetConfiguration())
            {
                USBUART_CDC_Init();
            }
        }        
        
        if (0u != USBUART_GetConfiguration())
        {
            if (0u != USBUART_DataIsReady())
            {
                /* Read received data and re-enable OUT endpoint. */
                bytes = USBUART_GetAll(buffer);
                cmd = buffer[0];
                
                switch(cmd)
                {
                    case 0:
                    {
                        input_ptr = 0;
                        buf_ptr = 0;
                        playing = 0;
                        count = 0;
                        latches = 0;
                        Timer_1_Write(0);
                        P1_IRQ_Stop();
                        
                        for(i = 0; i < 256; i++)
                        {
                            for(j = 0; j < 1; j++)
                            {
                                input[j][i] = 0;
                            }
                        }
                        break;
                    }
                    case 1:
                    {
                        databits = buffer[1];
                        controllers = buffer[2];
                        use_timer = buffer[3];
                        
                        buf_ptr = 0;
                        playing = 0;
                        sent = 0;
                        count = 0;
                        latches = 0;
                        
                        for(k = 0; k < 4; k++)
                        {
                            while (0u == USBUART_CDCIsReady()) { }
                            USBUART_PutChar(0xF);
                            
                            while(USBUART_DataIsReady() == 0) { }
                            bytes = USBUART_GetAll(buffer);
                            
                            for(j = 1; j < 61; j+= databits)
                            {
                                for(i = 0; i < databits; i++)
                                {
                                    tmp = (tmp<<8) + buffer[j+i];
                                }                        
                                input[0][buf_ptr] = tmp;
            					buf_ptr = (buf_ptr+1)%INPUT_BUF_SIZE;
                            }
                        }
                        
                        //buf_ptr = 0x1FFF;
                        input_ptr = 0;
                        
                        while (0u == USBUART_CDCIsReady()) { }
                        USBUART_PutChar(0xB);                        
                        data = input[0][0];
                        if(use_timer)
                        {
                            Timer_1_Write(1);
                        }
                        timer_ready = 1;
                        ready = 1;
                        playing = 1;
                        request = 0;
                        P1_IRQ_Start();
                        break;
                    }
                    case 0x0F:
                    {
                        tmp = 0;
                        for(j = 1; j < 61; j+= databits)
                        {
                            if(databits == 1)
                            {
                                /* For 8-bit widths fill shift register with two copies of
                                   the 8-bit value */
                                tmp = (buffer[j+1]<<8) + buffer[j+1];
                            } 
                            else 
                            {
                                tmp = (buffer[j+1]<<8) + buffer[j+2];
                            }
                            input[0][buf_ptr] = tmp;
        					buf_ptr = (buf_ptr+1)%INPUT_BUF_SIZE;
                        }
                        request = 0;
                        break;
                    }
                    case 0xF0:
                    {                        
                        ConsolePort_1_WinTimer_WritePeriod((buffer[1]<<8) + (buffer[2]&0xFF));
                        break;
                    }
                    case 0xFC:
                    {
                        /* automatically turn window mode off */
                        window_off = (buffer[1]<<8) + (buffer[2]&0xFF);
                        break;
                    }
                    case 0xFD:
                    {
                        disable_timer = 1;
                        break;
                    }
                    case 0xFE:
                    {
                        disable_timer = 0;
                        use_timer = 1;
                        timer_ready = 1;
                        break;
                    }
                    case 0xFF:
                    {
                        while (0u == USBUART_CDCIsReady()) { }
                        USBUART_PutChar(0xFF);
                        break;
                    }
                }
            }
        }
    }
}

/* [] END OF FILE */
