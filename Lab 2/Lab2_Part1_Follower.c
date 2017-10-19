/* Baldomero Vargas, bvarg006@ucr.edu
* Samuel Choi, schoi044@ucr.edu
* Lab Section: 22
* Assignment: Lab #2 Exercise #1 follower
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include "usart_ATmega1284.h"
#include "scheduler.h"


enum F_States { Follower_Wait, Follower_Output };
int TickFct_Follower(int state) {
	switch(state) { // Transitions
		case -1: // Initial transition
		state = Follower_Wait;
		break;
		
		case Follower_Wait:
		if(USART_HasReceived(0)){
			state = Follower_Output;
		}
		break;
		
		case Follower_Output:
		state = Follower_Wait;
		break;
		
		default:
		state = -1;
		break;
	}

	switch(state) { // State actions
		case -1: // Initial transition
		state = Follower_Wait;
		break;
		
		case Follower_Wait:
		break;
		
		case Follower_Output:
		PORTA = USART_Receive(0);
		break;
		
		default:
		state = -1;
		break;
	}

	return state;
}

//inputs are 0
//outputs are 1
int main(void) {

	
	// initialize ports
	DDRA = 0xFF; PORTA = 0x00;
	initUSART(0);
	
	tasksNum = 1; // declare number of tasks
	task tsks[1]; // initialize the task array
	tasks = tsks; // set the task array
	
	// define tasks
	unsigned char i=0; // task counter
	tasks[i].state = -1;
	tasks[i].period = 50;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TickFct_Follower;
	
	TimerSet(50); // value set should be GCD of all tasks
	TimerOn();

	while(1) {} // task scheduler will be called by the hardware interrupt
	
	
	return 0;
}

