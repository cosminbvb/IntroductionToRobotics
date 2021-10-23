// Potentiometers pins:
const int potPin1 = A0;
const int potPin2 = A1;
const int potPin3 = A2;

// RGB channels pins:
const int redPin = 6;
const int greenPin = 5;
const int bluePin = 3;

int potValue1 = 0;
int potValue2 = 0;
int potValue3 = 0;

// Brightness value for each channel
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void setup() {
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(potPin3, INPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);

  redValue = map(potValue1, 0, 1023, 0, 255);
  greenValue = map(potValue2, 0, 1023, 0, 255);
  blueValue = map(potValue3, 0, 1023, 0, 255);

  // PWM
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
