#include"math.h"
#include"c6x.h"

#include "struct.h"
#include "can.h"
#include "common.h"
#include "emif.h"
#include "interrupt.h"
#include "SJA1000.h"
#include "pll.h"
#include "regs.h"


#include "timer.h"


//----------------------------------------------------------
//-- set and start timer_x
//   internal clock source,clock mode,PWID=0,
//   clock 50M,1us = 50 clk
//----------------------------------------------------------
void timer_set_and_start_timer(unsigned char TIMER_ch,unsigned int us)
{
    *(unsigned volatile int *)TIMER_CTRL_ADDR(TIMER_ch)   = 0x301;  //clock mode
    *(unsigned volatile int *)TIMER_PERIOD_ADDR(TIMER_ch) = (25*us);//clock mode 25,puls mode 50
    *(unsigned volatile int *)TIMER_CTRL_ADDR(TIMER_ch)  |= 0x0c0;
}

//----------------------------------------------------------
//-- read back timer_x counter
//----------------------------------------------------------
unsigned int timer_read_timer(unsigned char TIMER_ch)
{
    return((unsigned int)(*(unsigned volatile int *)TIMER_COUNTER_ADDR(TIMER_ch)));
}

//----------------------------------------------------------
//-- stop timer_x counter
//----------------------------------------------------------
void timer_stop_timer(unsigned char TIMER_ch)
{
    *(unsigned volatile int *)TIMER_CTRL_ADDR(TIMER_ch) = 0x301;
}

//----------------------------------------------------------
//-- return timer_x counter sub value from start
//   timer_x counter increase
//----------------------------------------------------------
unsigned int timer_counter_sub(unsigned char TIMER_ch,unsigned int *start_t0,unsigned int period)
{
    unsigned int start_ti;

    start_ti = timer_read_timer(TIMER_ch);
    if(start_ti<*start_t0)
    {
        start_ti = start_ti + period - *start_t0;
    }
    else
    {
        start_ti = start_ti - *start_t0;
    }

    return(start_ti/50);
}

//----------------------------------------------------------
//-- timer_x delay assume value
//   timer_x counter increase
//----------------------------------------------------------
void timer_delay(unsigned char TIMER_ch,unsigned int period,unsigned int us)
{
    unsigned int start_t0,start_ti,sub_time;

    start_t0 = timer_read_timer(TIMER_ch);
    sub_time = 0;
    while(sub_time<(us*50))
    {
        start_ti = timer_read_timer(TIMER_ch);
        if(start_ti<start_t0)
        {
            sub_time = start_ti + period - start_t0;
        }
        else
        {
            sub_time = start_ti - start_t0;
        }
    }
}

