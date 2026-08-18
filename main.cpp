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
struct Orb{
    float x, y, r, v_x, v_y;
    string color;
    Orb(float xi, float yi, float ri, float vxi, float vyi)
	: x(xi), y(yi), r(ri), v_x(vxi), v_y(vyi){}
};

/* static vars */

const int TER_COLS = engine.getTerminalWidth();
const int TER_ROWS = engine.getTerminalHeight();
static bool sFinished = false;


void drawCircle(const Orb &orb, const string &color){
    for (int y=0; y<TER_ROWS; y++){
	for (int x=0; x<TER_COLS; x++){
	    float distance = sqrt(pow(orb.y-y, 2) + 0.2 * pow(orb.x-x,2));
	    /* note that shrinking distance means more space gets in */
	    string str = color + "#";
	    if (distance < orb.r) engine.print(str, x, y);
	}
    }
    printf("\033[0m");

}

void updateCircle(Orb &orb){
    orb.x += orb.v_x;
    orb.y += orb.v_y;

    if (orb.y + orb.r > TER_ROWS){
	orb.v_y = -orb.v_y;
    } 

    if (orb.y < orb.r){
	orb.v_y = -orb.v_y;
    } 
    
    if (orb.x + orb.r > TER_COLS){
	orb.v_x = -orb.v_x;
    } 

    if (orb.x < orb.r){
	orb.v_x = -orb.v_x;
    }
}

/* actual functions */
void gameLoop(Orb &orb1, Orb &orb2, Orb &orb3){
    while (!sFinished)
    {
	engine.clearScreen();
	drawCircle(orb1, "\033[93m");
	drawCircle(orb2, "\033[35m");
	drawCircle(orb3, "\033[92m");
	updateCircle(orb1);
	updateCircle(orb2);
	updateCircle(orb3);
	usleep(100000);
    }
}

int main(){
    
    engine.setCanonicalAndCursor(0);
    engine.clearScreen();
    Orb orb1(60, 10, 8, 1, 1);
    Orb orb2(40, 20, 3, 1, 1);
    Orb orb3(20, 10, 6, 1, 1);
    
    /* multithreading, quit loop when 'q' */
    thread worker(gameLoop, ref(orb1), ref(orb2), ref(orb3));
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
