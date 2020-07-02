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

// Checks how far do I need to move for a note in white keys
// Param: notesToMove is how many semit
// Uses the current position of the hand
// Returns:
//	<0 	Move left
//	0 	In current range of fingers
//	>0 	Move right 
int Hand::handMoveDist(int note)
{
	// Get current position
	int currentPos = positions[posNum].pos;

	// Get relative position (removing octaves)
	int relativePos = currentPos % 12;

	// Calculate # octaves
	int octaves = floor(((double)note - (double)currentPos) / 12.0);

	// Calculate relative note position (removing octaves)
	int relativeNotePos = note % 12;

	// Used to store # white keys movements needed
	int toMove;

	// Used to determine number of white keys to move
	// First index is hand's relative white key position
	// Second index is the finger's relative position
	int moveReference[7][12] = 
	{
		// Semitones from C natural
		//0  1  2  3  4  5  6  7  8  9 10 11
		{ 0, 0, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6},
		{ 6, 6, 0, 0, 1, 2, 2, 3, 3, 4, 4, 5},
		{ 5, 5, 6, 6, 0, 1, 1, 2, 2, 3, 3, 4},
		{ 4, 4, 5, 5, 6, 0, 0, 1, 1, 2, 2, 3},
		{ 3, 3, 4, 4, 5, 6, 6, 0, 0, 1, 1, 2},
		{ 2, 2, 3, 3, 4, 5, 5, 6, 6, 0, 0, 1},
		{ 1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6, 0}
		// Formula is equivalent to:
		// ([firstRow] - (relativehandPos)) % 7
	};

	// Used to figure out hand position index for moveReference
	int relativeHandPos[12] = {0, -1, 1, -1, 2, 3, -1, 4, -1, 5, -1, 6};
	
	// Calculate relative hand position of white keys
	int handPosIdx = relativeHandPos[relativePos];

	// Find the number of white keys to move
	if (octaves == 0) // In range of current hand
	{
		return 0; // Don't need to move
	}
	else if (octaves > 0) // Move right
	{
		toMove = moveReference[handPosIdx][relativeNotePos];
		
		// Subtract 1 to account for hand span
		toMove += (octaves - 1) * 7;
	}
	else // Move left
	{
		toMove = moveReference[handPosIdx][relativeNotePos];
		toMove += octaves * 7;
	}
	
	return toMove;
}