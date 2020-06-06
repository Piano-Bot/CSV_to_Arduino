#ifndef   __Hand__
#define   __Hand__
#include <iostream>
#include <vector>
#include <fstream>

// State to store each instance of a key-press changes
struct state
{
	int time;
	bool fingers[8];
};

// Hand positions struct to store the next ahnd position
struct handPos
{
	int time;
	int pos;
	vector<state> states;
};

using namespace std;

// Hand Class
class Hand
{
private:
	// Vector to store all hand positions
	vector<handPos> positions;
	int posNum;
	int stateNum;

public:
	// Constructor and destructor
	Hand();
	~Hand();

	// Adding hand positions and states
	void addHandPos(int time, int position);
	void addState(int time, bool fingers[8]);
	bool canMove();
	bool inRange(int note);
	int getHandPos();
	state getState();
	
};
#endif