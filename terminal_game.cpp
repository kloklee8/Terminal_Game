/*

Text based game that needs to:


* Take a file input - it gets characters from that file, puts them into arrays
* Rain letters over a player (which is an ASCII character)
* Know where our player is at all times, know if a letter exists at that position

*/

#include <iostream>
#include <curses.h>
#include <ncurses.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define INDENTATION 10
using namespace std;


// GAME VARIABLES
typedef unsigned short int num;
#define PLAYER "8_8"
#define LIVES 5
#define FPS 20
#define PPF 50
#define SECOND 1000000

num PLAYER_SIZE;
num rows;
num cols;

struct Position {
    num x;
    num y;
};

struct Ply {
    struct Position pos;
    num lives;
};

struct Ply ply;

int in;
num u;

num i;
num x;

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

	// Print every string in the array, each time skiping over to another line
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

void quit(const char* seq) {
    clear();
    curs_set(2);
    endwin();
    printf(seq);
    exit(0);
}

inline void draw(struct Position obj, const char* art) {
    mvprintw(obj.y, obj.x, art);
}

void draw_all() {
    clear();

/* Draws counter for lives on screen */
    mvprintw(rows-1, 0, "Lives: %u", ply.lives); 
    draw(ply.pos, PLAYER);
    
    refresh();
}

//Controls the Player, q- quit, p- pause
void run_ply() {
    for (x=0; x < PPF; ++x) {
        in = getch();
        usleep((SECOND/FPS) / PPF);

        if (in == ERR) {
            continue;
        }

        if (in == KEY_LEFT || in == 'a' || in == 'h') {
            ply.pos.x -= (ply.pos.x == 0) ? 0 : 1;
        } else if (in == KEY_UP || in == 'w' || in == 'j') {
            ply.pos.y -= (ply.pos.y == 0) ? 0 : 1;
        } else if (in == KEY_RIGHT || in == 'd' || in == 'k') {
            ply.pos.x += (ply.pos.x == cols-PLAYER_SIZE) ? 0 : 1;
        } else if (in == KEY_DOWN || in == 's' || in == 'l') {
            ply.pos.y += (ply.pos.y == rows-1) ? 0 : 1;
        } else if (in == 'q' || in == KEY_EXIT) {
            quit("Exited\n");
        } else if (in == 'p') {
			nodelay(stdscr,FALSE);
            mvprintw(0, 0, "~Paused~");
			getch();
			nodelay(stdscr,TRUE);
        }
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
//Main part used for game
    initscr();
    cbreak();
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, rows, cols);

    srand(time(NULL));
    PLAYER_SIZE = strlen(PLAYER);

    ply.lives = LIVES;

    while (1) {
        draw_all();

        run_ply();

        draw_all();
			
	}

	printw("Press any key to exit the game");
	getch();
	
	endwin();
	

	return 0;
	}
}