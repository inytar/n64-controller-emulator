# N64 Controller Emulator (using Teensy LC)

This is code to be compiled on the Teensy LC, so that it can emulate a Nintendo 64 controller. The Teensy communicates with the console by monitoring the voltage over the data wire: when it detects a request for information, it responds with the most recently queued controller input. Inputs are queued through the Teensy's communication with another computer over a Serial port - this allows the inputs to be determined by a program running independently of the Teensy Chip.

## Set up

You need an N64 controller you are willing to cut the cable of. The data wire, which is the white wire (of the cable's 3 internal wires white-data, black-ground, red-power). Connect the data wire to the Teensy's pin #12. We've done this through a bread board. Connect the teensy through a microusb, and in the project directory run this command in the terminal

```
platformio run -t upload
```

to compile the code and upload it onto the Teensy.

Identify the the serial port through which the Teensy is communicating with the computer. We have found this at 

```
/dev/tty.usb123456
```

or something similar.

### send_commands.py

The Python script takes the above Serial port as a command line argument and then generates random inputs to send over the Serial port to the Teensy which in turn sends them to the console (we have added a simple if statement to make sure the program never presses the start button - we were testing this on Super Smash Bros, and wanted to make sure it wouldn't quit the game).

The script is meant to be a basic example of how a script running on a non-Teensy system can communicate with the Teensy and dictate the contoller inputs it sends to the console.

### Communication Protocol

The console and the controller communicate over the data wire via sequences of bits represented by changes from high to low voltage at specific speeds.

* 0 BIT:
     _
 ___|
3 micro seconds of low voltage followed by 1 microsecond of high voltage

* 1 BIT:
   ___
 _|
1 micro second of low voltage followed by 3 microseconds of high voltage

* STOP BIT:
   __       __
__|    or _|
2 low followed by 2 high, or 1 low followed by two high

High voltage is the default inactive voltage.


The console sends an 8 bit message to the controller, generally of the form 00000001. This message is a request for controller input.

* Note: We respond to each message as if it is of this form (asking for controller input), and use an IntervalTimer to deal with cases where it is not. Periodically the console sends two requests in quick succession. The second is a request for controller input (00000001); the first is a request for non-controller input information (of the form 00000000), and the console will not process the controller's response as controller input. However, responding to this message with controller input causes no problems. The interval timer allows us to identify if we've received two requests in quick succession. If we have, we respond to the second request with the same controller input as we responded to the first. This way we can make sure no controller input is lost. We deal with the problem in this way, because the Teensy LC's execution of the basic library functions are not fast enough to distinguish between the console requests of 00000001 and 00000000.

The controller responds with a 32 bit signal. The first 16 bits represent analog buttons (0 means unpressed; 1 means pressed). The last 16 represent the joystick position - the first 8 are the position on the x-axis, and the last eight are the position on the y-axis.

The buttons from least to most significant bit are as follows (The 9th bit represents no button)

0:  A
1:  B
2:  Z
3:  S
4:  dU
5:  dD
6:  dL
7:  dR
8:  rst
9:  N/A
10: L
11: R
12: cU
13: cD
14: cL
15: cR
16-23: x-axis
25-31: y-axis
