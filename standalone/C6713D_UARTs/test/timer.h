#ifndef _TIMER_H_
#define _TIMER_H_

#define TIMER0                   1
#define TIMER1                   0

#define TIMER_BASE_ADDR          0x01940000

#define TIMER_CTRL_ADDR(chan)    (TIMER_BASE_ADDR + ((chan) * 0x40000))
#define TIMER_PERIOD_ADDR(chan)  (TIMER_BASE_ADDR + ((chan) * 0x40000) + 4)
#define TIMER_COUNTER_ADDR(chan) (TIMER_BASE_ADDR + ((chan) * 0x40000) + 8)

void         timer_set_and_start_timer(unsigned char TIMER_ch,unsigned int us);
unsigned int timer_read_timer(unsigned char TIMER_ch);
void         timer_stop_timer(unsigned char TIMER_ch);
unsigned int timer_counter_sub(unsigned char TIMER_ch,unsigned int *start_t0,unsigned int period);
void         timer_delay(unsigned char TIMER_ch,unsigned int period,unsigned int us);

#endif

