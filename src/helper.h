#ifndef   __Helper__
#define   __Helper__
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Helper
{
public:
	Helper();
	~Helper();
    int importData(vector<int> &time, vector<int> &onOff, vector<int> &note);
	int nextNote(int current, int notesToMove);
    bool inRange(int handPos, int note);
    int findFing(int handPos, int note);
    int howFar(int handPos, int note);
};
#endif