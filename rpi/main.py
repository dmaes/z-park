#! /usr/bin/env python3

from gpiozero import Button
from time import sleep

import display
import entrance

btn = Button(2)
display.open()

while True:
    if btn.is_pressed:
        display.refresh()
        entrance.run()
    sleep(0.1)

