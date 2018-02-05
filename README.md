# Bit It!
###### A simple game for the BBC micro:bit

## Contents
1. [Overview](#Overview)
2. [Controls](#Controls)
4. [Build](#Build)
3. [Enviroments](#Enviroments)

## Overview

The game is based on [Bop It!](https://en.wikipedia.org/wiki/Bop_It). All you need to do is the action prompted on the matrix LED display within a certain time limit.
The game continues until you take a wrong action or miss an action.
**See how high a score you can get!**
~~p.s. i hope you appreciate the awesome animations~~

## Controls

The game begins by playing it's start screen animation loop. This loop will play until a game start.
To start a game **press A**, then _GET RDY_:

* If the display flashes **A** and **←**, press **A**
* If the display flashes **B** and **→**, press **B**

You've got 1.5 seconds before time runs out, if you're too slow you can increase the SPEED_MS macro in src/main.cpp

## Build

These instructions will only work in the correct build enviroment. See [Enviroment Setup](#Enviroment) for details.
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

## Enviroment

| Build Environment | Documentation |
| ------------- |-------------|
| ARM mbed online | http://lancaster-university.github.io/microbit-docs/online-toolchains/#mbed |
| yotta  | http://lancaster-university.github.io/microbit-docs/offline-toolchains/#yotta |

## Author
* Alexander Collins _(14029202)_