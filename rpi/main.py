#! /usr/bin/env python3

import display
import entrance

btn = Button(2)
display.open()

while True:
    if btn.is_pressed:
        display.refresh()
        entrance.run()
    sleep(0.1)

