'''
pbitmap.py

    Draw a full screen bitmap on the display.

    convert bluemarble.jpg to bitmap module
        ../../../utils/imgtobitmap.py bluemarble.jpg 8 >bluemarble.py

    since the bitmap is large use mpy-cross to precompile the bluemarble.py module to save memory.
        mpy-cross bluemarble.py

    upload the compiled bitmap module `bluemarble.mpy` and example program `pbitmap.py`

    Bluemarble image courtesy of the NASA image and video gallery available at
    https://images.nasa.gov/


'''

import gc
import time
from machine import Pin, SPI
import gc9a01
import bluemarble

gc.enable()
gc.collect()


def main():
    '''
    Draw the bitmap on the display
    '''
    try:

        # initialize display

        tft = gc9a01.GC9A01(
            SPI(2, baudrate=80000000, polarity=0, sck=Pin(10), mosi=Pin(11)),
            240,
            240,
            reset=Pin(14, Pin.OUT),
            cs=Pin(9, Pin.OUT),
            dc=Pin(8, Pin.OUT),
            backlight=Pin(2, Pin.OUT),
            rotation=0)

        # enable display and clear screen
        tft.init()
        tft.fill(gc9a01.BLACK)

        # display bitmap
        tft.pbitmap(bluemarble, 0, 0)


    finally:
        # shutdown spi
        if 'spi' in locals():
            spi.deinit()


main()
