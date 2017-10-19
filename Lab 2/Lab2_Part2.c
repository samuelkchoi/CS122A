/* Baldomero Vargas, bvarg006@ucr.edu
* Samuel Choi, schoi044@ucr.edu
* Lab Section: 22
* Assignment: Lab #2 Exercise #2
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include "usart_ATmega1284.h"
#include "scheduler.h"

unsigned char poll = 0;

enum F_States { F_Wait, F_Output };
int TickFct_Follower(int state) {
	switch(state) { // Transitions
		case -1: // Initial transition
		state = F_Wait;
		break;
		
		case F_Wait:
		poll = PINB;
		if(!(poll & 0x01)){
			PORTC = 0;
			if(USART_HasReceived(0)){
				state = F_Output;
			}
		}
		break;
		
		case F_Output:
		state = F_Wait;
		break;
		
		default:
		state = -1;
		break;
	}

	switch(state) { // State actions
		case -1: // Initial transition
		state = F_Wait;
		break;
		
		case F_Wait:
		break;
		
		case F_Output:
		PORTA = USART_Receive(0);
		break;
		
		default:
		state = -1;
		break;
	}

	return state;
}

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
		
		poll = PINB;
		if((poll & 0x01))
		{
			PORTC = 0x01;
			if (USART_IsSendReady(1))
			{
				temp ^= 0x01;
				PORTA = temp;
				USART_Send( temp , 1);
				USART_Flush(1);
			}
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
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	initUSART(0);
	initUSART(1);
	
	tasksNum = 2; // declare number of tasks
	task tsks[2]; // initialize the task array
	tasks = tsks; // set the task array
	
	// define tasks
	unsigned char i=0; // task counter
	tasks[i].state = -1;
	tasks[i].period = 50;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TickFct_Follower;
	++i;
	tasks[i].state = -1;
	tasks[i].period = 1000;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TickFct_Leader;

	
	TimerSet(50); // value set should be GCD of all tasks
	TimerOn();

	while(1) {} // task scheduler will be called by the hardware interrupt
	
	return 0;
}

