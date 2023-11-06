/*
 * timer.c
 *
 *  Created on: Nov 3, 2023
 *      Author: PhongTran
 */
#include "timer.h"


int timer1_flag = 0;
int timer1_duration;

int timer2_flag = 0;
int timer2_duration;


int timer3_flag = 0;
int timer3_duration;


void setTimer1(int duration){
    timer1_duration = duration;
    timer1_flag = 0;
}

void setTimer2(int duration){
    timer2_duration = duration;
    timer2_flag = 0;
}

void setTimer3(int duration){
    timer3_duration = duration;
    timer3_flag = 0;
}
void timerRun(){
    if(timer1_duration > 0){
        timer1_duration--;
        if(timer1_duration <= 0){
            timer1_flag = 1;
        }
    }
     if(timer2_duration > 0){
        timer2_duration--;
        if(timer2_duration <= 0){
            timer2_flag = 1;

        }
    }
    if(timer3_duration > 0){
        timer3_duration--;
        if(timer3_duration <= 0){
            timer3_flag = 1;

        }
    }
}


