#include "Song.h"

Song::Song() 
{
	currLine = 0;
}
Song::~Song() {}

// Import song data into the vectors
void Song::importSong()
{
 	// Open up file
	inFile.open("Twinkle.txt", ios::in);
	if (!inFile)
	{
		cout << "Unable to open file";
		exit(1); // Terminate with error
	}

	// Buffer to store input values
	string buffer;

	// Reset row for a new song
	row = 0;

	// Flag to determine which column it is during input
	int flag = 0;

	// Loop through to save all the values
	while (!inFile.eof())
	{
		if (flag == 0)
		{
			// Get data from CSV file
			getline(inFile, buffer, ',');

			// Append to the vector
			if (!buffer.empty())
				time.push_back(stoi(buffer));
			
			// For debugging
			//cout << time[row] << ", ";

			// Increment counter to onOff
			flag++;
		}
		else if (flag == 1)
		{
			// Get data from CSV file
			getline(inFile, buffer, ',');

			// Append to the vector
			if (!buffer.empty())
				onOff.push_back(stoi(buffer));

			// For debugging
			//cout << onOff[row] << ", ";

			// Increment counter to note
			flag++;
		}
		else
		{
			// Get data from CSV file
			getline(inFile, buffer, '\n');

			// Append to the vector
			if (!buffer.empty())
				note.push_back(stoi(buffer));

			// For debugging
			//cout << note[row] << "\n";

			// Increment for one row of data
			row++;

			// Reset counter to time
			flag = 0;
		}
	}
}

// NOTE: INCOMPLETE
// Export current objects into an arduino .txt file
void Song::exportArduino()
{
	// TO-DO:
	// Iterate through both hand objects
	// Save the necessary values to the .txt file through

	// Open/create a new file to store the output for Arduino
	outFile.open("pianocontrol.txt", ios::out);
	if (!outFile)
	{
		cout << "Unable to open file";
		exit(1); // Terminate with error
	}

	// Loop until complete
	while (true)
	{
		// Example of out to output to file
		outFile << "H";
	}
}

// Add the next line of data from time, onOff, and note to the Hand classes
bool Song::addLine()
{
	// TO-DO:
	// If there is data remaining
	// Add the data to the hand
	// If it is the first line of data, use initialLH() and initialRH() to
	// initialize hand positions
	// If new hand position, create a new function to figure out which 
	// (if not both) hand needs to move to a new position
	// Return false to indicate that data remains to be added

	// If there is no data left
	// Return true to indicate completion

	// This function should check that the hands will not collide or exceed
	// boundaries of the piano
}

// Find initial starting hand positions using the note vector and buffer
int Song::initialHandPos()
{
	// Initialize variables to store initial hand positions
	int RHstart;
	int LHstart;

	// Flag to determine if the hand positions were set
	int flag = false;

	// Loop through all notes to find one that is far away from the first
	// Minimum distance set by handBuffer
	for (int i = 1; i < note.size(); i++) 
	{
		// Check distance from first note
		if (abs(note[i] - note.front()) > handBuffer) 
		{
			if (note[i] > note.front())
			{
				LHstart = note.front();
				RHstart = note[i];
			}
			else
			{
				LHstart = note[i];
				RHstart = note.front();
			}
			// Hand positions have been set
			flag = true;
			break;
       	}
	}

	if (flag)
	{
		RH.addHandPos(0, RHstart);
		LH.addHandPos(0, LHstart);
	}
	else
	{
		cout << "No note was >" << handBuffer << " semitones away." << endl;
		cout << "Hand positions were not set." << endl;
	}
}

// Checks how far do I need to move for a note in semitones
// Param: handPos is the current thumb position of hand
// Param: notesToMove is how many semit
// 
int Song::nextNote(int handPos, int notesToMove)
{
	// Get relative position (removing octaves)
	int pos = handPos % 12;

	// Calculate # octaves
	int octaves = notesToMove / 12;

	// Used to store # semitones
	int semitones;

	// Used to determine number of semitones to move one white key over
	int reference[7][7] = 
	{
		{ 0,2,4,5,7,9,11 },
		{ 0,2,3,5,7,9,10 },
		{ 0,1,3,5,7,8,10 },
		{ 0,2,4,6,7,9,11 },
		{ 0,2,4,5,7,9,10 },
		{ 0,2,3,5,7,8,10 },
		{ 0,1,3,5,6,8,10 }
	};

	// Matches relative white key position (to use in the array) based on note
	// 0 -> 0  |  2 -> 1  |  4 -> 2  |  5 -> 3  |  7 -> 4  |  9 -> 5  |  11 -> 6
	// The unused indices are set to -1
	int relativeHandPos[12] = {0, -1, 1, -1, 2, 3, -1, 4, -1, 5, -1, 6};
	
	// Use reference array to determine # semitones + 12 per octave
	semitones = reference[relativeHandPos[pos]][notesToMove];
	semitones += octaves * 12;

	return semitones;
}


// NOTE: CURRENTLY ONLY FINDS THE FINGER ON THE WHITE NOTES
// Finds which finger of the in-range note (from 1 to 8)
int Song::findFing(int handPos, int note)
{
	for (int i = 0; i < 8; i++)
	{
		if (handPos + nextNote(handPos, i) == note)
			return i + 1;
	}

	// No finger matches the note
	return -1;
}

// NOTE: CURRENTLY ONLY FINDS THE FINGER ON THE WHITE NOTES
// Calculates how far to move a hand, +ve or -ve (in semitones)
int song::howFar(int handPos, int note)
{
	// If in range of the current hand (theoretically should never execute)
	if (note >= handPos && note < handPos + 12)
	{
		// Return no motion
		return 0;
	}
	// If note is to the left of the hand position
	else if (note < handPos)
	{
		// NOTE: NEEDS UPDATING, THIS CODE IS INEFFICIENT
		// Could use difference between hand position and note instead
		for (int i = 0; i++; i < 100)
		{
			if (note + nextNote(note, i) == handPos)
				return -i;
		}
	}
	// If note is to the right of the hand position
	else
	{
		// NOTE: NEEDS UPDATING, THIS CODE IS INEFFICIENT
		// Could use difference between hand position and note instead
		for (int i = 0; i++; i < 100)
		{
			if (handPos + 12 + nextNote(handPos + 12, i) == note)
				return i;
		}
	}
}