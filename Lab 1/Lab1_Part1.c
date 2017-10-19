/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.8 --- 10/3/2017 15:56:8 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char temp = 0;
unsigned char temp2 = 0;
unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum SM1_States { SM1_up_init, SM1_S_U } SM1_State;

TickFct_ShiftUp() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_up_init;
         break;
      case SM1_up_init:
         if (1) {
            SM1_State = SM1_S_U;
            temp = 0x01;
         }
         break;
      case SM1_S_U:
         if (1) {
            SM1_State = SM1_S_U;
         }
         break;
      default:
         SM1_State = SM1_up_init;
      } // Transitions

   switch(SM1_State) { // State actions
      case SM1_up_init:
         break;
      case SM1_S_U:
         if( temp & 0x08){
         temp = 0x01;
         }
         else{
         temp <<= 1;
         }
         
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM2_States { SM2_down_init, SM2_S_D } SM2_State;

TickFct_Shift_Down() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(SM2_State) { // Transitions
      case -1:
         SM2_State = SM2_down_init;
         break;
      case SM2_down_init:
         if (1) {
            SM2_State = SM2_S_D;
            temp2 = 0x80;
         }
         break;
      case SM2_S_D:
         if (1) {
            SM2_State = SM2_S_D;
         }
         break;
      default:
         SM2_State = SM2_down_init;
      } // Transitions

   switch(SM2_State) { // State actions
      case SM2_down_init:
         break;
      case SM2_S_D:
         if( temp2 & 0x10){
         temp2 = 0x80;
         }
         else{
         temp2 >>= 1;
         }
         
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM3_States { SM3_Combine_Init, SM3_OR_1_2 } SM3_State;

TickFct_Combine() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(SM3_State) { // Transitions
      case -1:
         SM3_State = SM3_Combine_Init;
         break;
      case SM3_Combine_Init:
         if (1) {
            SM3_State = SM3_OR_1_2;
         }
         break;
      case SM3_OR_1_2:
         if (1) {
            SM3_State = SM3_OR_1_2;
            B = temp | temp2;
         }
         break;
      default:
         SM3_State = SM3_Combine_Init;
      } // Transitions

   switch(SM3_State) { // State actions
      case SM3_Combine_Init:
         break;
      case SM3_OR_1_2:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}
int main() {
   B = 0; //Init outputs
   TimerSet(1000);
   TimerOn();
   SM1_State = -1;
   SM2_State = -1;
   SM3_State = -1;
   while(1) {
      TickFct_ShiftUp();
      TickFct_Shift_Down();
      TickFct_Combine();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}
