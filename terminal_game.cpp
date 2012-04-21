/*

Text based game that needs to:


* Take a file input - it gets characters from that file, puts them into arrays
* Rain letters over a player (which is an ASCII character)
* Know where our player is at all times, know if a letter exists at that position

*/

#include <iostream>
#include <curses.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define INDENTATION 10
using namespace std;


// GAME VARIABLES

// A row of the chararacters in the 'rain' contains the letters in between the newline chars
string rainRow9 = "|######  ############|";
string rainRow8 = "|########  ##########|";
string rainRow7 = "|##########  ########|";
string rainRow6 = "|############   #####|";
string rainRow5 = "|#########  #########|";
string rainRow4 = "|######  ############|";
string rainRow3 = "|######  ############|";
string rainRow2 = "|######  ############|";
string rainRow1 = "|#######  ###########|";
string rainRow0 = "|########  ##########|";
string noStr	= "|                    |";

string strArray[10] = { rainRow0, rainRow1, rainRow2, rainRow3, rainRow4,rainRow5,rainRow6,rainRow7,rainRow8,rainRow9};
unsigned int index1 = 0;
vector<string> myvector;
int curLine = 5;
int strIndex = 1;
int curRun = 0;




// Prints the current game screen using the string array onto the window 
// * refresh() should be called afterwards
void printStrVector()
{
	curLine = 5;
	move(curLine, INDENTATION);

	vector<string>::iterator it;
	string row_str;
	const char *row;

	// Print every string in the array, each time skiping over to anothe line
	for (it=myvector.begin(); it != myvector.end(); it++)
	{
		row_str = *it;
		row = row_str.c_str();
		printw(row);
		printw("\n");
		curLine++;
		move(curLine,INDENTATION);
	}
}

// Shifts contents of the string array to the right once
void updateStrArray()
{
	rotate(myvector.begin(),myvector.begin()+9,myvector.end());
	myvector.erase(myvector.begin());
	myvector.insert(myvector.begin(), strArray[strIndex]);
}


int main(int argc, char* argv[]) {

	
	// initialize the string vector
	for (int j=0; j<10; j++)
	{
		if (j) myvector.push_back(noStr);
		else myvector.push_back(rainRow0);
	}

	/* During the first 10 runs, the string array will add new strings to the array */
	bool firstCycle = true;	
	
	initscr();
	noecho();

	// start of game loop
	while (true) {
		

		if (firstCycle)
		{

			/* Print the current string vector and update the string array */
			printStrVector();
			updateStrArray();
			/* Update the current run that we are on and the current string array index */
			strIndex++;
			curRun++;
		
			refresh();
		
			// wait a specific number of micro-seconds
			usleep(300*1000);

			// change the way we update the string array if we're no longer on our first cycle
			if (curRun > 8)	firstCycle = false;
		} 
		/* If no longer on the first cycle */
		else 
		{
			rotate(myvector.begin(),myvector.begin()+9,myvector.end());
			printStrVector();

			refresh();
			usleep(300*1000);
		}
			
	}

	printw("Press any key to exit the game");
	getch();
	
	endwin();
	

	return 0;

}
