int xPin = 34;
int yPin = 35;
int buttonPin = 36;
int switchPin = 39;

int redPin = 0;
int greenPin = 0;
int bluePin = 0;

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
  delay(20);
  // use map to chane rgb colors
  // outputValue = map(sensorValue, 0, 1023, 0, 255);

}

void printStates() {
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

  if (prevButtonState != buttonState) { // state change
//    Serial.print("Button State: ");
//    Serial.println(buttonState);
    Serial.write(50);
  }
  if (prevSwitchState != switchState) {
//    Serial.print("Swtich State: ");
//    Serial.println(switchState);
    Serial.write(60);
  }
}
