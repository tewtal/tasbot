/* ========================================
 * TAS NES/NES Replay Device for the PSoC5
 * ========================================
 */

#include <main.h>
#define USBUART_BUFFER_SIZE (64u)

volatile int sent = 0;
volatile int playing = 0;
volatile uint16 data[6] = {0, 0, 0, 0, 0, 0};
volatile uint16 input[6][INPUT_BUF_SIZE];
volatile int input_ptr[2];
volatile int buf_ptr[2] = {0, 0};
volatile int count = 0;
volatile int ready = 0;
volatile int timer_ready[2] = {0, 0};
volatile int use_timer[2] = {0, 0};
volatile int ports = 0;
volatile int lines = 0;
volatile int databits = 0;
volatile int request[2] = {0, 0};
volatile int disable_timer[2] = {0, 0};
volatile int bytes = 0;
volatile int window_off[2] = {-1, -1};
volatile int latches[2] = {0, 0};
volatile int async = 0;

int main()
{
    uint8 buffer[USBUART_BUFFER_SIZE];
    uint8 cmd;
    uint16 tmp = 0;
    int i = 0, j = 0, k = 0, p = 0, d = 0, blocksize = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    USBUART_Start(0, USBUART_5V_OPERATION);
    

    /* Start registers and timers */
    ConsolePort_1_RegD0_Start();
    ConsolePort_1_RegD0_WriteRegValue(1);
    ConsolePort_1_RegD1_Start();
    ConsolePort_1_RegD1_WriteRegValue(1);
    ConsolePort_1_RegD2_Start();
    ConsolePort_1_RegD2_WriteRegValue(1);
    
    ConsolePort_1_WinTimer_Start();
    ConsolePort_1_ClockTimer_Start();

    ConsolePort_2_RegD0_Start();
    ConsolePort_2_RegD0_WriteRegValue(1);
    ConsolePort_2_RegD1_Start();
    ConsolePort_2_RegD1_WriteRegValue(1);
    ConsolePort_2_RegD2_Start();
    ConsolePort_2_RegD2_WriteRegValue(1);

    ConsolePort_2_ClockTimer_Start();

    for(;;)    
    {      
        if(async)
        {
            if(playing && request[0] == 0)
    		{
            	i = (INPUT_BUF_SIZE - 1) - ((buf_ptr[0] - input_ptr[0])&(INPUT_BUF_SIZE - 1));
    			if(i != (INPUT_BUF_SIZE - 1) && i > 65)
    			{
                    if (0u != USBUART_GetConfiguration())
                    {
                        while (0u == USBUART_CDCIsReady()) { }
                        USBUART_PutChar(0xF0);
                        request[0] = 1;
                    }
                }
            }
            
            if(playing && request[1] == 0)
            {
                i = (INPUT_BUF_SIZE - 1) - ((buf_ptr[1] - input_ptr[1])&(INPUT_BUF_SIZE - 1));
    			if(i != (INPUT_BUF_SIZE - 1) && i > 65)
    			{
                    if (0u != USBUART_GetConfiguration())
                    {
                        while (0u == USBUART_CDCIsReady()) { }
                        USBUART_PutChar(0xF1);
                        request[1] = 1;
                    }
                }
            }
        }
        else
        {
            if(playing && request[0] == 0)
            {
                i = (INPUT_BUF_SIZE - 1) - ((buf_ptr[0] - input_ptr[0])&(INPUT_BUF_SIZE - 1));
    			if(i != (INPUT_BUF_SIZE - 1) && i > 65)
    			{
                    if (0u != USBUART_GetConfiguration())
                    {
                        while (0u == USBUART_CDCIsReady()) { }
                        USBUART_PutChar(0xF);
                        request[0] = 1;
                    }
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
                        input_ptr[0] = 0;
                        input_ptr[1] = 0;
                        buf_ptr[0] = 0;
                        buf_ptr[1] = 0;
                        playing = 0;
                        count = 0;
                        latches[0] = 0;
                        latches[1] = 0;
                        async = 0;
                        blocksize = 0;
                        P1_IRQ_Stop();
                        P1_TimerIRQ_Stop();
                        
                        P2_IRQ_Stop();
                        P2_TimerIRQ_Stop();
                        ConsolePort_2_WinTimer_Stop();

                        /* Reset timers to default */
                        ConsolePort_1_ClockTimer_WritePeriod(2);
                        ConsolePort_2_ClockTimer_WritePeriod(2);                        
                        ConsolePort_1_WinTimer_WritePeriod(2500);
                        ConsolePort_2_WinTimer_WritePeriod(2500);
                        
                        disable_timer[0] = 0;
                        use_timer[0] = 0;
                        timer_ready[0] = 0;
                        window_off[0] = -1;

                        disable_timer[1] = 0;
                        use_timer[1] = 0;
                        timer_ready[1] = 0;
                        window_off[1] = -1;

                        for(i = 0; i < INPUT_BUF_SIZE; i++)
                        {
                            for(j = 0; j < 6; j++)
                            {
                                input[j][i] = 0;
                            }
                        }
                        break;
                    }
                    case 1:
                    {
                        databits = buffer[1];
                        ports = buffer[2];
                        lines = buffer[3];
                        async = buffer[4];
                        use_timer[0] = buffer[5];
                        use_timer[1] = buffer[6];
                        
                        buf_ptr[0] = 0;
                        buf_ptr[1] = 0;
                        playing = 0;
                        sent = 0;
                        count = 0;
                        latches[0] = 0;
                        latches[1] = 0;
                        
                        blocksize = ports * databits * lines;
                        
                        for(k = 0; k < 4 * blocksize; k++)
                        {
                            while (0u == USBUART_CDCIsReady()) { }
                            USBUART_PutChar(0x0F);
                            
                            while(USBUART_DataIsReady() == 0) { }
                            bytes = USBUART_GetAll(buffer);
                            
                            for(j = 1; j < bytes; j+= blocksize)
                            {
                                for(p = 0; p < ports; p++)
                                {
                                    for(d = 0; d < lines; d++)
                                    {
                                        
                                        tmp = 0;
                                        if(databits > 1)
                                        {
                                            for(i = 0; i < databits; i++)
                                            {
                                                tmp = (tmp<<8) + buffer[j+(p*(databits*lines))+(d*databits)+i];
                                            }
                                        } 
                                        else 
                                        {
                                            tmp = buffer[j+(p*(databits*lines))+(d*databits)] << 8;
                                        }
                                        
                                        input[(p*3) + d][buf_ptr[p]] = tmp;
                                    }
                                }
            					buf_ptr[0] = (buf_ptr[0]+1)%INPUT_BUF_SIZE;
                                buf_ptr[1] = (buf_ptr[1]+1)%INPUT_BUF_SIZE;
                            }
                        }
                        
                        input_ptr[0] = 0;
                        input_ptr[1] = 0;
                        
                        data[0] = input[0][0];
                        data[1] = input[1][0];
                        data[2] = input[2][0];
                        data[3] = input[3][0];
                        data[4] = input[4][0];
                        data[5] = input[5][0];
                        
                        timer_ready[0] = 1;
                        timer_ready[1] = 1;
                        ready = 1;
                        playing = 1;
                        request[0] = 0;
                        request[1] = 1;

                        P1_IRQ_Start();
                        P1_TimerIRQ_Start();
                        
                        if(async && ports > 1)
                        {
                            ConsolePort_2_WinTimer_Start();
                            P2_TimerIRQ_Start();
                            P2_IRQ_Start();
                            request[1] = 0;
                        }                        
                        break;
                    }
                    case 0xF0:
                    {
                        tmp = 0;
                        for(j = 1; j < bytes; j+= databits * lines)
                        {
                            for(d = 0; d < lines; d++)
                            {
                                tmp = 0;
                                for(i = 0; i < databits; i++)
                                {
                                    tmp = (tmp<<8) + buffer[j+(d*databits)+i];
                                }
                                input[d][buf_ptr[0]] = tmp;
                            }
        					buf_ptr[0] = (buf_ptr[0]+1)%INPUT_BUF_SIZE;
                        }
                        request[0] = 0;
                        break;
                    }
                    case 0xF1:
                    {
                        tmp = 0;
                        for(j = 1; j < bytes; j+= databits * lines)
                        {
                            for(d = 0; d < lines; d++)
                            {
                                tmp = 0;
                                for(i = 0; i < databits; i++)
                                {
                                    tmp = (tmp<<8) + buffer[j+(d*databits)+i];
                                }
                                input[3 + d][buf_ptr[1]] = tmp;
                            }
        					buf_ptr[1] = (buf_ptr[1]+1)%INPUT_BUF_SIZE;
                        }
                        request[1] = 0;
                        break;
                    }
                    case 0xF:
                    {
                        /* synchronous send to both ports with interleaved data */                        
                        for(j = 1; j < bytes; j+= blocksize)
                        {
                            for(p = 0; p < ports; p++)
                            {
                                for(d = 0; d < lines; d++)
                                {
                                    tmp = 0;
                                    if(databits > 1)
                                    {
                                        for(i = 0; i < databits; i++)
                                        {
                                            tmp = (tmp<<8) + buffer[j+(p*(databits*lines))+(d*databits)+i];
                                        }
                                    } 
                                    else 
                                    {
                                        tmp = buffer[j+(p*(databits*lines))+(d*databits)] << 8;
                                    }
                                    input[(p*3) + d][buf_ptr[p]] = tmp;
                                    
                                }
                            }
        					buf_ptr[0] = (buf_ptr[0]+1)%INPUT_BUF_SIZE;
                            buf_ptr[1] = (buf_ptr[1]+1)%INPUT_BUF_SIZE;
                        }
                        request[0] = 0;
                        break;
                    }
                    case 0xA0:
                    {                        
                        ConsolePort_1_WinTimer_WritePeriod((buffer[1]<<8) + (buffer[2]&0xFF));
                        break;
                    }
                    case 0xA1:
                    {
                        window_off[0] = (buffer[1]<<8) + (buffer[2]&0xFF);
                        break;
                    }
                    case 0xA2:
                    {
                        disable_timer[0] = 1;
                        break;
                    }
                    case 0xA3:
                    {
                        disable_timer[0] = 0;
                        use_timer[0] = 1;
                        timer_ready[0] = 1;
                        break;
                    }
                    case 0xA4:
                    {
                        ConsolePort_1_ClockTimer_WritePeriod(buffer[1]);
                        break;
                    }                    
                    case 0xB0:
                    {                        
                        ConsolePort_2_WinTimer_WritePeriod((buffer[1]<<8) + (buffer[2]&0xFF));
                        break;
                    }
                    case 0xB1:
                    {
                        window_off[1] = (buffer[1]<<8) + (buffer[2]&0xFF);
                        break;
                    }
                    case 0xB2:
                    {
                        disable_timer[1] = 1;
                        break;
                    }
                    case 0xB3:
                    {
                        disable_timer[1] = 0;
                        use_timer[1] = 1;
                        timer_ready[1] = 1;
                        break;
                    }
                    case 0xB4:
                    {
                        ConsolePort_2_ClockTimer_WritePeriod(buffer[1]);
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
