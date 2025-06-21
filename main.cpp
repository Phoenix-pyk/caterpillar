#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct dot {
    int x;
    int y;

    dot(int xval, int yval) {
        x = xval;
        y = yval;
    }
};

//Dimensions of the board
const int boardwidth = 30; //y coordinate
const int boardlength = 30; //x coordinate

char direction = 'D';
deque <dot> caterpillar;
bool alive = true;

void move();
dot generatefood();
void checkwall();

int main() {
    srand(time(0));
    caterpillar.push_front(dot(3,3));

    //Implement gameplay

    cout << "code check 1";
    dot leaf = generatefood();

    while (alive) {
        //move();
        //checkwall();
        //if (!alive) break;
        //checkfood();
        //checkinput();
    }

    return 0;
}

void move() {
    int x = caterpillar[0].x;
    int y = caterpillar[0].y;
    if (direction == 'D' || direction == 'd') {
        //move right
        dot d(x+1,y);
        caterpillar.push_front(d);
        caterpillar.pop_back();
    }
    else if (direction == 'A' || direction == 'a') {
        //move left
        dot d(x-1,y);
        caterpillar.push_front(d);
        caterpillar.pop_back();
    }
    else if (direction == 'S' || direction == 's') {
        //move down
        dot d(x,y+1);
        caterpillar.push_front(d);
        caterpillar.pop_back();
    }
    else if (direction == 'W' || direction == 'w') {
        //move up
        dot d(x,y-1);
        caterpillar.push_front(d);
        caterpillar.pop_back();
    }
}

//function make sure food is not generated directly over the caterpillar
dot generatefood() {
    dot food(rand()%boardlength,rand()%boardwidth);
    for (dot d : caterpillar) {
        if (d.x == food.x && d.y == food.y) return generatefood();
    }
    return food;
}

//function check if the caterpillar head hits the wall and end game play if it does
void checkwall() {
    dot head = caterpillar[0];
    if (head.x>=boardlength || head.x<0 || head.y>=boardwidth || head.y<0) {
        cout <<"YOU DIED... GAME OVER...";
        alive = false;
    }
}