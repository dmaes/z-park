from selenium import webdriver
from gpiozero import Button
from time import sleep

driver = webdriver.Chrome()
driver.get("https://z-park.eu-gb.mybluemix.net/parking/api/empty_spots")

btn = Button(2)
while True:
    if btn.is_pressed:
        driver.refresh()
    sleep(0.1)

