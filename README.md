# Introduction to Robotics
Repo regarding the Introduction to Robotics Course, taken in the 3rd year of Computer Science, University of Bucharest.
Each section will belong to a homework, including requirements, implementation details, code and image files.

### [Assignment 1](https://github.com/cosminbvb/IntroductionToRobotics/tree/main/Assignment1)
Controlling the brightness of each channel of an RGB LED with the input given by 3 different potentiometers.

<details>

## Requirements
- Arduino UNO
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
- Arduino UNO
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