//
// Created by Phoo Yamon Kyaw on 7/10/26.

#include <deque>
#include <SDL.h>
#include <stdio.h>
#include <__xlocale.h>
using namespace std;

//Screen dimensions
const int SCREEN_WIDTH =    900;
const int SCREEN_LENGTH =   900;

//Direction constants
enum Direction{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

//Global Variables
struct segment{
    int x;
    int y;

    segment(int xval, int yval) {
        x = xval;
        y = yval;
    }
};
SDL_Window* gWindow =   NULL;
SDL_Renderer* gRenderer = NULL;
const int grid_size = 30;
deque<segment> caterpillar;
segment food(0,0);

//Starts up SDL and creates window
bool init();
bool loadMedia();
void close();
segment generatefood();
bool eatfood();
bool isOpposite(Direction x, Direction y);
bool check_collision( int x, int y, bool growing);
bool willEat(int x, int y);



int main( int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize \n");
    }
    else {
        //Game States
        bool quit = false;
        bool game_over = false;

        SDL_Event e;
        const int startInterval = 300;
        const int minInterval = 66;
        const int speedStep = 9;

        Uint32 lastMoveTime = 0;
        Uint32 moveInterval = startInterval; //ms between moves

        //int rectx = 45;
        //int recty = 45;
        //const int rectwidth = 30;
        //const int rectlength = 30;



        caterpillar.push_front(segment(30,30));
        
        Direction current_direction = NONE;
        Direction next_direction = NONE;
        //int movespeed = 5;

        if (!loadMedia()) {
            printf("Failed to load media \n");
        }
        else {
            //Game Loop Starts
            food = generatefood();
            // game play loop
            while (!quit) {

                //handle events first
                while (SDL_PollEvent(&e)!=0) {
                    //check if event is quit
                    //inner game keypress loop
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    //if it is a keypress, change direction
                    else if (e.type == SDL_KEYDOWN) {
                        Direction requested = current_direction;
                        switch (e.key.keysym.sym) {
                            case SDLK_p:        requested = NONE; break;
                            case SDLK_UP:       requested = UP; break;
                            case SDLK_DOWN:     requested = DOWN; break;
                            case SDLK_LEFT:     requested = LEFT; break;
                            case SDLK_RIGHT:    requested = RIGHT; break;
                            default:            requested = current_direction; break;
                        }
                        if (!(isOpposite(requested, current_direction))) next_direction = requested;
                    }
                } //event keypress handling done
                // outer game play loop

                //Grid time
                Uint32 currentTime = SDL_GetTicks();

                if (!game_over) {
                    if (currentTime - lastMoveTime >= moveInterval) {
                        current_direction = next_direction;
                        int newX = caterpillar.front().x;
                        int newY = caterpillar.front().y;

                        switch (current_direction) {
                            case NONE:  break;
                            case UP:    newY -= grid_size; break;
                            case DOWN:  newY += grid_size; break;
                            case LEFT:  newX -= grid_size; break;
                            case RIGHT: newX += grid_size; break;
                        }

                        //check collision
                        bool growing = willEat(newX, newY);
                        if (!check_collision(newX, newY, growing)) {
                            caterpillar.push_front(segment(newX, newY));
                            if (growing) {
                                food = generatefood();
                                if (moveInterval>minInterval) moveInterval -= speedStep;
                            }else {
                                caterpillar.pop_back();
                            }
                        } else {
                            //game over
                            game_over = true;
                        }
                        lastMoveTime = currentTime;
                    }
                    //Render to the screen
                    //1. Clear first
                    SDL_SetRenderDrawColor(gRenderer,0,0,0,255);
                    SDL_RenderClear(gRenderer);

                    if (game_over) {
                        //2. Build the rectangle
                        SDL_Rect    rect = {caterpillar.front().x, caterpillar.front().y, grid_size, grid_size};

                        //3. Set draw color and draw it
                        SDL_SetRenderDrawColor(gRenderer, 225,0,0,255);
                        SDL_RenderFillRect(gRenderer,&rect);
                    }else{
                        //Alive branch of the game loop

                        //==== Draw caterpillar segments ===
                        for (const auto& segment : caterpillar) {
                            //2. Build the rectangle
                            SDL_Rect    rect = {segment.x, segment.y, grid_size, grid_size};

                            //3. Set draw color and draw it
                            SDL_SetRenderDrawColor(gRenderer, 115,115,115,255);
                            SDL_RenderFillRect(gRenderer,&rect);
                        }

                        //4. Draw food
                        SDL_Rect    foodblock = {food.x, food.y, grid_size, grid_size};
                        SDL_SetRenderDrawColor(gRenderer, 0,255,0,255);
                        SDL_RenderFillRect(gRenderer,&foodblock);
                    }
                    //4. Present the Screen
                    SDL_RenderPresent(gRenderer);
                }
            }
        }


        close();
        return 0;
    }
}

bool init() {
    //Initialize flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)<0) {
        printf("Could not Init SDL, SDL_Error: %s \n", SDL_GetError());
        success = false;
    }
    else {
        //create the window and screen
        gWindow = SDL_CreateWindow("Game Loop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_LENGTH, SDL_WINDOW_SHOWN);
        if (gWindow==NULL) {
            printf("Window is null. SDL_Error: %s \n", SDL_GetError());
            success = false;
        }
        else {
            //Renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL ) {
                printf("Renderer error: %s \n", SDL_GetError());
                success = false;
            }
            /*else {
                SDL_SetRenderDrawColor(gRenderer,225,225,225,225);
                SDL_RenderClear(gRenderer);

                SDL_Rect    rect = {rectx, recty, rectwidth, rectlength};
                SDL_RenderFillRect(gRenderer, &rect);
            }*/
        }
    }
    return success;
}


bool loadMedia() {
    bool success = true;

    return success;
}

void close() {
    //Destroy Renderer and Window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Shut Down SDL
    SDL_Quit();
}

segment generatefood() {
    int cellsX = SCREEN_WIDTH / grid_size;
    int cellsY = SCREEN_LENGTH / grid_size;

    segment food((rand()%cellsX)*grid_size, (rand()%cellsY)*grid_size);

    for (segment d : caterpillar) {
        if (d.x == food.x && d.y == food.y) return generatefood();
    }
    return food;
}

/*bool eatfood() {
    segment head = caterpillar.front();
    if (head.x==food.x && head.y==food.y) {
        food = generatefood(); // respawn food elsewhere
        return true; // snake should grow
    }
    return false;
}*/

bool isOpposite(Direction x, Direction y) {
    return (x==LEFT && y==RIGHT) || (x==RIGHT && y==LEFT) || (x==UP && y==DOWN) || (x==DOWN && y==UP);
}

bool willEat(int x, int y) {
    return (x==food.x && y==food.y);
}

bool check_collision( int x, int y, bool growing) {
    // wall collision
    bool hits_left_wall = x < 0;
    bool hits_right_wall = x + grid_size > SCREEN_WIDTH;
    bool hits_top_wall = y < 0;
    bool hits_bottom_wall = y + grid_size > SCREEN_LENGTH;
    if (hits_left_wall || hits_right_wall || hits_top_wall || hits_bottom_wall) return true;

    //self collision
    for (size_t i = 0; i < caterpillar.size(); i++) {
       if (!growing && i == caterpillar.size()-1) continue; // don't check the tail if growing
        if (caterpillar[i].x == x && caterpillar[i].y == y) return true;
    }
    return false;
}