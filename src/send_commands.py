from __future__ import print_function
import sys
import serial
import struct

import random

random = random.SystemRandom()

def main():
    port = sys.argv[1]
    ser = serial.Serial(port, baudrate=115200)
    print(ser.name)
    x = 40
    count = 0
    while True:
        # x = random.randint(-80, 80)
        # y = random.randint(-80, 80)
        # buttons = random.randint(0, 2**16 - 1)
        # if buttons & 2**3:
        #     buttons -= 2**3
        # if buttons & 2**1:
        #     #p = random.randrange(10)
        #     #if p > 0:
        #     buttons -= 2**1
        # if buttons & 2**11:
        #     buttons -= 2**11
        # # buttons = buttons & 2**3
        # ser.write(get_write_value(buttons, x, y))
        ser.write(get_write_value('cU',x=x))
        ser.write(get_write_value(x=x))
        ser.write(get_write_value(x=x))
        ser.write(get_write_value('B', y=-80, x=x))
        for _ in xrange(9):
            ser.write(get_write_value())
        ser.write(get_write_value(y=40))
        count += 1
        if count >= 5:
            x *= -1
            count = 0


def get_write_value(buttons='', x=0, y=0):
    val = 0
    if isinstance(buttons, str):
        if 'A' in buttons:
            val += 2**0
        if 'B' in buttons:
            val += 2**1
        if 'Z' in buttons:
            val += 2**2
        if 'S' in buttons:
            val += 2**3
        if 'dU' in buttons:
            val += 2**4
        if 'dD' in buttons:
            val += 2**5
        if 'dL' in buttons:
            val += 2**6
        if 'dR' in buttons:
            val += 2**7
        if 'rst' in buttons:
            val += 2**8
        if 'LT' in buttons:
            val += 2**10
        if 'RT' in buttons:
            val += 2**11
        if 'cU' in buttons:
            val += 2**12
        if 'cD' in buttons:
            val += 2**13
        if 'cL' in buttons:
            val += 2**14
        if 'cR' in buttons:
            val += 2**15
    else:
        val = buttons

    x, = struct.unpack('B', struct.pack('b', x))
    y, = struct.unpack('B', struct.pack('b', y))
    val += x * (2**16)
    val += y * (2**24)

    byte = struct.pack('I', val)
    #print(':'.join('{:08b}'.format(ord(b)) for b in byte))
    return byte


if __name__ == '__main__':
    main()
