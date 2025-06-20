#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct position {
    int x;
    int y;

    position(int xval, int yval) {
        x = xval;
        y = yval;
    }
};

//Dimensions of the board
const int boardwidth = 30; //y coordinate
const int boardlength = 30; //x coordinate

char direction = 'D';
deque <position> caterpillar;

bool alive = true;



void move();

int main() {
    srand(time(0));
    caterpillar.push_front(position(3,3)); //IMPORTANT: Need to adjust so that it starts from the left top corner)

    //Implement gameplay

    cout << "code check 1";

    while (alive) {
        //move();
        //checkwall();
        //checkfood();
        //checkinput();
    }

    return 0;
}

void move() {
    if (direction == 'D' || direction == 'd') {
        //move right
    }
    else if (direction == 'A' || direction == 'a') {
        //move left
    }
    else if (direction == 'S' || direction == 's') {
        //move down
    }
    else if (direction == 'W' || direction == 'w') {
        //move up
    }
}

//this function make sure food is not generated directly over the caterpillar
position generatefood() {
    position food(rand()%boardlength,rand()%boardwidth);
    for (position p : caterpillar) {
        if (p.x == food.x && p.y == food.y) return generatefood();
    }
    return food;
}