/*
 * fsm_traffic.h
 *
 *  Created on: Nov 3, 2023
 *      Author: PhongTran
 */

#ifndef INC_FSM_TRAFFIC_H_
#define INC_FSM_TRAFFIC_H_

enum lightState{
	RED1_GREEN2,
	RED1_YELLOW2,
	GREEN1_RED2,
	YELLOW1_RED2,
};
void init();
void fsm();
void display_4LED();
void checkButton();
#endif /* INC_FSM_TRAFFIC_H_ */
