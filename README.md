# Interactive-Devices

## Objective 

Build a "perfomable device" while satisfying all the requirements below. 

* Use all the hardware resources available (SPST switch, momentary button, analog joystick)
* Device must have an enclosure or enclosures
* Use the ESP32 (or any other Arduino-style microcontroller) and may additionally use the Raspberry Pi.

## Result 

The end result was essentially an etch a sketch. I love drawing and art, and I ended up gravitating towards a visual piece--more specifically, a piece where the user has a lot of control. The etch a sketch utilizes Processing that runs on the Raspberry Pi 3B+ while taking in signal from a button, swtich, and joystick through the ESP32 to create art. 

The goal was to emulate an environment and tool for the user to draw freely and comfortably, in a more natural setting. Of course, since we are drawing digitally, I decided to make the enclosure and presentation of the device more "natural" looking by giving it a wooden appearance that freqeuently appears in a setting where an artist is using real paints (wooden floors, brush handles, easels, etc.) 

The switch has two modes:

1. Drawing Mode
  * In order to draw a line, the user presses the button while moving the joystick. Moving the joystick without pressing the button still moves the cursor location.
2. Color Picking Mode 
  * LED's only turn on during the color picking mode as an indicator 
  * Move joystick left and right to pick an LED, and move it up and down to change the brightness
  * The rgb LED's brightness corresponds to the actual rgb value on a (0, 255) scale of the line being drawn on the screen 
    * i.e. Keeping only the red LED on makes the color of the line red 
    * i.e. Dimming the blue light makes the blue darker 
    
## Challenges 

There were many challenges along the way, some prominent ones were: 

* Creating the enclosure
* Figuring out serial communication between the Raspberry Pi and ESP32 
  
 

