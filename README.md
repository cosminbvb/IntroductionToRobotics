# Introduction to Robotics
Repo regarding the Introduction to Robotics Course, taken in the 3rd year of Computer Science, University of Bucharest.
Each section will belong to a homework, including requirements, implementation details, code and image files.

### [Assignment 1](https://github.com/cosminbvb/IntroductionToRobotics/tree/main/Assignment1)
Controlling the brightness of each channel of an RGB LED with the input given by 3 different potentiometers.

<details>

## Requirements
- Arduino
- Common Cathode RGB LED
- 3 potentiometers
- 2x100 Ohm, 1x220 Ohm resistors (or higher)
- Wires

## Setup
![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment1/setup.jpeg)

## Demo
You can watch a quick demo [here](https://youtu.be/YZvqX90rD-g).
  
</details>

### [Assignment 2](https://github.com/cosminbvb/IntroductionToRobotics/tree/main/Assignment2)
Crosswalk simulator: traffic lights for people and vehicles.

<details>

The system has the following states:
1. State 1 (default, reinstated after state 4 ends): green light for cars, red light for people, no sounds.   Duration: indefinite, changed by pressing the button.
2. State 2 (initiated by counting down 10 seconds after a button press): the light should be yellow for vehicles,  red for people and no sounds. Duration: 3 seconds.
3. State 3 (iniated after state 2 ends): red for cars, green for people and a beeping sound from the buzzer at a constant interval. Duration: 10 seconds.
4. State 4 (initiated after state 3 ends): red for cars, blinking green for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3. This state should last 5 seconds.

 ## Requirements
- Arduino
- 2xRed LED (I only had 1xRed so I used 1xRed & 1xRBG)
- 2xGreen LED
- 1xYellow LED
- 2x220 Ohm resistors (for each Led cluster cathode)
- Buzzer (passive / active)
- 1x100 Ohm resistor (for the buzzer)
- Button
- Wires

## Setup
![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment2/setup0.jpeg)

![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment2/setup1.jpeg)

## Demo
You can watch a quick demo [here](https://www.youtube.com/watch?v=L-AnE9UuTwI).

Serial monitor logs:
![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment2/monitor_output.png)
  
</details>

### [Assignment 3](https://github.com/cosminbvb/IntroductionToRobotics/tree/main/Assignment3)
EMF Detector

<details>

## Requirements
- Arduino
- 7 Segment Display
- Buzzer
- 1x100 Ohm resistor (for the buzzer)
- 2x330 Ohm resistors (for the display, also doable with only 1 resistor)
- Wires

## Setup
![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment3/setup0.jpeg)

## Demo
You can watch a quick demo [here](https://youtu.be/nbxJk5SI_a4).
  
</details>

### [Assignment 4](https://github.com/cosminbvb/IntroductionToRobotics/tree/main/Assignment4)
Controlling a 4 digit 7-segment display connected with a shift register with the input of a joystick while storing the displayed value in the EEPROM.

<details>
The decimal point indicates which digit is currently being controlled. When the decimal point is blinking, we can move the joystick to the left / right to choose another digit, or press down on the joystick to lock the digit in.
However, as long as the decimal point is blinking, it means that the digit hasn't been locked in (selected) and any up / down movement will be ignored. Once a digit has been locked in, we can now move the joystick up / down to choose which number will be displayed on the selected digit or press down on the joystick to unlock the digit. When a digit is locked in, any left / right movement will be ignored (meaning that to choose another digit you will first have to press the button to unlock the current digit). To avoid any confusion, in this context "digit" means one of the 4 7-segment displays.
  
## Requirements
- Arduino
- 4 digit 7-segment display
- 74hc595 shift register
- Joystick
- 4x330 Ohm resistors (for the display)
- Wires

## Setup
![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment4/setup0.jpeg)
![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment4/setup1.jpeg)

## Connection diagrams:

shift register - arduino
  
![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment4/reg-arduino.png)

shift register - display
  
![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment4/reg-display.png)
  
display - arduino (used a 330 Ohm resistor for each connection)
  
![](https://github.com/cosminbvb/IntroductionToRobotics/blob/main/Assignment4/display-arduino.png)

## Demo
You can watch a quick demo [here](https://youtu.be/auXu2F_4Vyw).
  
</details>