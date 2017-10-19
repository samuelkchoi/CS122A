/* Baldomero Vargas, bvarg006@ucr.edu
* Samuel Choi, schoi044@ucr.edu
* Lab Section: 22
* Assignment: Lab #3 Exercise #1 Servant
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "scheduler.h"

#include "SPI.h"


unsigned char temp = 0;

enum Slave_Receive {Servant_Receive};
	
int slaveTick(int state)
{
	//Transitions
	switch(state)
	{
		case Servant_Receive:
		state = Servant_Receive;
		break;
		
		default:
		state = Servant_Receive;
		break;
	}
	
	//Actions
	switch(state)
	{
		
		case -1:
		break;
		
		case Servant_Receive:
		//SPI_SlaveReceive();
		temp = receivedData;
		PORTD = temp;
		break;
		
		default:
		break;
	}
	
	return state;
	
}

int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	SPI_ServantInit();
	
	//Task Scheduler
	tasksNum = 1;
	task tsks[1];
	tasks = tsks;
	
	unsigned char i = 0;
	tasks[i].state = -1;
	tasks[i].period = 50;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &slaveTick;
	
	TimerSet(50);
	TimerOn();
	
	while(1){}
}

