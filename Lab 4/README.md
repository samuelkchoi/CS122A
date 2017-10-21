# Exercises

### 1. 
*Blink three LEDs connected to PD0,PD2, and PD4 at a rate of 1000ms. Use only one task to complete this functionality.*

### 2. 
*From the previous lab we had you implement three LEDs that blinked at different rates. PD0 at a rate of 500ms, PD2 at a rate of 1000ms and PD4 at a rate of 2500ms. Implement the same functionality using the FreeRTOS library. Use multiple tasks to complete this functionality and make them visible in your code.*

### 3. 
*Now we want to implement a state machine design where the LEDs will cycle through each LED one after another. Once it reaches the last LED it will bounce and go in the opposite direction. (Try simplifying your designs by using the shift operator.)* 

### 4. 
*(Challenge) Expand upon exercise 3 by adding a button which will reverse the direction of the LED cycle whenever it is pressed. (Hint: Review priorities to implement this.)*
