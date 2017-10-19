# Exercises

### 1. 
**Master:** *Design a system that uses SPI to send an incremented 8-bit value to the Servant microcontroller every second.*
**Servant:** *Design a system that outputs any data received from the Master to a bank of 8 LEDs.*
### 2. 
*Design a system where a pattern number and speed number are sent as one 8-bit value to the Servant whenever a new key is pressed on the keypad.*

**Leader: Sending pattern and speed numbers to a Follower**   

**Leader Criteria:**
  * *Use shared variables to hold the current pattern and speed numbers.*
  * *Use another shared variable named "data" that holds the 8-bit value to be sent to the Follower.*
  * *The upper 4 bits of "data" should hold the pattern number.*
  * *The lower 4 bits of "data" should hold the speed number.*
  * *"data" is updated and sent whenever a button is pressed on the keypad.*
  
**Follower: Display one of four patterns**   

**Follower Criteria:**
  * *Write a "pattern" synchSM for each pattern described in the "Overall System Description" part of the lab. Each "pattern" synchSM writes its pattern to a unique shared variable.*
  * *Write an "output" synchSM that writes a pattern to the bank of 8 LEDs. The pattern written is determined by the upper 4 bits of "receivedData".*
### 3. 
**Leader: Keypad input with LCD Display**  
*The LCD display is constantly displaying the currently selected pattern number, speed, and microcontroller. Expand upon part 2 by designing a system where a button press on the keypad updates the LCD display.* 
  
**Follower: Adjust speed of blinking patterns**  
*Expand upon part 2 of the lab by adjusting the rate at which the blinking patterns updates. The lower 4 bits of "receivedData" represent the desired speed number. Refer to the given speeds at the top of the lab.*
