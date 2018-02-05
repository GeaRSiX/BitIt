/*------------------------------------------
|	Proj: Challenge1-UFCFVK-15-2 
|	File: main.cpp
|	Auth: Alexander Collins
|	Desc: Implement a simple game on the BBC Microbit that uses the LED matrix and at least two \
|			buttons or other sensors on the device.
|		  Game that queues several actions and awards the user points for acting them out within \
|			a certain time period (depending upon difficulty)
|	Date: Jan-Feb, 2018
|-----------------------------------------*/
//========
// MACROS
//========
// includes
#include "MicroBit.h"
#include "img.h"
// defines
#define DEBUG	1	//1 = print debug messages to serial
#define ROUNDS	10	//# game rounds
#define ACTIONS	2	//# user inputs
#define SPEED_MS	1500	//MS before user misses an action	//increase this if your finding the game too fast

//=========
// GLOBALS
//=========
MicroBit uBit;
// ACTIONS
int action[ACTIONS] = {
	MICROBIT_ID_BUTTON_A,
	MICROBIT_ID_BUTTON_B
};
// ACTION->IMG mapping
MicroBitImage action_image[ACTIONS][2] = {
	{IMG_A, IMG_leftarrow},
	{IMG_B, IMG_rightarrow}
};
// general
int score = 0;
int user_action = -1;
int round_action = -1;
bool game_over = false;
bool user_action_open = false;

//============
// PROTOTYPES
//============
void read_action(MicroBitEvent evt)
{
	if (user_action_open)
	{	
		// log user action
		user_action = evt.source;
		// close action window
		user_action_open = false;
	#if DEBUG
		uBit.serial.printf("READ: %i\r\n", evt.source);
	#endif
	}
}
void register_listeners()
{
	for (int i = 0; i < ACTIONS; i++)
		uBit.messageBus.listen(action[i], MICROBIT_EVT_ANY, read_action, MESSAGE_BUS_LISTENER_IMMEDIATE);
//	uBit.messageBus.listen(ACTION_0, MICROBIT_EVT_ANY, read_action, MESSAGE_BUS_LISTENER_IMMEDIATE);
//	uBit.messageBus.listen(ACTION_1, MICROBIT_EVT_ANY, read_action, MESSAGE_BUS_LISTENER_IMMEDIATE);
}
void start_screen();
void init_round();
void get_ready();
void next_action();
void check_score();
void print_score();

//======
// MAIN
//======
int main()
{
//init
	uBit.init();
	uBit.display.setDisplayMode(DISPLAY_MODE_BLACK_AND_WHITE_LIGHT_SENSE);
	register_listeners();
#if DEBUG
	uBit.serial.printf("\r\nSTART-----------------------------------------------------------\r\n");
#endif
//----

//loop
	while (1)
	{
		// play start screen until user presses action[0]
		user_action = -1;
		while (user_action != action[0])
		{
			user_action_open = true;
			start_screen();
		}
		// get ready player
		get_ready();
		// game loop
		score = 0;
		game_over = false;
		while (!game_over)
		{
			// init new round
			init_round();
			// display next action
			next_action();
			// check if user_action was correct
			check_score();
		}
		// print final score
		print_score();
	}
//----

//exit
#if DEBUG
	uBit.serial.printf("\r\nEND -------------------------------------------------------------\r\n");
#endif
	release_fiber();
//----
}

void start_screen()
{
#if DEBUG
	uBit.serial.printf("start_screen()\n\r");
#endif
	// display start screen animation loop
	int step = 0;
	while (user_action_open)
	{	//note: using a switch to cancel this loop at any point between animations
		switch (step)
		{
			case 0:
				uBit.display.scroll("START", 75);
				break;
			case 1:
				IMG_animation_square(&uBit, 2, 150, false);
				break;
			case 2:
				IMG_animation_flash(&uBit, IMG_A, IMG_blank, 2, 150);
				break;
			case 3:
				IMG_animation_flash(&uBit, IMG_leftarrow, IMG_blank, 2, 150);
				break;
			case 4:
				IMG_animation_square(&uBit, 2, 150, true);
				break;
			case 5:
				IMG_animation_flash(&uBit, IMG_A, IMG_blank, 2, 100);
				break;
			case 6:
				IMG_animation_flash(&uBit, IMG_leftarrow, IMG_blank, 2, 150);
				break;;
			case 7:
				IMG_animation_square(&uBit, 2, 150, false);
				step = -1;
				break;
		}
		step++;
	}
}

void get_ready()
{
#if DEBUG
	uBit.serial.printf("get_ready()\n\r");
#endif
	uBit.display.scroll("GET RDY", 75);
	IMG_animation_flash(&uBit, IMG_centerdot, IMG_blank, 2, 200);
}

void init_round()
{
	// generate new random seed
	uBit.seedRandom();
	// reset user_action
	user_action = -1;
	// select a random ACTION_* for the round
	round_action = uBit.random(ACTIONS);
	// allow user actions
	user_action_open = true;
#if DEBUG
	uBit.serial.printf("NEW ROUND: a=%i\r\n", round_action);
#endif
}

void next_action()
{
	// start timer
	unsigned long timestamp = uBit.systemTime();
	// display next action (for 1.5secs or until user_action)
	int step = 0;
	while (uBit.systemTime() < timestamp + 1500 && user_action == -1)
	{
		if (step == 0)
		{
			IMG_animation_flash(&uBit, action_image[round_action][0], IMG_blank, 1, 100);
			step++;
		}
		else if (step == 1)
		{
			IMG_animation_flash(&uBit, action_image[round_action][1], IMG_blank, 1, 100);
			step--;
		}
	}
	uBit.display.clear();
}

void check_score()
{
	if (user_action == action[round_action])
	{
		score++;
		uBit.display.print(IMG_tick);
	}
	else
	{
		game_over = true;
		uBit.display.print(IMG_cross);
	}
	uBit.sleep(2000);
}

void print_score()
{
	IMG_animation_rotation(&uBit, 2, 75, false);
	uBit.display.scroll("SCORE", 100);
	uBit.display.print(score);
	uBit.sleep(2000);
}

