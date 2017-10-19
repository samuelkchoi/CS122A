# Exercises

### 1. 
*Two microcontrollers each have an LED connected to PA0. Both LEDs are synchronously toggled on/off in one second intervals using USART.*

**Criteria:**
  * *One team member programs their microcontroller to be a Leader.*
  * *The other team member programs their microcontroller to be a Follower.*
  * *The Leader toggles the value of a local variable between 0 and 1, displays the value of the local variable on the LED connected to PA0, and then transmits a packet containing the value of the local variable to the Follower.*
  * *The Follower receives a packet from the Leader and displays the value received on the LED connected to PA0.*
  * *Each microcontroller receives data on USART0 and sends data on USART1.*


### 2. 
*Expand upon Exercise 1 by adding a switch that determines the mode (Leader or Follower) of the microcontroller.*

**Criteria:**
  * *If a microcontroller is in Leader mode, the microcontroller behaves like the Leader described in part 1.*
  * *If a microcontroller is in Follower mode, the microcontroller behaves like the Follower described in part 1.*
  * *On each microcontroller, a switch is connected to PB0. The direction of the switch determines whether the microcontroller is in Leader mode or a Follower mode.*
  * *On each microcontroller, an LED is connected to PC0. The LED is illuminated when the microcontroller is in Leader mode. The LED is turned off when the microcontroller is in Follower mode.*
  * *The LEDs on the Leader and Follower should appear to blink together.*

### 3. 
*Expand on exercise 2 by replacing "manual" mode switching with "automatic" mode switching.*  

**Criteria:**
  * *Both microcontrollers start in Follower mode.*
  * *If a microcontroller is in Follower mode and does not receive a packet for 3 seconds, the microcontroller switches to Leader mode.*
  * *If a microcontroller is in Leader mode and receives a packet at any time, the microcontroller switches to Follower mode.*
  * *Each microcontroller receives data on USART0 and sends data on USART1.*
### 4.
*After a microcontroller in Follower mode receives a packet on USART0 and displays that value on the LED connected to PA0, the microcontroller will then transmit that same value to another connected Follower.*  

