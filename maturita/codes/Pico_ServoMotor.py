# https://www.upesy.com/blogs/tutorials/pi-pico-servo-motor-sg90-on-micropython#

from machine import Pin, PWM
from time import sleep

sg90 = PWM(Pin(0, mode=Pin.OUT))

# 0.5ms/20ms = 0.025 = 2.5% duty cycle
# 2.4ms/20ms = 0.12 = 12% duty cycle

# 0.025*65535=1638
# 0.12*65535=7864

duty_min = 2,5
duty_max = 12

while True:
    sg90.duty_u16(duty_min/100*65535)
    sleep(1)
    sg90.duty_u16(duty_max/100*65535)
    sleep(1)