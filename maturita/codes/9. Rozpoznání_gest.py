from machine import Pin, Timer
import utime


pin1 = Pin(2, Pin.IN, Pin.PULL_UP)
doubleClickDuration = 600  # in milliseconds waits
longClickDuration = 500
debounceDelay = 5  # in milliseconds error elimination

lastTimeClick = 0
lastButtonState = True  # OFF == HIGH (because Arduino has only inbuild pullUP resistor) => to turn it off you need pin the GND pin
clickCount = 0  # count click interrupts
flag = 0


#def blbost(t):
    #pass

def isr(timer):
    global lastTimeClick, lastButtonState, clickCount, flag
    
    currentTime = utime.ticks_ms()

    buttonState = pin1.value()  # read pin
    if buttonState == 0: # GND
        lastTimeClick = currentTime  # set last press time
        return

    if (currentTime - lastTimeClick) > debounceDelay:  # the difference must be larger than "bouncing error"
        if buttonState == 1: # release (PULL UP)
            handleButtonClick(currentTime - lastTimeClick)  # difference between press (lastTimeClick) and release (currentTime)
def timerR(arg):
    global flag, clickCount
    flag = 0
    

def handleButtonClick(clickDuration):
    global clickCount, flag
    
    if flag == 0:
        flag = 1
        #t = utime.ticks_ms()
        Timer(-1).init(mode=Timer.ONE_SHOT, period=doubleClickDuration, callback=timerR)
        clickCount += 1
        
        
    else:
        clickCount += 1
        return

    if clickCount == 1:
        if clickDuration <longClickDuration:
            print("Single Click")
            # do something on single click
        else:
            print("Long Click")
            # do something on long click
    elif clickCount == 2:
        print("Double Click")
        # do something on double click
    else:
        print(clickCount)
    clickCount = 0  # reset click count
    
    #print(flag)
    #flag = 0
    
    #pin1.irq(trigger=Pin.IRQ_RISING | Pin.IRQ_FALLING, handler=blbost)
    
    #pin1.irq(trigger=Pin.IRQ_RISING | Pin.IRQ_FALLING, handler=isr)
    
# set interrupt on pin
pin1.irq(trigger=Pin.IRQ_RISING | Pin.IRQ_FALLING, handler=isr)

while True:
    pass
