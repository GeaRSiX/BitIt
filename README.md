# Bit It!
###### A simple game for the BBC micro:bit
###### Including an image/animation library for a BBC micro:bit 5x5 matrix led display

## Contents
1. [Overview](#Overview)
2. [Controls](#Controls)
3. [Modding](#Modding)
4. [Animations](#Animations)
4. [Build](#Build)
5. [Author](#Author)

## Overview

The game is based on [Bop It!](https://en.wikipedia.org/wiki/Bop_It) 
All you need to do is the action prompted on the matrix LED display within a certain time limit. 
The game continues until you take a wrong action or miss an action.
**See how high a score you can get!**


## Controls

The game begins by playing it's start screen animation loop. This loop will play until a game starts.
To start a game **press A**, then _GET RDY_:

* If the display flashes A, press A
* If the display flashes B, press B
* If the display flashes ↑, tilt the micro:bit away from you
* If the display flashes ↓, tilt the micro:bit toward you
* If the display flashes ←, tilt the micro:bit left
* If the display flashes →, tilt the micro:bit right

**Note: The accelerometer gestures seem to require quite vigorious gesturing. Try not to break your micro:bit.**

## Modding

The game is designed so that the controls are easily moddable.
~~For example, if you think the tilt controls are stupid~~
For example, if you only want to use the buttons A and B:
1. Change the new total number of actions the game is going to contain
```cpp
#define NUM_INPUTS 2
```
2. All the actions that are chosen from in the game are defined in the actions[] array, so remove all of the GESTURE actions
```cpp
INPUT actions[NUM_INPUTS] = {
	{ .id = MICROBIT_ID_BUTTON_A, .evt = MICROBIT_EVT_ANY, .img = IMG_A },
	{ .id = MICROBIT_ID_BUTTON_B, .evt = MICROBIT_EVT_ANY, .img = IMG_B }
}
```

3. DONE! You should also be able to add actions.

**Note: There must be at least 1 action, since actions[0] is used to move past the start screen.**

## Animations

I found myself writing a lot of animation loops and images for the 5x5 LED matrix, so I put them into img.h.
The images are MicroBitImage objects and all have comments showing exactly what they output.
The animations are functions which use the defined images and also have comments explaining exactly what they do.

## Build

The above build instructions are based on the _yotta_ build enviroment.
1. First set the build target to the BBC micro:bit
```bash
yt target bbc-microbit-classic-gcc
```
2. Next, install the depenencies (in this case it's the Lancaster University DAL runtime
```bash
yt install
```
3. Build the project
```bash
yt build
```
4. And finally copy the .hex file over to the BBC micro:bit device (assuming it's plugged in and shows up as a removable device)
```bash
cp build/bbc-microbit-classic-gcc/src/assignment-1-combined.hex /media/<USER>/MICROBIT
```
### Build Enviroment
One of the following are required to build this project
	| Build Environment | Documentation |
	| ------------- |-------------|
	| ARM mbed online | http://lancaster-university.github.io/microbit-docs/online-toolchains/#mbed |
	| yotta  | http://lancaster-university.github.io/microbit-docs/offline-toolchains/#yotta |

## Author
* Alexander Collins _(14029202)_