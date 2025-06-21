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

//Global variables
char direction = 'D';
deque <dot> caterpillar;
bool alive = true;
dot leaf(0,0);

//function declarations
void move();
dot generatefood();
void hitwall();

int main() {
    srand(time(0));
    caterpillar.push_front(dot(15,15));

    //Implement gameplay
    cout << "code check 1";
    leaf = generatefood();

    while (alive) {
        //move();
        //hitwall();
        //if (!alive) break;
        //eatfood();
        //inputcheck();
    }

    return 0;
}

//function moves the caterpillar accordingly to user input
void move() {
    int x = caterpillar[0].x;
    int y = caterpillar[0].y;
    dot d(0,0);
    if (direction == 'D' || direction == 'd') {
        //move right
        d.x = x+1;
        d.y = y;
    }
    else if (direction == 'A' || direction == 'a') {
        //move left
        d.x = x-1;
        d.y = y;
    }
    else if (direction == 'S' || direction == 's') {
        //move down
        d.x = x;
        d.y = y+1;
    }
    else if (direction == 'W' || direction == 'w') {
        //move up
        d.x = x;
        d.y = y-1;
    }
    caterpillar.push_front(d);
}

//function make sure food is not generated directly over the caterpillar
dot generatefood() {
    dot food(rand()%boardlength,rand()%boardwidth);
    for (dot d : caterpillar) {
        if (d.x == food.x && d.y == food.y) return generatefood();
    }
    return food;
}

//function check food and keep the tail if food eaten and not otherwise to imitate movement
void eatfood() {
    dot head = caterpillar[0];
    if (head.x==leaf.x && head.y==leaf.y) leaf = generatefood();
    else caterpillar.pop_back();
}

//function check if the caterpillar head hits the wall and end game play if it does
void hitwall() {
    dot head = caterpillar[0];
    if (head.x>=boardlength || head.x<0 || head.y>=boardwidth || head.y<0) {
        cout <<"YOU DIED... GAME OVER...";
        alive = false;
        return;
    }
    for (int i = 1; i<caterpillar.size(); i++) {
        dot d = caterpillar[i];
        if (d.x==head.x && d.y==head.y) {
            cout <<"YOU DIED... GAME OVER...";
            alive = false;
            return;
        }
    }
}
