// Traffic Lights:
const int greenLightCars = 2;
const int yellowLightCars = 3;
const int redLightCars = 4;

// Pedestrian Lights
const int greenLightPed = 6;
const int redLightPed = 5;

// Pedestrian Button:
const int buttonPin = 7;
bool buttonState = LOW;
bool buttonRequest = 0; // no active request 
unsigned long requestTime; // time recorded when a pedestrian pushed the button
unsigned long lastDebounceTime = 0;
const unsigned int debounceDelay = 50; 
bool lastButtonState;
bool reading;

// Pedestrian Buzzer:
const int buzzerPin = 10;
const int buzzerTone = 5000;
const int buzzerDuration = 10;
const int buzzerIntervalLong = 1000;
const int buzzerIntervalShort = 500;
unsigned long lastChangedBuzzer = 0;

// State durations and countdowns:
const unsigned int state2Duration = 3000;
const unsigned int countdownToStep2 = 10000;
const unsigned int state3Duration = 10000;
const unsigned int state4Duration = 5000;

// Variables used for state 4 blinking green
bool greenState = HIGH; 
const unsigned int blinkingInterval = 500; 
unsigned long lastChanged = 0;

// Helpers:
unsigned long stateTime; // time recorded when the last state started

int currentState = 1;

void setup() {
  pinMode(greenLightCars, OUTPUT);
  pinMode(yellowLightCars, OUTPUT);
  pinMode(redLightCars, OUTPUT);
  pinMode(greenLightPed, OUTPUT);
  pinMode(redLightPed, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
}

void state1() {
  digitalWrite(greenLightCars, HIGH);
  digitalWrite(yellowLightCars, LOW);
  digitalWrite(redLightCars, LOW);
  digitalWrite(greenLightPed, LOW);
  digitalWrite(redLightPed, HIGH);
}

void state2() {
  digitalWrite(greenLightCars, LOW);
  digitalWrite(yellowLightCars, HIGH);
}

void state3() {
  digitalWrite(yellowLightCars, LOW);
  digitalWrite(redLightCars, HIGH);
  digitalWrite(greenLightPed, HIGH);
  digitalWrite(redLightPed, LOW);
  
  // buzzer for blind people
  if (millis() - lastChangedBuzzer >= buzzerIntervalLong) {
    tone(buzzerPin, buzzerTone, buzzerDuration);
    lastChangedBuzzer = millis();
  }
}

void state4() {
  if (millis() - lastChanged >= blinkingInterval) {
    greenState = !greenState;
    digitalWrite(greenLightPed, greenState);  
    lastChanged = millis();  
  }
  
  // buzzing quicker  
  if (millis() - lastChangedBuzzer >= buzzerIntervalShort) {
    tone(buzzerPin, buzzerTone, buzzerDuration);
    lastChangedBuzzer = millis();
  } 
}

void readPedestrianButton() {
  // debounce
  reading = !digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
    }
  }
  lastButtonState = reading;

}

void loop() {

  readPedestrianButton();
  
  if (currentState == 1 && buttonState && !buttonRequest) {
    Serial.println("Button pressed => starting 10s countdown till yellow light");
    // if we're in state1, the button has been pressed and there is no request in process:
    buttonRequest = 1;  // make a green light request
    buttonState = 0; // reset it
    requestTime = millis(); // start the 10 seconds countdown till the green light
  }
  if (currentState == 1 && buttonRequest == 1 && millis() - requestTime >= countdownToStep2) { 
    // if we're in state1, there is a request in process and the 10s countdown ended:
    buttonRequest = 0; // clear the request
    currentState = 2; // move to next state
    Serial.println("10s countdown over => yellow light on for 3 seconds");
    stateTime = millis(); // save state 2 start time
  }
  if (currentState == 2 && millis() - stateTime >= state2Duration) {
    // if we're in state2 and the 3s state duration ended, go to the next state:
    currentState = 3;
    Serial.println("3 seconds over => green light for pedestrians and red light for cars for 10 seconds");
    stateTime = millis();
  }
  if (currentState == 3 && millis() - stateTime >= state3Duration) {
    // if we're in state3 and the 10s state duration ended, go to the next state:
    currentState = 4;
    Serial.println("10 seconds over => blinking green for pedestrians for 5 seconds");
    stateTime = millis();
  }
  if (currentState == 4 && millis() - stateTime >= state4Duration) {
    // if we're in state4 and the 5s state duration ended, go to the next state:
    currentState = 1;
    Serial.println("5 seconds over => red for pedestrians and green for cars");
  }
  
  // depending on the currentState, this switch activates a certain state:
  switch(currentState) {
    case 1:
      state1();
      break;
    case 2:
      state2();
      break;
    case 3:
      state3();
      break;
    case 4:
      state4();
      break;
  }

}
