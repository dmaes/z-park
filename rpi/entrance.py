import RPi.GPIO as GPIO 
import time

def clearPins():
    for pin in range (4):
        GPIO.output(ControlPin[pin], 0)

def up():
    for i in range (128):
       for halfstep in range (8):
             for pin in range (4):
                GPIO.output (ControlPin[pin], seg[halfstep][pin])
                time.sleep (0.001)
def down():
    for i in range (128):
       for halfstep in reversed(range (8)):
             for pin in reversed(range (4)):
                GPIO.output (ControlPin[pin], seg[halfstep][pin])
                time.sleep (0.001)

def run():
    GPIO.setmode (GPIO.BCM)

    ControlPin = [5,6,13,19]

    for pin in ControlPin:
       GPIO.setup (pin, GPIO.OUT)
       GPIO.output (pin, 0)
       
    seg = [ [1,0,0,0],
            [1,1,0,0],
            [0,1,0,0],
            [0,1,1,0],
            [0,0,1,0],
            [0,0,1,1],
            [0,0,0,1],
            [1,0,0,1] ]

    down()

    time.sleep(3)

    up()

    clearPins()

    GPIO.cleanup()
