/*------------------------------------------
|	Proj: Challenge1-UFCFVK-15-2 
|	File: images.cpp
|	Auth: Alexander Collins
|	Desc: Implement a simple game on the BBC Microbit that uses the LED matrix and at least two \
|			buttons or other sensors on the device.
|		  Game that queues several actions and awards the user points for acting them out within \
|			a certain time period (depending upon difficulty)
|	Date: Jan-Feb, 2018
|-----------------------------------------*/
#ifndef _IMG_
#define _IMG_
//========
// MACROS
//========
// includes
#include "MicroBit.h"

//=========
// GLOBALS
//=========
// images
/*! Sets all pixels to 0
	- - - - -
	- - - - -
	- - - - -
	- - - - -
	- - - - -
*/
MicroBitImage IMG_blank			("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n");

/*! capital 'A', left-aligned
	- 1 1 - -
	1 - - 1 -
	1 1 1 1 -
	1 - - 1 -
	1 - - 1 -
*/
MicroBitImage IMG_A				("0,1,1,0,0\n1,0,0,1,0\n1,1,1,1,0\n1,0,0,1,0\n1,0,0,1,0\n");

/*! capital 'B', left-aligned
	1 1 1 - -
	1 - - 1 -
	1 1 1 - -
	1 - - 1 -
	1 1 1 - -
*/
MicroBitImage IMG_B				("1,1,1,0,0\n1,0,0,1,0\n1,1,1,0,0\n1,0,0,1,0\n1,1,1,0,0\n");

/*! right arrow, centered
	- - - - -
	- - - 1 -
	1 1 1 1 1
	- - - 1 -
	- - - - -
*/
MicroBitImage IMG_rightarrow	("0,0,0,0,0\n0,0,0,1,0\n1,1,1,1,1\n0,0,0,1,0\n0,0,0,0,0\n");

/*! left arrow, centered
	- - - - -
	- 1 - - -
	1 1 1 1 1
	- 1 - - -
	- - - - -
*/
MicroBitImage IMG_leftarrow		("0,0,0,0,0\n0,1,0,0,0\n1,1,1,1,1\n0,1,0,0,0\n0,0,0,0,0\n");

/*! line, top-left -> bot-right
	1 - - - -
	- 1 - - -
	- - 1 - -
	- - - 1 -
	- - - - 1
*/
MicroBitImage IMG_rotation0		("1,0,0,0,0\n0,1,0,0,0\n0,0,1,0,0\n0,0,0,1,0\n0,0,0,0,1\n");

/*! line, top -> bot, centered
	- - 1 - -
	- - 1 - -
	- - 1 - -
	- - 1 - -
	- - 1 - -
*/
MicroBitImage IMG_rotation1		("0,0,1,0,0\n0,0,1,0,0\n0,0,1,0,0\n0,0,1,0,0\n0,0,1,0,0\n");

/*! line, top-right -> bot-left
	- - - - 1
	- - - 1 -
	- - 1 - -
	- 1 - - -
	1 - - - -
*/
MicroBitImage IMG_rotation2		("0,0,0,0,1\n0,0,0,1,0\n0,0,1,0,0\n0,1,0,0,0\n1,0,0,0,0\n");

/*! line, left -> right, centered
	- - - - -
	- - - - -
	1 1 1 1 1
	- - - - -
	- - - - -
*/
MicroBitImage IMG_rotation3		("0,0,0,0,0\n0,0,0,0,0\n1,1,1,1,1\n0,0,0,0,0\n0,0,0,0,0\n");

/*! square (outer)
	1 1 1 1 1
	1 - - - 1
	1 - - - 1
	1 - - - 1
	1 1 1 1 1
*/
MicroBitImage IMG_square0		("1,1,1,1,1\n1,0,0,0,1\n1,0,0,0,1\n1,0,0,0,1\n1,1,1,1,1\n");

/*! square (inner)
	- - - - -
	- 1 1 1 -
	- 1 - 1 -
	- 1 1 1 -
	- - - - -
*/
MicroBitImage IMG_square1		("0,0,0,0,0\n0,1,1,1,0\n0,1,0,1,0\n0,1,1,1,0\n0,0,0,0,0\n");

