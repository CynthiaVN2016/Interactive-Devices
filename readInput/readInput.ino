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
int bigRedPin = 6;
int greenPin = 18;
int bigGreenPin = 7;
int bluePin = 5;
int bigBluePin = 8;
int selectedLED = redLEDChannel;

int xVal = 1800;
int yVal = 1800;
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

//  pinMode(bigRedPin, OUTPUT);
//  pinMode(bigGreenPin, OUTPUT);
//  pinMode(bigBluePin, OUTPUT);

  // set up the LED Channels
  ledcSetup(redLEDChannel, freq, resolution);
  ledcSetup(greenLEDChannel, freq, resolution);
  ledcSetup(blueLEDChannel, freq, resolution);
  ledcAttachPin(redPin, redLEDChannel);
  ledcAttachPin(greenPin, greenLEDChannel);
  ledcAttachPin(bluePin, blueLEDChannel);

  ledcWrite(redLEDChannel, rgbValues[redLEDChannel]);
  ledcWrite(greenLEDChannel, rgbValues[greenLEDChannel]);
  ledcWrite(blueLEDChannel, rgbValues[blueLEDChannel]);
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

  // delay has to be longer if selecting colors, but shorter for drawing mode
  if (switchState == LOW) // drawing mode
    delay(20); 
  else 
    delay(200); // color picking mode
  // use map to chane rgb colors
  // outputValue = map(sensorValue, 0, 1023, 0, 255);

}

void printStates() {
  if (switchState == LOW) { // drawing mode
//    Serial.println("Drawing mode");
    if (xVal < 1000) { // reached lower threshold 
      if (yVal < 1000) // go lower-left
        Serial.write(41); 
      else if (yVal > 3500) // go upper-right
        Serial.write(42);
      else 
        Serial.write(10);
    }
    else if (xVal > 3500) { // reached upper threshold
      if (yVal < 1000) 
        Serial.write(43);
      else if (yVal > 3500)
        Serial.write(44);
      else
        Serial.write(20);
    }
    
    if (yVal < 1000) {
      Serial.write(30);
    }
    else if (yVal > 3500) {
      Serial.write(40);
    }
  }
  else { // color picking mode

  // Testing out LED manipulation
  if (xVal < 500) { // reached lower threshold 
     selectedLED = (selectedLED + 2) % 3;
  }
  else if (xVal > 3500) { // reached upper threshold
     selectedLED = (selectedLED + 1) % 3;
  }

//  Serial.println(selectedLED);
  
  if (yVal > 3500) {
    rgbValues[selectedLED] = rgbValues[selectedLED] - 25;
    if (rgbValues[selectedLED] < 0)
      rgbValues[selectedLED] = 0;
  }
  else if (yVal < 500) {
     rgbValues[selectedLED] = rgbValues[selectedLED] + 25;
    if (rgbValues[selectedLED] > 255)
      rgbValues[selectedLED] = 255;
  }

//  Serial.print(rgbValues[redLEDChannel]);
//  Serial.print(rgbValues[greenLEDChannel]);
//  Serial.println(rgbValues[blueLEDChannel]);

  ledcWrite(redLEDChannel, rgbValues[redLEDChannel]);
  ledcWrite(greenLEDChannel, rgbValues[greenLEDChannel]);
  ledcWrite(blueLEDChannel, rgbValues[blueLEDChannel]);
  }
  
  if (prevButtonState != buttonState) { // state change
    Serial.write(50);
  }
  // TODO: figure out how to send signals to indicate the mode 
  // when going back to drawing mode, send over the rgb values to processing 
  if (prevSwitchState != switchState) {
    Serial.write(switchState);
      if (switchState == LOW) { // drawing mode 
        // Turn off the LED 
        ledcWrite(redLEDChannel, 0);
        ledcWrite(greenLEDChannel, 0);
        ledcWrite(blueLEDChannel, 0);

        // Send over (rgb) values 
        Serial.write(rgbValues[redLEDChannel]);
        Serial.write(rgbValues[greenLEDChannel]);
        Serial.write(rgbValues[blueLEDChannel]);
      }
      else { // color picking mode
        ledcWrite(redLEDChannel, rgbValues[redLEDChannel]);
        ledcWrite(greenLEDChannel, rgbValues[greenLEDChannel]);
        ledcWrite(blueLEDChannel, rgbValues[blueLEDChannel]);
      }
  }
}
