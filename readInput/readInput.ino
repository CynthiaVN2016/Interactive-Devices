int xPin = 34;
int yPin = 35;
int buttonPin = 36;
int switchPin = 39;

// setting PWM properties
const int freq = 5000;
const int redLedChannel = 0;
const int greenLedChannel = 1;
const int blueLedChannel = 2;
const int resolution = 8;

int redPin = 19, redValue = 255;
int greenPin = 18, greenValue = 255;
int bluePin = 5, blueValue = 255;
int selectedLED = redLedChannel;

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
  
  ledcSetup(redLedChannel, freq, resolution);
  ledcSetup(greenLedChannel, freq, resolution);
  ledcSetup(blueLedChannel, freq, resolution);
  ledcAttachPin(redPin, redLedChannel);
  ledcAttachPin(greenPin, greenLedChannel);
  ledcAttachPin(bluePin, blueLedChannel);

  ledcWrite(redLedChannel, 255);
  ledcWrite(greenLedChannel, 255);
  ledcWrite(blueLedChannel, 255);
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

  delay(800); // delay has to be longer if selecting colors
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
     switch(selectedLED) { 
      case redLedChannel: 
        selectedLED = blueLedChannel;
        break;
       case greenLedChannel: 
        selectedLED = redLedChannel;
        break;
       case blueLedChannel: 
        selectedLED = greenLedChannel;
        break;
     }
  }
  else if (xVal > 3500) { // reached upper threshold
     switch(selectedLED) { 
      case redLedChannel: 
        selectedLED = greenLedChannel;
        break;
       case greenLedChannel: 
        selectedLED = blueLedChannel;
        break;
       case blueLedChannel: 
        selectedLED = redLedChannel;
        break;
     }
  }

  Serial.println(selectedLED);
  
  if (yVal < 500) {
    switch(selectedLED) { 
      case redLedChannel: 
        redValue = redValue - 25;
        if (redValue < 0) 
           redValue = 0;
        break;
       case greenLedChannel: 
        greenValue = greenValue - 25;
        if (greenValue < 0) 
           greenValue = 0;
        break; 
       case blueLedChannel: 
        blueValue = blueValue - 25;
        if (blueValue < 0) 
           blueValue = 0;
        break;
     }
  }
  else if (yVal > 3500) {
     switch(selectedLED) { 
      case redLedChannel: 
        redValue = redValue + 25;
        if (redValue > 255) 
           redValue = 255;
        break;
       case greenLedChannel: 
        greenValue = greenValue + 25;
        if (greenValue > 255) 
           greenValue = 255;
        break; 
       case blueLedChannel: 
        blueValue = blueValue + 25;
        if (blueValue > 255) 
           blueValue = 255;
        break;
     }
  }

  Serial.print(redValue);
  Serial.print(greenValue);
  Serial.println(blueValue);

  ledcWrite(redLedChannel, redValue);
  ledcWrite(greenLedChannel, greenValue);
  ledcWrite(blueLedChannel, blueValue);
  
  if (prevButtonState != buttonState) { // state change
    Serial.write(50);
  }
  if (prevSwitchState != switchState) {
    Serial.write(60);
  }
}
