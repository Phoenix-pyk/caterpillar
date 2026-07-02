#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <termios.h>
#include <unistd.h>
#include <cctype>
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
char grid[boardwidth][boardlength]; //board

static termios Org_term{}; //Might not need it after frontend
static bool Raw_on = false; //Might not need it after frontend

void enableRawMode() {
    if (Raw_on) return;
    tcgetattr(STDIN_FILENO, &Org_term);
    termios raw = Org_term;

    raw.c_lflag &= ~(ECHO | ICANON); // no echo, no line buffering
    raw.c_cc[VMIN]  = 0;             // read returns immediately
    raw.c_cc[VTIME] = 0;             // no timeout

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    Raw_on = true;
} //Might not need it after frontend

void disableRawMode() {
    if (!Raw_on) return;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &Org_term);
    Raw_on = false;
} //Might not need it after frontend

//function declarations
void move();
dot generatefood();
void hitwall();
void eatfood();
void inputcheck();
bool isOpposite(char x, char y);
void draw();

int main() {
    srand(time(0));
    caterpillar.push_front(dot(15,15));


    //Implement gameplay
    cout << "code check 1";
    leaf = generatefood();

    //Enable RAW MODE here
    enableRawMode();

    while (alive) {
        //inputcheck();
        //move();
        //hitwall();
        //if (!alive) break;
        //eatfood();
    }

    //BREAK RAW MODE RIGHT HERE.
    disableRawMode();
    return 0;
}

//function moves the caterpillar accordingly to user input
void move() {
    int x = caterpillar[0].x;
    int y = caterpillar[0].y;
    dot d(0,0);
    if (direction == 'D') {
        //move right
        d.x = x+1;
        d.y = y;
    }
    else if (direction == 'A') {
        //move left
        d.x = x-1;
        d.y = y;
    }
    else if (direction == 'S') {
        //move down
        d.x = x;
        d.y = y+1;
    }
    else if (direction == 'W') {
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

//function check if the input direction is valid or not
void inputcheck() {
    char input;
    cin >> input;
    char INPUT = toupper(input);
    bool validinput = (INPUT == 'W' || INPUT == 'A' || INPUT == 'S' || INPUT == 'D');
    if (validinput) {
        if (caterpillar.size()>1 && isOpposite(direction,INPUT)) return;
        else direction = INPUT ;
    }
}

//helper function to prevent caterpillar from doing 180 degree turns
bool isOpposite(char x, char y) {
        return (x=='A'&&y=='D')||(x=='S'&&y=='W')||(x=='D'&&y=='A')||(x=='W'&&y=='S');
    }

//terminal screen display
void draw() {
    //1.Build a fresh picture on the board
    for (int y=0; y<boardwidth; y++) {
        for (int x=0; x<boardlength; x++) {
            grid[y][x]= '.';
        }
    }
    for (dot d: caterpillar) grid[d.y][d.x] = '0';

    dot head = caterpillar[0];
    grid[head.y][head.x] = '@';

    grid[leaf.y][leaf.x] = '*';

    //2.Clear the board
    cout << "\033[2J\033[H";

    //3.Print it
    for (int y=0; y<boardwidth; y++) {
        for (int x=0; x<boardlength; x++) {
            cout << grid [y][x];
        }
        cout << '\n' ;
    }
}