from machine import Pin, PWM
from gpio_lcd import GpioLcd
 
# Create the LCD object
lcd = GpioLcd(rs_pin=Pin(16),
              enable_pin=Pin(17),
              d4_pin=Pin(18),
              d5_pin=Pin(19),
              d6_pin=Pin(20),
              d7_pin=Pin(21),
              num_lines=2, num_columns=16)
vo = PWM(Pin(22))
vo.freq(1000)         # set frequency
vo.duty_u16(32768)      # set duty cycle, range 0-65535
# #The following line of codes should be tested one by one according to your needs
#
# #1. To print a string to the LCD, you can use

lcd.putstr('circuitschools.')
# #2. Now, to clear the display.
# lcd.clear()
# #3. and to exactly position the cursor location
# lcd.move_to(0,1)
#lcd.putstr('LCD16x2display')
# # If you do not set the cursor position,
# # the character will be displayed in the
# # default cursor position starting from
# # 0, x and 0, y location which is the top left-hand side.
# # There are other useful functions we can use in using the LCD.
# #4. Show the cursor
# lcd.show_cursor()
# #5. Hide the cursor
# lcd.hide_cursor()
# #6. Turn ON blinking cursor
# lcd.blink_cursor_on()
# #7. Turn OFF blinking cursor
# lcd.blink_cursor_off()
# #8. Disable display
# lcd.display_off()
# this will only hide the characters
# #9. Enable display
# lcd.display_on()
# #10. Turn backlight OFF
# lcd.backlight_off()
# #11. Turn backlight ON
# lcd.backlight_on()
# # 12. Print a single character
# lcd.putchar('x')
# but this will only print 1 character
# #13. Display a custom characters using hex codes, you can create the character from <a href="https://maxpromer.github.io/LCD-Character-Creator/">here.</a>
# happy_face = bytearray([0x00,0x0A,0x00,0x04,0x00,0x11,0x0E,0x00])
# lcd.custom_char(0, happy_face)
# lcd.putchar(chr(0))

#LAYOUT
#VBUS - VDD, A
#GND -  VSS, K, RW
#G22 -  V0
#G21 -  D7
#G20 -  D6
#G19 -  D5
#G18 -  D4
#G17 -  E
#G16 -  RS