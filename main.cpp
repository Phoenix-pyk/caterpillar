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

int main() {
    srand(time(0));
    //Dimensions of the board
    const int boardwidth = 30;
    const int boardlength = 30;

    deque <position> caterpillar;
    caterpillar.push_back(position(rand()%boardlength, rand()%boardwidth));



    return 0;
}