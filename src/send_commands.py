from __future__ import print_function
import sys
import serial
import struct

import random

random = random.SystemRandom()


def main():
    port = sys.argv[1]
    ser = serial.Serial(port, baudrate=115200)

    while True:
        # generate random controller input
        x = random.randint(-80, 80)
        y = random.randint(-80, 80)
        buttons = random.randint(0, 2**16 - 1)
        # remove any presses of the start button
        if buttons & 2**3:
            buttons -= 2**3
        # write the appropriate byte values to the serial port
        ser.write(get_write_value(buttons, x, y))


def get_write_value(buttons=0, x=0, y=0):
    val = buttons

    x, = struct.unpack('B', struct.pack('b', x))
    y, = struct.unpack('B', struct.pack('b', y))
    val += x * (2**16)
    val += y * (2**24)

    byte = struct.pack('I', val)
    return byte


if __name__ == '__main__':
    main()
