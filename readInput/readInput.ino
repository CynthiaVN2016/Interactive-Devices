int xPin = 34;
int yPin = 35;
int buttonPin = 36;
int switchPin = 39;

// setting PWM properties
const int freq = 5000;
const int redLEDChannel = 0;
const int greenLEDChannel = 1;
const int blueLEDChannel = 2;
const int resolution = 8;

int rgbValues[3] = {255, 255, 255};
int redPin = 19;
int greenPin = 18;
int bluePin = 5;
int selectedLED = redLEDChannel;

int xVal = 0;
int yVal = 0;
int prevButtonState = 0, buttonState = 0;
int prevSwitchState = 0, switchState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   // Setup serial
  // make the pushbutton & swtich's pin an input:
  pinMode(buttonPin, INPUT);
  pinMode(switchPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  ledcSetup(redLEDChannel, freq, resolution);
  ledcSetup(greenLEDChannel, freq, resolution);
  ledcSetup(blueLEDChannel, freq, resolution);
  ledcAttachPin(redPin, redLEDChannel);
  ledcAttachPin(greenPin, greenLEDChannel);
  ledcAttachPin(bluePin, blueLEDChannel);

  ledcWrite(redLEDChannel, 255);
  ledcWrite(greenLEDChannel, 255);
  ledcWrite(blueLEDChannel, 255);
}

void loop() {
  // put your main code here, to run repeatedly:
  yVal = analogRead(yPin);
  xVal = analogRead(xPin);
  prevButtonState = buttonState;
  prevSwitchState = switchState;
  buttonState = digitalRead(buttonPin);
  switchState = digitalRead(switchPin);
  
  printStates();
  // LED modulation
//  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) { 
//    ledcWrite(redLedChannel, dutyCycle);
//    delay(10);
//  }
//  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) { 
//    ledcWrite(redLedChannel, dutyCycle);
//    delay(10);
//  }

  delay(800); // delay has to be longer if selecting colors, but shorter for drawing mode
  // use map to chane rgb colors
  // outputValue = map(sensorValue, 0, 1023, 0, 255);

}

void printStates() {
//  if (xVal < 1000) { // reached lower threshold 
//    if (yVal < 1000) // go lower-left
//      Serial.write(41); 
//    else if (yVal > 3500) // go upper-right
//      Serial.write(42);
//    else 
//      Serial.write(10);
//  }
//  else if (xVal > 3500) { // reached upper threshold
//    if (yVal < 1000) 
//      Serial.write(43);
//    else if (yVal > 3500)
//      Serial.write(44);
//    else
//      Serial.write(20);
//  }
//  
//  if (yVal < 1000) {
//    Serial.write(30);
//  }
//  else if (yVal > 3500) {
//    Serial.write(40);
//  }

  // Testing out LED manipulation
  if (xVal < 500) { // reached lower threshold 
     selectedLED = (selectedLED + 2) % 3;
  }
  else if (xVal > 3500) { // reached upper threshold
     selectedLED = (selectedLED + 1) % 3;
  }

  Serial.println(selectedLED);
  
  if (yVal < 500) {
    rgbValues[selectedLED] = rgbValues[selectedLED] - 25;
    if (rgbValues[selectedLED] < 0)
      rgbValues[selectedLED] = 0;
  }
  else if (yVal > 3500) {
     rgbValues[selectedLED] = rgbValues[selectedLED] + 25;
    if (rgbValues[selectedLED] > 255)
      rgbValues[selectedLED] = 255;
  }

  Serial.print(rgbValues[redLEDChannel]);
  Serial.print(rgbValues[greenLEDChannel]);
  Serial.println(rgbValues[blueLEDChannel]);

  ledcWrite(redLEDChannel, rgbValues[redLEDChannel]);
  ledcWrite(greenLEDChannel, rgbValues[greenLEDChannel]);
  ledcWrite(blueLEDChannel, rgbValues[blueLEDChannel]);
  
  if (prevButtonState != buttonState) { // state change
    Serial.write(50);
  }
  if (prevSwitchState != switchState) {
    Serial.write(60);
  }
}
