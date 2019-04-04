from selenium import webdriver
from gpiozero import Button
from time import sleep

driver = None

def open():
    driver = webdriver.Chrome()
    driver.get("https://z-park.eu-gb.mybluemix.net/parking/welcome")

def refresh():
    driver.refresh()

