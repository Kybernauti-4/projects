import time
from neopixel import Neopixel
#from machine import Pin
import machine
import math
import utime
import FFT
machine.freq(270000000)


numpix = 30
pin = 29
pixels = Neopixel(numpix, 0, pin, "GRBW")

white = (255,255,255,255)
yellow = (155, 50, 0)
orange = (155, 50, 0)
green = (0, 155, 0)
blue = (0, 0, 155)
red = (155, 0, 0)
color0 = red

BRIGHTNESS = 100
pixels.brightness(BRIGHTNESS)

pixels.fill(orange)
pixels.set_pixel_line_gradient(0, 29, red, blue)
pixels.show()




def sum_list(lst):
    su = 0
    for n in lst:
        for k in n:
            su +=k
    return su

def disco_ball(led_values):
    new_values = []
    if sum_list(led_values)/255<15:
        for n in range(len(led_values)-1):
            rand = random.random()
            if rand < 0.33:
                led_values[n][0]=155
            elif rand > 0.66:
                led_values[n][1]=155
            else:
                led_values[n][2]=155
    
    k = sum_list(led_values)/255/8
    for i in range(len(led_values)):
        r, g, b, w = led_values[i]
        if random.random() < 0.5:
            # randomly switch red and green channels
            r, g = g, r
        if random.random() > 0.5:
            # randomly switch blue and white channels
            b, g = g, b
        # randomly adjust color intensity
        
        intensity = random.uniform(0.5/k, 1.3/k)
        r, g, b = [int(round(c * intensity)) for c in (r, g, b)]
        new_values.append([r, g, b, w])
    return new_values

def set_arr(arr):
    for i, n in enumerate(arr):
        pixels.set_pixel(i, (n))
        
def get():
    arr = list()
    for n in range(numpix):
        arr.append(list(pixels.get_pixel(n)))
    return arr

def shift(lst, n):
    """
    Shifts the elements of the list `lst` by `n` positions to the right.
    If `n` is negative, the elements are shifted to the left.
    """
    if len(lst) <= 1:
        return lst  # nothing to shift
    
    n = n % len(lst)  # ensure `n` is within bounds
    if n == 0:
        return lst  # no need to shift
    
    return lst[-n:] + lst[:-n] if n > 0 else lst[-n:] + lst[:-n]

def move(by):
    arr = shift(get(), by)

    set_arr(arr)
    pixels.show()

    
    #set_arr(shift(get(), 2))
    #pixels.show()

while True:
    data = FFT.get_FFT()
    
    n = 31  # number of output values
    count = 64
    step = 2  # step size for selecting values
    output = []  # list to hold the output values
    
    
    for i in range(1, n):
        start = i * step
        end = start + step
        chunk = data[start:end]
        chunk2 = data[-end:-start]
        avg = sum(chunk) / step
        avg2 = sum(chunk2) / step
        
        
        R = max(round(avg)*5-50,0)
        G = 0
        B = max(round(avg2)*5-50,0)
        #G = max(0,G-R)
        #B = B - R/2
        output.append((R,G,B))
   

    #print(output)
    set_arr(output)
    #pixels.show()
    move(15)
    pixels.show()