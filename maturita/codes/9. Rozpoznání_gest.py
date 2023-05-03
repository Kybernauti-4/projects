from machine import Pin, Timer
import utime


pin1 = Pin(2, Pin.IN, Pin.PULL_UP)
doubleClickDuration = 600  # in milliseconds waits
longClickDuration = 500
debounceDelay = 25  # in milliseconds error elimination

lastTimeClick = 0
lastButtonState = True  # OFF == HIGH (because Arduino has only inbuild pullUP resistor) => to turn it off you need pin the GND pin
clickCount = 0  # button pressed and released count
flag = 0 # timer is running?


def isr(timer):
    global lastTimeClick, lastButtonState, flag
    
    currentTime = utime.ticks_ms()

    buttonState = pin1.value()  # read pin
    if buttonState == 0: # GND
        lastTimeClick = currentTime  # set last press time
        return

    if (currentTime - lastTimeClick) > debounceDelay:  # the difference must be larger than "bouncing error"
        if buttonState == 1: # release (PULL UP)
            handleButtonClick(currentTime - lastTimeClick)  # difference between press (lastTimeClick) and release (currentTime)

def timerR(args):
    global clickCount, flag
    flag = 0
    clickCount += 1 # button pressed and released

def handleButtonClick(clickDuration):
    global clickCount, flag # count of clicks, if timer is running
    
    if flag == 0: # button has been pressed (1 time)
        
        flag = 1 # timer is running?
        
        # timer (mode = 1x, period = time of double click, callback = run when timer has value of the period)
        Timer(-1).init(mode=Timer.ONE_SHOT, period=doubleClickDuration, callback=timerR)
        
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
            # do something on tripple click...
        
        # reset click count
        clickCount = 0
        
    else: # button has been pressed while timer has been running
        clickCount += 1 # button pressed and released

      
    
# set interrupt on pin
pin1.irq(trigger=Pin.IRQ_RISING | Pin.IRQ_FALLING, handler=isr)


while True:
    pass
    # do something other when no interrupt is running (do not consume processing power)
