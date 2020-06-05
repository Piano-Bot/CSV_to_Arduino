#include "Helper.h"

Helper::List() {}
List::~List() {}

int Helper::importData(string filename, vector<int> &time, vector<int> &onOff, vector<int> &note)
{
    //Set up midi file to get information
	fstream inFile;
	inFile.open("Twinkle.txt", ios::in);
	if (!inFile)
	{
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	//Buffer to store input values
	string buffer;

	//Initialize arrays to store information
	int row = 0;

	//Flag to determine which column it is during input
	int flag = 0;

	//Loop through to save all the values
	while (!inFile.eof())
	{
		if (flag == 0)
		{
			getline(inFile, buffer, ',');
			if (!buffer.empty())
				time[row] = stoi(buffer);
			cout << time[row] << ", ";
			flag++;
		}
		else if (flag == 1)
		{
			getline(inFile, buffer, ',');
			if (!buffer.empty())
				onOff[row] = stoi(buffer);
			cout << onOff[row] << ", ";
			flag++;
		}
		else
		{
			getline(inFile, buffer, '\n');
			if (!buffer.empty())
				note[row] = stoi(buffer);
			cout << note[row] << "\n";
			row++;
			flag = 0;
		}
	}
	return row;
}

//Checks how far do I need to move for a note in semitones
int Helper::nextNote(int current, int notesToMove)
{
	int pos = current % 12;
	int pos_note;
	int octaves = notesToMove / 12;
	int relative = notesToMove % 7;
	int num;
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
	switch (pos)
	{
	case 0:
		pos_note = 0;
		break;
	case 2:
		pos_note = 1;
		break;
	case 4:
		pos_note = 2;
		break;
	case 5:
		pos_note = 3;
		break;
	case 7:
		pos_note = 4;
		break;
	case 9:
		pos_note = 5;
		break;
	case 11:
		pos_note = 6;
		break;
	default:
		cout << "Included black keys\n";
		break;
	}
	num = reference[pos_note][notesToMove];
	num += octaves * 12;
	return num;
}

//Checks if a note is within range of a hand position
bool Helper::inRange(int handPos, int note)
{
	if (note < handPos || note > handPos + 12)
		return 0;
	else
		return 1;
}

//Finds which finger of the in-range note
int Helper::findFing(int handPos, int note)
{
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		if (handPos + nextNote(handPos, i) == note)
			return i + 1;
	}
	return 0;
}

//Calculates how far to move a hand, +ve or -ve
int Helper::howFar(int handPos, int note)
{
	int i;
	if (note < handPos)
	{
		for (i = 0; i++; i < 100)
		{
			if (note + nextNote(note, i) == handPos)
				return -i;
		}
	}
	else
	{
		for (i = 0; i++; i < 100)
		{
			if (handPos + 12 + nextNote(handPos + 12, i) == note)
				return i;
		}
	}
}