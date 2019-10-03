import processing.serial.*;

String val;
Serial myPort;
int xVal = 0, yVal = 0;
boolean buttonState = false, switchState = false;
int xPin = 34, yPin = 35, buttonPin = 36, switchPin = 8;
int prevXPos, prevYPos, xPos, yPos;
int[] rgbValues = {255, 255, 255};

void setup() { 
  //fullScreen();
  size(400,400);
  noStroke();
  println(Serial.list());
  xPos = width/2;
  prevXPos = width/2;
  yPos = height/2;
  prevYPos = height/2;
  stroke(255);
  
  myPort = new Serial(this, Serial.list()[2], 9600);
  myPort.bufferUntil('\n');
}

void draw() {
    
  if (myPort.available() > 0) {
    int info = myPort.read(); 
      println(info);
      
    switch(info) {
      case 10: // negative x value
        prevXPos = xPos;
        prevYPos = yPos;
        xPos = xPos - 5;
        if (xPos < 0) 
          xPos = 0;
        break;
      case 20: // positive x value
        prevXPos = xPos;
        prevYPos = yPos;
        xPos = xPos + 5;
        if (xPos > width) 
          xPos = width;  
        break;
      case 30: // negative y value
        prevYPos = yPos;
        prevXPos = xPos;
        yPos = yPos - 5;
        if (yPos < 0) 
          yPos = 0;
        break;
      case 40: // positive y value. Subtract b/c of screen coordinate
        prevYPos = yPos;
        prevXPos = xPos;
        yPos = yPos + 5;
        if (yPos > height) 
          yPos = height;
        break;
      case 41: // neg x & neg y == bottom left
        prevYPos = yPos;
        prevXPos = xPos;
        xPos = xPos - 5;
        yPos = yPos - 5;
        if (yPos < 0) 
          yPos = 0;
        if (xPos < 0) 
          xPos = 0;
        break;
      case 42: // neg x & pos y == top left
        prevYPos = yPos;
        prevXPos = xPos;
        xPos = xPos - 5;
        if (xPos < 0) 
          xPos = 0;
        yPos = yPos + 5;
        if (yPos > height) 
          yPos = height;
        break;
      case 43: // pos x & neg y == bottom right
        prevYPos = yPos;
        prevXPos = xPos;
        xPos = xPos + 5;
        if (xPos > width) 
          xPos = width;
        yPos = yPos - 5;
        if (yPos < 0) 
          yPos = 0;
        break;
      case 44: // pos x & pos y == top right
        prevYPos = yPos;
        prevXPos = xPos;
        xPos = xPos + 5;
        if (xPos > width) 
          xPos = width;
        yPos = yPos + 5;
        if (yPos > height) 
          yPos = height;
        break;
      case 50: // change in button state
        buttonState = !buttonState;
        break;
      case 1: // change in switch state -- color picking mode
        switchState = !switchState;
        break;
      case 0: // drawing mode
        switchState = !switchState;
        // read in new rgb values coming
        for (int col = 0; col < 3; col++) {
          int colVal = myPort.read();
          println(colVal);
          rgbValues[col] = colVal; 
        }
        stroke(rgbValues[0], rgbValues[1], rgbValues[2]);
        break;
    }
    
    if (buttonState) { // start drawing
      line(prevXPos, prevYPos, xPos, yPos);
      //println("(" + prevXPos + ", " + prevYPos + ") --> (" + xPos + ", " + yPos + ")");
    }
  }
}
