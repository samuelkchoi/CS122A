/* Baldomero Vargas, bvarg006@ucr.edu
* Samuel Choi, schoi044@ucr.edu
* Lab Section: 22
* Assignment: Lab #3 Exercise #2 Master
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "scheduler.h"
#include "keypad.h"
#include "lcd.h"
#include "SPI.h"

unsigned char tempRead, tempAssign, upperTemp, lowerTemp;
char * topLCD = "Ptrn:    Spd:";
unsigned char PtrnCur = 7;
unsigned char SpdCur = 15;
unsigned char pattern = 0;
unsigned char speed = 0;

enum masterPattern {masterWait, masterInput, masterSend};

int masterPatternTick (int state)
{
	//transitions
	switch(state)
	{
		case -1:
		LCD_DisplayString(1, topLCD);
		state = masterWait;
		break;
		
		case masterWait:
		
		state = masterInput;
		break;
		
		case masterInput:

		state = masterSend;
		break;
		case masterSend:

		state = masterWait;
		break;
		
		default:
		state = -1;
		break;
	}
	
	//actions
	switch(state)
	{
		case masterWait:
		break;
				
		case masterInput:
		tempRead = GetKeypadKey();
		if(tempRead >= 'A' && tempRead <= 'D')
		{
			upperTemp = (tempRead - 64) << 4;
			pattern = tempRead - 16;
			LCD_Cursor(PtrnCur);
			LCD_WriteData(pattern);
		}		

		if(tempRead >= '1' && tempRead <= '6')
		{
			lowerTemp = (tempRead - 48);
			speed = tempRead;
			LCD_Cursor(SpdCur);
			LCD_WriteData(speed);
		}
			
		break;
		
		case masterSend:
		tempAssign = upperTemp | lowerTemp;
		SPI_MasterTransmit(tempAssign);

		
		break;
				
		default:
		break;
	}
	
	return state;
}



int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRA = 0xFF; PORTA = 0x00;		
	SPI_MasterInit();
	LCD_init();
	
	//Task Scheduler
	tasksNum = 1;
	task tsks[1];
	tasks = tsks;
	
	unsigned char i = 0;
	tasks[i].state = -1;
	tasks[i].period = 50;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &masterPatternTick;
	
	TimerSet(1);
	TimerOn();
	
	while(1){}
}

