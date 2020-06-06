#include "Hand.h"

// Constructor to create a hand position with no fingers pressed
Hand::Hand()
{
	// Initialize position and state indices
	posNum = 0;
	stateNum = 0;
}

// Empty destructor
Hand::~Hand() {}

// Adding a hand position using given time and position
void Hand::addHandPos(int time, int position)
{
	// Create a new hand position
	handPos newPosition;
	newPosition.time = time;
	newPosition.pos = position;

	// Append created hand position
	positions.push_back(newPosition);

	// Reset state number and increment position index
	stateNum = 0;
	posNum++;
}

// Adding a fingers state using given time and state
void Hand::addState(int time, bool fingers[8])
{
	// Create new state
	state newState;
	bool nextFingers[8];
	int lastIndex = positions.size() - 1;

	// Iteratively copy over the finger state
	newState.time = time;
	for (int i = 0; i < 8; i++)
	{
		newState.fingers[i] = fingers[i];
	}

	// Append created state
	positions[lastIndex].states.push_back(newState);

	// Increment state index
	stateNum++;
}

// Check if any finger is pressed
bool Hand::canMove()
{
	// Get current state
	state currState = positions[posNum].states[stateNum];

	// Check if any fingers are pressed down
	for (int i = 0; i < 8; i++)
	{
		if (currState.fingers[i] == 1)
		{
			return false;
		}
	}
	return true;
}

// Checks if a note is within range of a hand position
bool Hand::inRange(int note)
{
	int pos = getHandPos();

	if (note < pos || note > pos + 12)
		return false;
	else
		return true;
}

// Return current hand position
int Hand::getHandPos()
{
	return positions[posNum].pos;
}

// Return current finger state
state Hand::getState()
{
	return positions[posNum].states[stateNum];
}