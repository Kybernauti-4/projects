from machine import Pin
import utime

arr_position = [18, 19, 20, 21] # definování pinů pro pozici (1,2,3,4)
arr_segment = [8, 9, 10, 11, 12, 13, 14, 15] # definování pinů pro konkrétní "pixel" (a,b,c,d,e,f,g,h)

arr_pin_position = list() # seznam pro output pozici
arr_pin_segment = list() # seznam pro output "pixel" (segmanty - aby se nepletlo používám pixel)

# nastaví všechny piny na out  uloží do seznamu
for pin_number in arr_position:
    arr_pin_position.append(Pin(pin_number, Pin.OUT))
    
for pin_number in arr_segment:
    arr_pin_segment.append(Pin(pin_number, Pin.OUT))

# slovník pro jednotlivé pozice (defaultní hodnota - vše vypnuté)
data = {
    "default": (0,0,0,0,0,0,0,0),
    0: (1,1,1,0, 1,1,1,0), #A
    1: (0,1,1,0, 1,1,1,0), #H
    2: (1,1,1,1, 1,1,0,0), #O
    3: (0,1,1,1,1,0,0,0),  #J
}

# vynulování (zapnutí na HIGH)
for i in range (4):
    arr_pin_position[i].value(1)

# neustálá změna pozice a znměna znaku
while True:
    # adresuje jednotlivé pozice
    for i in range (4):
        arr_pin_position[i].value(0)
        
        # adresuje jednotlivé pixely
        for n in range(8):
            arr_pin_segment[n].value(data[i][n])
        
        # proti blikání (co nejmenší) + přechodu (zobazení 1 znaku na dvě pozice - co největší)
        utime.sleep_ms(5)
        
        # vynulování
        arr_pin_position[i].value(1)
        
# nezapomeň dát rezistory pro 1, 2, 3, 4 jinak shoříš! 
        