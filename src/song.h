#ifndef   __Song__
#define   __Song__
#include <iostream>
#include <string>
#include <fstream>
#include "Hand.h"

// May instead use a function to determine where the hands start
const int RHstart = 60; // Start on C4 for right hand
const int LHstart = 36; // Start on C2 for left hand

const int octave = 12; // Set #semitones
const int limitL = 48; // Left limit
const int limitR = 108; // Right limit

using namespace std;
class Song
{
private:
	// Left and right hand variables
	Hand LH;
	Hand RH;
	vector<int> time;
	vector<int> onOff;
	vector<int> note;
	int row;
	int currLine;

public:
	Song();
	~Song();

	void importSong();
	void exportArduino();
	bool addLine();
	int initialLH();
	int initialRH();
	int nextNote(int current, int notesToMove);
	int findFing(int handPos, int note);
    int howFar(int handPos, int note);
};
#endif