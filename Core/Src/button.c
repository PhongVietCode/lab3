/*
 * button.c
 *
 *  Created on: Nov 3, 2023
 *      Author: PhongTran
 */
#include "button.h"

static int current_button_state[NO_OF_BUTTONS];

// debounce for each button
static int debounce_1[NO_OF_BUTTONS];
static int debounce_2[NO_OF_BUTTONS];
static int debounce_3[NO_OF_BUTTONS];

// state
static int button_state_save[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

static int counter_for_button_pressed[NO_OF_BUTTONS];

// flag for buttons
static int button_flag[NO_OF_BUTTONS];
static int button_flag_long[NO_OF_BUTTONS];
int isButtonPress(int index)
{
    // if press, turn off the flag and return 1
    if (button_flag[index] == 1)
    {
        button_flag[index] = 0;
        return 1;
    }

    // if not just return 0
    return 0;
}
int isButtonLongPress(int index){
	// if press return 1 and turn off flag
	 if (button_flag_long[index] == 1)
	{
		button_flag_long[index] = 0;
		return 1;
	}
	// if not just return 0
	return 0;
}
void button_process(int index)
{
    if (index >= 0 && index < NO_OF_BUTTONS)
    {
        button_flag[index] = 1;
    }
}
void button_reading()
{
    for (int i = 0; i < NO_OF_BUTTONS; i++)
    {
        // debounce button
        debounce_3[i] = debounce_2[i];
        debounce_2[i] = debounce_1[i];

        // read pin button state
        switch (i)
        {
        case 0:
            debounce_1[i] = HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
            break;
        case 1:
            debounce_1[i] = HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
            break;
        case 2:
            debounce_1[i] = HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
            break;
        default:
            break;
        }

        // pass debouncing
        if ((debounce_3[i] == debounce_2[i]) && (debounce_2[i] == debounce_1[i]))
        {
            current_button_state[i] = debounce_1[i];

            // fsm
            switch (button_state_save[i])
            {
            case BUTTON_IS_RELEASED:
                /* code */
                if (current_button_state[i] == PRESS_STATE)
                {
                    button_state_save[i] = BUTTON_IS_PRESSED;
                }
                break;

            case BUTTON_IS_PRESSED:
                /* code */
            	if (current_button_state[i] == RELEASED_STATE)
			   {
            		button_flag[i] = 1;
				   button_state_save[i] = BUTTON_IS_RELEASED;
				   counter_for_button_pressed[i] = 0;
				   return;
			   }
                counter_for_button_pressed[i]++;
                if (counter_for_button_pressed[i] >= WAITING_TIME / TIME_CYCLE)
                {
                    button_state_save[i] = BUTTON_IS_LONG_PRESSED;
                    counter_for_button_pressed[i] = 0;
                    button_flag_long[i] = 1;
                }

                break;

            case BUTTON_IS_LONG_PRESSED:
                /* code */
                if (current_button_state[i] == RELEASED_STATE)
                {
                    button_state_save[i] = BUTTON_IS_RELEASED;
                    counter_for_button_pressed[i] = 0;
                }
                counter_for_button_pressed[i]++;
                if (counter_for_button_pressed[i] == TIME_OUT_FOR_KEY_PRESSED / TIME_CYCLE)
                {
                    counter_for_button_pressed[i] = 0;
                }
                break;
            default:
                break;
            }
        }
    }
}
