import RPi.GPIO as GPIO
import time

# Pin 27 = Toggle
GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(22, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(27, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
toggle = GPIO.input(27)

GPIO.add_event_detect(22, GPIO.RISING)  # add rising edge detection on a channel
GPIO.add_event_detect(23, GPIO.RISING)
GPIO.add_event_detect(17, GPIO.RISING)

X = False
Y = False
Button = False

while(True):
    Y = GPIO.event_detected(22)
    X = GPIO.event_detected(23)
    Button = GPIO.event_detected(17)
    str = ''
    if (Y):
        str += 'Y is Pressed! | '
    if (X):
        str += 'X is Pressed! | '
    if (Button):
        str += 'Button is Pressed! | '
    if (toggle != GPIO.input(27)):
        toggle = GPIO.input(27)
        str += 'Toggle changed state!'
    if (not str == ''):
        print(str)
    time.sleep(1)