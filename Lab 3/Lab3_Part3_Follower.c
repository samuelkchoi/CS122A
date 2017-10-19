/* Baldomero Vargas, bvarg006@ucr.edu
* Samuel Choi, schoi044@ucr.edu
* Lab Section: 22
* Assignment: Lab #3 Exercise #3 Servant
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "scheduler.h"

#include "SPI.h"

unsigned char CNT_DIR; //1 is to go down, 0 is to go up 
unsigned char patternCheck, speedCheck, output1, output2, output3, output4;
unsigned short clkSpeed = 1000;
unsigned short clkCount = 0;

enum data_sent {dataRecieve};

int data_sent(int state){
	//transitions
	switch(state)
	{
		case dataRecieve:
		state = dataRecieve;
		break;
		    
		default:
		state = dataRecieve;
		break;
	}
	    
	//actions
	switch(state)
	{
		case dataRecieve:
		if(receivedData != 0){
			patternCheck = (receivedData & 0xF0) >> 4;
			speedCheck = receivedData & 0x0F;
		}
		break;
		    
		default:
		break;
	}
	return state;
}

enum clk_set {setClk};

int clk_set(int state){
	//transitions
	switch(state)
	{
		case -1:
		state = setClk;
		break;
		
		case setClk:
		state = setClk;
		break;
		
		default:
		state = setClk;
		break;
	}
	
	//actions
	switch(state)
	{
		case -1:
		state = setClk;
		break;
		
		case setClk:
		if(speedCheck == 0x01){clkSpeed = 2000;}
		else if(speedCheck == 0x02){clkSpeed = 1000;}
		else if(speedCheck == 0x03){clkSpeed = 500;}
		else if(speedCheck == 0x04){clkSpeed = 250;}
		else if(speedCheck == 0x05){clkSpeed = 100;}
		else if(speedCheck == 0x06){clkSpeed = 50;}									
			
		state = setClk;
		break;
		
		default:
		state = setClk;
		break;
	}
	return state;
}

enum pattern_topToBot {pattern_one};

int pattern_topToBot (int state)
{
    //transitions
    switch(state)
    {
		case -1:
		output1 = 0xF0;
		state = pattern_one;
		break;
		
        case pattern_one:
        state = pattern_one;
        break;
            
        default:
        state = pattern_one;
        break;
    }
    
    //actions
    switch(state)
    {
		case -1:
		break;
		
        case pattern_one:
		if(clkCount == clkSpeed - 1){
			if(patternCheck == 0x01)
			{
				output1 ^= 0xFF;
			}
		}
        break;
            
        default:
        break;  
    }
    return state;
}

enum pattern_leftToRight {pattern_two};

int pattern_leftToRight (int state)
{
    //transitions
    switch(state)
    {
		case -1:
		output2 = 0xAA;
		state = pattern_two;
		break;
		
        case pattern_two:
        state = pattern_two;
        break;
            
        default:
        state = pattern_two;
        break;
    }
    
    //actions
    switch(state)
    {
		case -1:
		break;
		
        case pattern_two:
		if(clkCount == clkSpeed - 1){		
			if(patternCheck == 0x02)
			{
				output2 = ~output2;
			}
		}
        break;
            
        default:
        break;  
    } 
    return state;
}

enum pattern_shiftPingPong {pattern_three};

int pattern_shiftPingPong (int state)
{
    //transitions
    switch(state)
    {
		case -1:
        CNT_DIR = 1;
		output3 = 0x80;
		state = pattern_three;
		break;
				
        case pattern_three:
        state = pattern_three;
        break;
            
        default:
        state = pattern_three;
        break;
    }
    
    //actions
    switch(state)
    {
		case -1:
		break;
		
        case pattern_three:
		if(patternCheck == 0x03)
		{
		if(clkCount == clkSpeed - 1){							
			if(CNT_DIR == 1)
				{
					if(output3 == 0x01)
					{
						CNT_DIR = 0;
						break;
					}
					else
					{
						output3 >>= 1;
					}
				}
				else if(CNT_DIR == 0)
				{
					if(output3 == 0x80)
					{
						CNT_DIR = 1;
						break;
					}
					else
					{
						output3 <<= 1;
					}
				}
			}
		}
        break;
            
        default:
        break;  
    }
    return state;
}

enum pattern_binaryCount {pattern_four};

int pattern_binaryCount (int state)
{
    //transitions
    switch(state)
    {
		case -1:
		output4 = 0;
		state = pattern_four;
		break;
		
        case pattern_four:
        state = pattern_four;
        break;
            
        default:
        state = pattern_four;
        break;
    }
    
    //actions
    switch(state)
    {
        case pattern_four:
		if(patternCheck == 0x04)
		{
			if(clkCount == clkSpeed - 1){
				output4++;
				if(output4 == 255){
					output4 = 0;
				}
			}
		}
        break;
            
        default:
        break;  
    }
    return state;
}

enum pattern_output {output_pattern};

int pattern_output (int state)
{
    //transitions
    switch(state)
    {    
        case output_pattern:
        state = output_pattern;
        break;
        
        default:
        state = output_pattern;
        break;
    }
    
    //actions
    switch(state)
    {
        case output_pattern:
		
		clkCount++;
		if(clkCount >= clkSpeed){
			
			if(patternCheck == 0x01)
			{
				PORTD = output1;
			}
			else if(patternCheck == 0x02)
			{
				PORTD = output2;
			}
			else if(patternCheck == 0x03)
			{
				PORTD = output3;
			}
			else if(patternCheck == 0x04)
			{
				PORTD = output4;
			}
			else{
				patternCheck = 0x01;   
			}
			clkCount = 0;
		}
        break;    
    }
    return state; 
}

int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	SPI_ServantInit();
	
	//Task Scheduler
	unsigned char i = 0;
	tasksNum = 7;
	task tsks[7];
	tasks = tsks;
	
	tasks[i].state = -1;
	tasks[i].period = 50;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &data_sent;
	++i;
	
	tasks[i].state = -1;
	tasks[i].period = 50;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &clk_set;
	++i;	
	
	tasks[i].state = -1;
	tasks[i].period = 1;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &pattern_topToBot;
	++i;

	tasks[i].state = -1;
	tasks[i].period = 1;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &pattern_leftToRight;
	++i;
	
	tasks[i].state = -1;
	tasks[i].period = 1;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &pattern_shiftPingPong;
	++i;

	tasks[i].state = -1;
	tasks[i].period = 1;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &pattern_binaryCount;
	++i;

	tasks[i].state = -1;
	tasks[i].period = 1;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &pattern_output;
	++i;
	
	TimerSet(1);
	TimerOn();
	
	while(1){}
}

