import RPi.GPIO as GPIO
import time 

def bin_10 (value):
    return list(map(int, bin(value)[2:].zfill(8)))

dac = [26, 19, 13, 6, 5, 11, 9, 10]

GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT)

try:
    for i in range(256):
        GPIO.output(dac, bin_10(i))
        time.sleep(0.01)
    for i in range(255, -1, -1):
        GPIO.output(dac, bin_10(i))
        time.sleep(0.01)
finally:
    GPIO.output(dac, 0)
    GPIO.cleanup()