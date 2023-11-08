#ifndef INC_TIMER_H
#define INC_TIMER_H

#include "main.h"
#include"button.h"

extern int timer1_flag, timer2_flag, timer3_flag, timer4_flag;

void setTimer1(int);
void setTimer2(int);
void setTimer3(int);
void setTimer4(int);
void timerRun(void);

#endif /*INC_TIMER_H*/
