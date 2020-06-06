#include "Song.h"
#include "Hand.h"

using namespace std;
/* Several objectives and milestones:
 * 1. Converts to the correct format
 * 2. Adds in proper stepper controls
 * 3. Add optimization for hand paths (later)
 */

// In the Song and Hand classes, break down tasks into smaller functions
// Add as many as necessary

int main(void)
{
	// Create the song and import the .csv data
	Song song;
	song.importSong();

	// Flag to indicate if completed
	bool done = false;

	// While there is still data to add
	while (!done)
	{
		done = song.addLine();
	}
	
	// Export code in arduino format
	song.exportArduino();

	return 0;
}