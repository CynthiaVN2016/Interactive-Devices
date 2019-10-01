int xPin = 34;
int yPin = 35;
int buttonPin = 36;
int switchPin = 39;

int redPin = 0;
int greenPin = 0;
int bluePin = 0;

int xVal = 0;
int yVal = 0;
int buttonState = 0;
int switchState = 0;

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
  buttonState = digitalRead(buttonPin);
  switchState = digitalRead(switchPin);

  printStates();
  delay(1000);
  // use map to chane rgb colors
  // outputValue = map(sensorValue, 0, 1023, 0, 255);

}

void printStates() {
//  Serial.print("X Val: ");
//  Serial.print(xVal);
//  Serial.print(" | Y Val: ");
//  Serial.println(yVal);

  Serial.print("Button State: ");
  Serial.println(buttonState);
  Serial.print("Swtich State: ");
  Serial.println(switchState);
}
