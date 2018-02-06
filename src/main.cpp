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
#define RESET		-1
#define SPEED_MS	1500	//MS user is allowed before timeout each round
#define NUM_INPUTS	6		//# actions user can take

//=========
// GLOBALS
//=========
MicroBit uBit;
//STRUCTS
struct INPUT {
	int id;				//Message Bus ID
	int evt;			//Message Bus Event
	MicroBitImage img;	//Image1 to flash when this INPUT appears
};
//VARIABLES
// list of user actions
INPUT actions[NUM_INPUTS] = {
	{ .id = MICROBIT_ID_BUTTON_A, .evt = MICROBIT_EVT_ANY, .img = IMG_A },
	{ .id = MICROBIT_ID_BUTTON_B, .evt = MICROBIT_EVT_ANY, .img = IMG_B },
	{ .id = MICROBIT_ID_GESTURE, .evt = MICROBIT_ACCELEROMETER_EVT_TILT_DOWN, .img = IMG_uparrow },
	{ .id = MICROBIT_ID_GESTURE, .evt = MICROBIT_ACCELEROMETER_EVT_TILT_UP, .img = IMG_downarrow },
	{ .id = MICROBIT_ID_GESTURE, .evt = MICROBIT_ACCELEROMETER_EVT_TILT_LEFT, .img = IMG_leftarrow },
	{ .id = MICROBIT_ID_GESTURE, .evt = MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT, .img = IMG_rightarrow }
};
//determines whether or not user input is ignored
bool user_action_window;
//user score, resets after ever game over
int score;
//determines whether or not a game is active
bool game_over;
//index of actions[], signals the action the user must perform to score
int round_action;
//index of actions[], signals the action user took
int user_action;

//============
// PROTOTYPES
//============
// if the event registers as one of actions[] log is as user_action, close user_action_window
void handle_event(MicroBitEvent evt)
{
	for (int a = 0; a < NUM_INPUTS; a++)
	{
		// id match & evt match
		if (actions[a].id == evt.source && actions[a].evt == evt.value)
			user_action = a;
		// id match & wildcard evt
		else if (actions[a].id == evt.source && actions[a].evt == MICROBIT_EVT_ANY)
			user_action = a;
		// wildcard id & evt match
		else if (actions[a].id == MICROBIT_ID_ANY && actions[a].evt == evt.value)
			user_action = a;
	}

	user_action_window = false;
}
// registers all the uBit listeners (based on actions[])
void register_listeners(MicroBitMessageBus *uBit)
{
	for (int i = 0; i < NUM_INPUTS; i++)
		uBit->listen(actions[i].id, actions[i].evt, handle_event, MESSAGE_BUS_LISTENER_IMMEDIATE);
}
// displays the start screen animation loop until user takes action[0]
void start_screen();
// displays some text & animations telling the user to GET RDY
void get_ready();
// initialises a new game round
void init_round();
// displays the next action for SPEED ms or until user makes an action
void display_action();
// checks if user_action matches round_action
bool user_scored();
// prints the current value of score and a rating
void print_score();

//======
// MAIN
//======
int main()
{
//init
	uBit.init();
	uBit.display.setDisplayMode(DISPLAY_MODE_BLACK_AND_WHITE_LIGHT_SENSE);
	register_listeners(&uBit.messageBus);
	
//loop
	uBit.display.scroll("BitIt!", 75);
	while(1)
	{
		start_screen();
		get_ready();
		//reset game
		score = 0;
		game_over = false;
		//game loop
		do {
			init_round();		//reset user_input and select random action[]
			display_action();	//if display_action() exits, the user made an input or was timed-out
		} while (user_scored());
		//print final score
		print_score();
	}

//exit
	release_fiber();
}

//===========
// FUNCTIONS
//===========
void start_screen()
{
	user_action = RESET;	//reset user action
	//loop until user makes action[0]
	while (user_action != 0)
	{
		// display start screen animation loop until user input is recieved
		user_action_window = true;
		//note: using a switch so the loop can be canceled at any point between animations
		int step = 0;
		while (user_action_window)
		{	switch (step)
			{
				case 0:
					IMG_animation_square(&uBit, 2, 150, false);
					break;
				case 1:
					uBit.display.scroll("START", 75);
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
					step = RESET;
					break;
			}
			step++;
		}
	}
	uBit.display.clear();
}
void get_ready()
{
	uBit.display.scroll("GET RDY", 75);
	IMG_animation_flash(&uBit, IMG_centerdot, IMG_blank, 3, 150);
}
void init_round()
{
	// generate a new random seed
	uBit.seedRandom();
	// select a random ACTION_* for the round
	round_action = uBit.random(NUM_INPUTS);
	// reset user_action
	user_action = RESET;
	// open the user action window
	user_action_window = true;
}
void display_action()
{
	unsigned long timestamp = uBit.systemTime();
	// display next action (for 1.5secs or until user_action)
	while (uBit.systemTime() < timestamp + SPEED_MS && user_action == RESET)
	{
		IMG_animation_flash(&uBit, actions[round_action].img, IMG_blank, 1, 100);
	}
	uBit.display.clear();
}
bool user_scored()
{
	if (user_action == round_action)
	{
		score++;
		uBit.display.print(IMG_tick);
		uBit.sleep(2000);
		return true;
	}
	else
	{
		uBit.display.print(IMG_cross);
		uBit.sleep(2000);
		return false;
	}
}
void print_score()
{
	IMG_animation_rotation(&uBit, 2, 75, false);
	uBit.display.scroll("SCORE", 75);
	uBit.display.print(score);
	uBit.sleep(2000);
	switch(score)
	{
		case 0:
		case 1:
		case 2:
		case 3:		uBit.display.scroll("NOPE", 75);	break;
		case 4:
		case 5:
		case 6:
		case 7:		uBit.display.scroll("OK", 75);	break;
		case 8:
		case 9:
		case 10:	uBit.display.scroll("GG", 75);			break;
		case 11:
		case 12:
		case 13:	uBit.display.scroll("NICE", 75);		break;
		case 14:
		case 15:
		case 16:
		case 17:	uBit.display.scroll("MASTER!!", 75);	break;
		case 18:
		case 19:
		case 20:	uBit.display.scroll("WINNER!!!!", 75);	break;
		default:	uBit.display.scroll("BEATS ME..", 75);	break;
	}
}

