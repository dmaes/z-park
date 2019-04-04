from selenium import webdriver

def open():
    global driver
    driver = webdriver.Chrome()
    driver.get("https://z-park.eu-gb.mybluemix.net/parking/welcome")

def refresh():
    global driver
    driver.execute_script("getEmptySpots();")

