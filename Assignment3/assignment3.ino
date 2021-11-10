// 7 segment display section
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;

const int segSize = 8;
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

const int refreshRate = 200; // in ms
unsigned long lastUpdate = 0;

const int noOfDigits = 10;
bool digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};


void displayNumber(int digit, bool decimalPoint) {
  for (int i = 0; i < segSize; i++){
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(pinDP, decimalPoint);
}


// Buzzer section:
const int buzzerPin = 10;
const int buzzerBaseTone = 21000;
const int buzzerStep = 2000; // tone difference between 2 intensities
int buzzerTone;
unsigned long lastChanged;


// EMF detector section
const int sampleSize = 300; // how many samples (readings) at a time
int readings[sampleSize];   // samples array (in which we store the batch of readings)
int antenaPin = A0;
int value;                  // final value (displayed)
unsigned long sum = 0;      // total sum of the array
int senseLimit = 500;       // maximum value used for constraining


void setup() {
  // initializing each 7 seg display pin
  for (int i = 0; i < segSize; i++){
    pinMode(segments[i], OUTPUT);
  }
  pinMode(antenaPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < sampleSize; i++) {
    readings[i] = analogRead(antenaPin);
    sum += readings[i];
  }

  value = sum / sampleSize; // average over sampleSize readings
  value = constrain(value, 1, senseLimit); 
  value = map(value, 0, senseLimit, 0, 9); // mapping for display

  // updating the 7 seg display every "refreshRate" miliseconds
  if (millis() - lastUpdate > refreshRate) {
    displayNumber(value, false);
    lastUpdate = millis();
  }


  if (value > 2) {
    buzzerTone = buzzerBaseTone - value * buzzerStep; 
    tone(buzzerPin, buzzerTone);    
  }
  else {
    noTone(buzzerPin);
  }

  
  sum = 0;
}