# Interactive-Devices

## Table of Contents  
* [Objective](#objective)  
* [Development](#development)
  * [Hardware](#hardware)
  * [Code](#code)
  * [Enclosure](#enclosure)
* [Result](#result)
* [Demo](#demo)
* [Challenges](#challenges)


<a name="objective"/>

## Objective 

Build a "perfomable device" while satisfying all the requirements below. 

* Use resources available (SPST switch, momentary button, analog joystick)
* Device must have an enclosure or enclosures
* Use the ESP32 (or any other Arduino-style microcontroller) and may additionally use the Raspberry Pi.

<a name="development"/>

## Development

I love drawing and art, and I ended up gravitating towards a visual piece--more specifically, a piece where the user has a lot of control. Since the project involved working heavily with hardware, wiring, etc.--all of which I had no experience with--I decided to use Processing, a software I used in my previous project to ease the load of learning new software while allowing me to have visual component to the project. With that in mind, I decided to make an etch a sketch. It utilizes Processing that runs on the Raspberry Pi 3B+ while taking in signal from a button, swtich, and joystick through the ESP32 to create art.

<a name="code"/>

#### Hardware

The first part of the development was to learn how to wire the inputs using a breadboard just to read in signal. I also learned to solder my wires and devices. I started taking in signal with the Raspberry PI 3B+, but switched over to use the ESP32 to read in the analog values from the joystick. I also decided later on to incorporate LED's into my device, which required me to learn about resistors and voltage in order to use LED's properly without burning it out. 

<a name="code"/>

#### Code 

Once the wiring was complete, I worked on the ESP32 until I was able to read in inputs from all 3 resources succesfully, then worked on establishing a serial connection between the ESP32 and Processing. I was able to take the inputs to start drawing basic lines; however at this point, I did not use the switch signal for anything. With that in mind, I decided to create two states in my program: a drawing mode and a color picking mode. To add more clarity to the user, I incorporated 3 LED lights into my device, and that involved use Arduino's Pulse Width Modulation. Explanations on the states will be discussed under the result section. Once everything worked on my laptop, I set up a connection between my Raspberry Pi and ESP32 to eventually run on a monitor. I used VNC viewer to order to visually work on my Rasperry Pi. 

<a name="enclosure"/>

#### Enclosure

The enclosure ended up being a simple box after much deliberation. Due to it being my first time using hardware, I decided to go down a simpler path with my enclosure to ensure the functionality of my device without having to worry about the enclosure obstructing any part of the deivce.

<a name="result"/>

### Result 

The goal was to emulate an environment and tool for the user to draw freely and comfortably, in a more natural setting. Of course, since we are drawing digitally, I decided to make the enclosure and presentation of the device more "natural" looking by giving it a wooden appearance that freqeuently appears in a setting where an artist is using real paints (wooden floors, brush handles, easels, etc.) 

The switch has two modes:

1. Drawing Mode
  * In order to draw a line, the user must continuously press the button while moving the joystick
  * Moving the joystick without pressing the button still moves the cursor location. So if the user stops pressing the button while moving the joystick and then presses it again, there will be a discontinuity within the drawing
2. Color Picking Mode 
  * LED's only turn on during the color picking mode as an indicator 
   * The rgb LED's brightness corresponds to the actual rgb value on a (0, 255) scale of the line being drawn on the screen 
    * i.e. Keeping only the red LED on makes the color of the line red 
    * i.e. Dimming the blue light makes the blue value smaller, which essentially starts to remove blue from the line color 
  * Move joystick left and right to select an LED, and move it up and down to change the brightness

<a name="demo"/>

## Demo
    
## Challenges 

There were many challenges along the way, some prominent ones were: 

* Creating the enclosure
* Figuring out serial communication between the Raspberry Pi and ESP32 
  
 

