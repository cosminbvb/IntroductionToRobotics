#include <EEPROM.h>

/* Shift register section */

const int dataPin = 12;  // DS
const int latchPin = 11; // STCP
const int clockPin = 10; // SHCP


/* 4 digit 7 segment display section */

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

const int displayCount = 4;

int digitArray[16] = {
//A B C D E F G DP 
  B11111100, // 0 -> 252
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};


int dp = B00000001;
bool dpState = LOW;
const int dpInterval = 500;  // dp blinking interval
unsigned long lastChanged = 0;

/* Joystick section */

const int xPin = A0;
const int yPin = A1;
const int swPin = 3;

int xValue = 0;
int yValue = 0;
bool joyMoved = false;

const int debounceDelay = 200; // for the switch debounce

const int minThreshold = 400;
const int maxThreshold = 750;


/* Others */

volatile bool selected = false; // HIGH = user pressed the switch and selected a display

int displayNumber = 0;        // reffers  to one of the 4 displays

int digits[4] = {0, 0, 0, 0}; // display content (it's actually displayed inversed)


void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (auto digit : displayDigits) {
    pinMode(digit, OUTPUT);
    digitalWrite(digit, LOW);
  }

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(swPin), readJoystickSw, FALLING);

  readStoredDigits();
  
  Serial.begin(9600);
}

void loop() {
  
  if (selected) {
    selectDigit();
  }
  else {
    selectDisplay();   
  }

  writeDisplay();
  
}

/* EEPROM functions */

// storing the digits array into EEPROM
void storeDigits() {
  Serial.println("storing into EEPROM");
  EEPROM.write(displayNumber, digits[displayNumber]);
}

// reading the digits array from the EEPROM
void readStoredDigits() {
  for (int i = 0; i < displayCount; i++) {
    digits[i] = EEPROM.read(i);
  }
}


/* Joystick functions */

void selectDisplay() {
  yValue = analogRead(yPin);

  if (yValue > maxThreshold && !joyMoved) {
    if (displayNumber > 0) {
      displayNumber--;
    }
    else {
      displayNumber = 3;
    }
    joyMoved = true;
  }

  if (yValue < minThreshold && !joyMoved) {
    if (displayNumber < 3) {
      displayNumber++;
    }
    else {
      displayNumber = 0;
    }
    joyMoved = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
    joyMoved = false;
  }
}

void selectDigit() {
  xValue = analogRead(xPin);
   
  if (xValue > maxThreshold && !joyMoved) {
    if (digits[displayNumber] < 9) {
      digits[displayNumber]++;
    }
    else {
      digits[displayNumber] = 0;
    }
    storeDigits();
    joyMoved = true;
  }

  if (xValue < minThreshold && !joyMoved) {
    if (digits[displayNumber] > 0) {
      digits[displayNumber]--;
    }
    else {
      digits[displayNumber] = 9;
    }
    storeDigits();
    joyMoved = true;
  }

  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }
  
}

void readJoystickSw() {
//  Serial.println("interrupt");
  static unsigned long lastInterrupt = 0; // static => only initialized once
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterrupt > debounceDelay) {
    // if there was no interrupt in the last debounceDelay ms, we change selected state
    selected = !selected;
    Serial.println("selected changed");
  }
  lastInterrupt = interruptTime;
}


/* Display functions */

void writeDisplay() {
  // for each display (out of the 4)
  for (int i = 0; i < displayCount; i++) {
    // we turn it on
    showDigit(i);
    if (i == displayNumber) {
      if (selected) {
         // decimal point always on
         writeReg(digitArray[digits[i]] | dp); 
      }
      else {
        // blinking decimal point (every dpInterval ms)
        if (millis() - lastChanged > dpInterval) {
          dpState = !dpState;
          lastChanged = millis();
        }
        if (dpState) {
          writeReg(digitArray[digits[i]] | dp);
        }
        else {
          writeReg(digitArray[digits[i]]);
        }
      }    
    }
    else {
      // no decimal point
      writeReg(digitArray[digits[i]]);
    }
    delay(6);
  }
}

void showDigit(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeReg(int digit) {

  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  
  digitalWrite(latchPin, HIGH);  
}