/*! single center pixel
	- - - - -
	- - - - -
	- - 1 - -
	- - - - -
	- - - - -
*/
MicroBitImage IMG_centerdot		("0,0,0,0,0\n0,0,0,0,0\n0,0,1,0,0\n0,0,0,0,0\n0,0,0,0,0\n");

/*! tick
	- - - - -
	- - - - 1
	- - - 1 -
	1 - 1 - -
	- 1 - - -
*/
MicroBitImage IMG_tick			("0,0,0,0,0\n0,0,0,0,1\n0,0,0,1,0\n1,0,1,0,0\n0,1,0,0,0\n");

/*! cross
	1 - - - 1
	- 1 - 1 -
	- - 1 - -
	- 1 - 1 -
	1 - - - 1
*/
MicroBitImage IMG_cross			("1,0,0,0,1\n0,1,0,1,0\n0,0,1,0,0\n0,1,0,1,0\n1,0,0,0,1\n");

//============
// PROTOTYPES
//============
// animations
/*! flashes two images 'flashes' times for 'speed' ms
	1. displays 'img1' for 'speed' ms
	2. displays 'img2' for 'speed' ms
	3. repeat 'flashes' # times
*/
void IMG_animation_flash(MicroBit *uBit, MicroBitImage img1, MicroBitImage img2, int flashes, unsigned long speed)
{
	if (!speed)
		speed = 100;

	for (int i = 0; i < flashes; i++)
	{
		uBit->display.print(img1);
		uBit->sleep(speed);
		uBit->display.print(img2);
		uBit->sleep(speed);
	}

	uBit->display.clear();
}
/*!	shows a square getting bigger/smaller from center
if ('reverse' == false):
1.	1 1 1 1 1	2.	- - - - -	3.	- - - - -
	1 - - - 1		- 1 1 1 -		- - - - -
	1 - - - 1		- 1 - 1 -		- - 1 - -
	1 - - - 1		- 1 1 1 -		- - - - -
	1 1 1 1 1		- - - - -		- - - - -
with 'speed' ms between frames
*/
void IMG_animation_square(MicroBit *uBit, int loops, unsigned long speed, bool reverse)
{
	if (!speed)
		speed = 200;

	if (reverse == true)
	{
		for (int i = 0; i < loops; i++)
		{
			uBit->display.print(IMG_centerdot);
			uBit->sleep(speed);
			uBit->display.print(IMG_square1);
			uBit->sleep(speed);
			uBit->display.print(IMG_square0);
			uBit->sleep(speed);
		}
	}
	else
	{
		for (int i = 0; i < loops; i++)
		{
			uBit->display.print(IMG_square0);
			uBit->sleep(speed);
			uBit->display.print(IMG_square1);
			uBit->sleep(speed);
			uBit->display.print(IMG_centerdot);
			uBit->sleep(speed);
		}
	}

	uBit->display.clear();
}
void IMG_animation_rotation(MicroBit *uBit, int rotations, unsigned long speed, bool reverse)
{
	if (!speed)
		speed = 200;

	if (reverse == true)
	{
		for (int i = 0; i < rotations; i++)
		{
			uBit->display.print(IMG_rotation3);
			uBit->sleep(speed);
			uBit->display.print(IMG_rotation2);
			uBit->sleep(speed);
			uBit->display.print(IMG_rotation1);
			uBit->sleep(speed);
			uBit->display.print(IMG_rotation0);
			uBit->sleep(speed);
		}
	}
	else
	{
		for (int i = 0; i < rotations; i++)
		{
			uBit->display.print(IMG_rotation0);
			uBit->sleep(speed);
			uBit->display.print(IMG_rotation1);
			uBit->sleep(speed);
			uBit->display.print(IMG_rotation2);
			uBit->sleep(speed);
			uBit->display.print(IMG_rotation3);
			uBit->sleep(speed);
		}
	}

	uBit->display.clear();
}

#endif	//IMG

