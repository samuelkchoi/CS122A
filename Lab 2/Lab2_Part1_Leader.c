/* Baldomero Vargas, bvarg006@ucr.edu
* Samuel Choi, schoi044@ucr.edu
* Lab Section: 22
* Assignment: Lab #2 Exercise #1 leader
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include "usart_ATmega1284.h"
#include "scheduler.h"


unsigned char temp = 0x01;
enum L_States { Leader_Output };
int TickFct_Leader(int state) {
	switch(state) { // Transitions
		case -1: // Initial transition
		state = Leader_Output;
		break;
		
		case Leader_Output:
		break;
		
		default:
		state = -1;
		break;
	}

	switch(state) { // State actions
		case -1: // Initial transition
		state = Leader_Output;
		break;
		
		case Leader_Output:
		if (USART_IsSendReady(0))
		{
			temp ^= 0x01;
			PORTA = temp;
			USART_Send( temp , 0);
		}
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
	tasks[i].period = 1000;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TickFct_Leader;
	
	TimerSet(1000); // value set should be GCD of all tasks
	TimerOn();

	while(1) {} // task scheduler will be called by the hardware interrupt
	
	
	return 0;
}

