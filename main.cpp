#include "termigine.h"
#include <cmath> 
#include <print>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <thread>

using namespace std;

/* OOP */

Engine engine;
vector<Vec2> orb = {};

/* static vars */

const int TER_COLS = engine.getTerminalWidth();
const int TER_ROWS = engine.getTerminalHeight();
static bool sFinished = false;
static char sDirection = '0';
/* actual functions */


void gameLoop(vector<Vec2> &orb){
    while (!sFinished)
    {
	engine.clearScreen();
	vector<vector<char>> m = engine.drawTerminalBorder();

	/* collision detection */
	for (Vec2 &p : orb) {
	    if (m[p.y][p.x]!=' ') 
	    { // collision with border detected!
		/* bounce up and down for now */
		sDirection == '0' ? 
		    sDirection = '1' : sDirection = '0';
		break;	
	    }
	}

	/* draw movements */
	switch(sDirection)
	{
	    case '0':
		for (Vec2 &p : orb) {
		    p.y -= 1;
		    engine.print("*", p.x, p.y);
		}
		break;
	    case '1':
		for (Vec2 &p : orb) {
		    p.y += 1;
		    engine.print("*", p.x, p.y);
		}
		break;
	}
	

	usleep(100000);
    }
}

int main(){
    
    engine.setCanonicalAndCursor(0);
    engine.clearScreen();

    // vector<vector<char>> m = engine.drawTerminalBorder();
    // printf("m[%d][%d]\n", m.size(), m[1].size());
    // engine.setCanonicalAndCursor(1);
    // return 0;

    /* ======================== */
    
    float angle = 0.0;
    float x = 0;
    float y = 0;
     
    /* draw orb animation */
    while (angle < 2 * M_PI)
    {
	x = cos(angle) * 20 + TER_COLS/2;
	y = sin(angle) * 9 + TER_ROWS/2;
	
	orb.push_back(Vec2(round(x), round(y)));
	engine.print("*", round(x), round(y));
	
	angle+=0.1;
	usleep(10000);
    }

    /* multithreading, quit loop when 'q' */
    thread worker(gameLoop, ref(orb));
    char ch;
    while(ch!='q')
    {
	ch = getchar();
	if (ch == 'q')
	{
	    sFinished = true;
	    break;
	}
    }
    worker.join();

    engine.setCanonicalAndCursor(1);
    return 1;
}
