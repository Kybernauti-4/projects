# https://microcontrollerslab.com/28byj-48-stepper-motor-raspberry-pi-pico-micropython/

from machine import Pin
from time import sleep

#definice pinů
IN1 = Pin(1,Pin.OUT)
IN2 = Pin(2,Pin.OUT)
IN3 = Pin(3,Pin.OUT)
IN4 = Pin(4,Pin.OUT)

#piny si dáme do pole
pins = [IN1, IN2, IN3, IN4]

#první cívka [1,0,0,0] druhá cívka [0,1,0,0] ...
coils = [[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]]
#proměná, která sleduje na které cívce jsem
coil = 0
#počet kroků  kolik chceme provést
num_step = 512

def turn():
    #ujištění že á funkce přístup k proměnným
    global coil, coils

    #máme jenom 4 cívky (0,1,2,3) tudíž když proměná coil má hodnotu 4
    #tak musí program proměnnou vrátit na 0
    if coil >= 4:
        coil = 0

    #Čtyři hodnoty co jsou v poli pro cívku se musí zapsat na piny postupně
    for i in range(len(coils)):
        pins[i].value(coils[coil][i])

    #otočili jsme se na nějakou cívku, tudíž další otočení musí být na cívku +1
    coil += 1

#smy4ka pro nějakou ukázku že to fachá
while True:
    for i in range(num_step):
        turn()
        sleep(0.01)
    
    sleep(2)