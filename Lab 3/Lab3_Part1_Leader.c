/* Baldomero Vargas, bvarg006@ucr.edu
* Samuel Choi, schoi044@ucr.edu
* Lab Section: 22
* Assignment: Lab #3 Exercise #1 Master
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "scheduler.h"

#include "SPI.h"

unsigned char temp = 0;

enum Master_Transmit {Master_Send};
	
int masterTick(int state)
{
	//Transitions
	switch(state)
	{
		case Master_Send:
		state  = Master_Send;
		break;
		
		default:
		state = Master_Send;
		break;
	}
	
	//Actions
	switch(state)
	{
		case Master_Send:
		temp += 1;
		SPI_MasterTransmit(temp);
		break;
		
		default:
		break;
	}
	
	return state;
}

int main(void)
{
	SPI_MasterInit();
	
	//Task Scheduler
	tasksNum = 1;
	task tsks[1];
	tasks = tsks;
	
	unsigned char i = 0;
	tasks[i].state = -1;
	tasks[i].period = 1000;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &masterTick;
	
	TimerSet(50);
	TimerOn();
}

