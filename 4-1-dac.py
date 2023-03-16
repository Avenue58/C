import RPi.GPIO as GPIO

def bin_10 (value):
    return list(map(int, bin(value)[2:].zfill(8)))

dac = [26, 19, 13, 6, 5, 11, 9, 10]

GPIO.setmode(GPIO.BCM)
GPIO.setup(dac, GPIO.OUT)

try:
    while True:
        num = input()
        if num == 'q':
            break;

        num = int(num)

        if num < 256 and num >= 0:
            GPIO.output(dac, bin_10(num))
        else:
            print ("enter an integer NUMBER in [0, 255]")
            break

        print (3.3*num/256)

except ValueError:
    print ("enter an integer NUMBER in [0, 255]")
    
finally:
    GPIO.output(dac, 0)
    GPIO.cleanup()