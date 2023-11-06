#ifndef INC_BUTTON_H
#define INC_BUTTON_H

#include "main.h"

#define NO_OF_BUTTONS 3
#define TIME_OUT_FOR_KEY_PRESSED 200
#define WAITING_TIME 1000

// Button base state
#define PRESS_STATE 0
#define RELEASED_STATE 1
#define TIME_CYCLE 10
// Button state fcm
#define BUTTON_IS_PRESSED 11
#define BUTTON_IS_RELEASED 12
#define BUTTON_IS_LONG_PRESSED 13

void button_reading();
void button_process(int);
int isButtonPress(int);
int isButtonLongPress(int);


#endif  /*INC_BUTTON_H*/
