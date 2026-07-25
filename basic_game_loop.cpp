//
// Created by Phoo Yamon Kyaw on 7/10/26.

#include <deque>
#include <SDL.h>
#include <stdio.h>
using namespace std;

//Screen dimensions
const int SCREEN_WIDTH =    600;
const int SCREEN_LENGTH =   600;

//Direction constants
enum Direction{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

//Starts up SDL and creates window
bool init();
bool loadMedia();
void close();

//Variables
SDL_Window* gWindow =   NULL;
SDL_Renderer* gRenderer = NULL;

struct segment{
    int x;
    int y;

    segment(int xval, int yval) {
        x = xval;
        y = yval;
    }
};


int main( int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize \n");
    }
    else {
        //Game States
        bool quit = false;
        bool game_over = false;

        SDL_Event e;
        Uint32 lastMoveTime = 0;
        Uint32 moveInterval = 150; //ms between moves

        //int rectx = 45;
        //int recty = 45;
        //const int rectwidth = 30;
        //const int rectlength = 30;

        const int grid_size = 30;
        deque <segment> caterpillar;
        caterpillar.push_front(segment(45,45));
        
        Direction current_direction = NONE;
        //int movespeed = 5;

        if (!loadMedia()) {
            printf("Failed to load media \n");
        }
        else {
            //Game Loop Starts

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
                        switch (e.key.keysym.sym) {
                            case SDLK_p:        current_direction = NONE; break;
                            case SDLK_UP:       current_direction = UP; break;
                            case SDLK_DOWN:     current_direction = DOWN; break;
                            case SDLK_LEFT:     current_direction = LEFT; break;
                            case SDLK_RIGHT:    current_direction = RIGHT; break;
                        }
                    }
                } //event keypress handling done
                // outer game play loop

                //Grid time
                Uint32 currentTime = SDL_GetTicks();

                if (!game_over) {
                    if (currentTime - lastMoveTime >= moveInterval) {

                        int newX = caterpillar.front().x;
                        int newY = caterpillar.front().y;

                        switch (current_direction) {
                            case NONE:  break;
                            case UP:    newY -= grid_size; break;
                            case DOWN:  newY += grid_size; break;
                            case LEFT:  newX -= grid_size; break;
                            case RIGHT: newX += grid_size; break;
                        }

                        //check if the rectangle has reached the edge of the screen
                        bool hits_left_wall = newX < 0;
                        bool hits_right_wall = newX + grid_size > SCREEN_WIDTH;
                        bool hits_top_wall = newY < 0;
                        bool hits_bottom_wall = newY + grid_size > SCREEN_LENGTH;

                        if (!hits_left_wall && !hits_right_wall && !hits_top_wall && !hits_bottom_wall) {
                            caterpillar.front().x = newX;
                            caterpillar.front().y = newY;
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
                        //2. Build the rectangle
                        SDL_Rect    rect = {caterpillar.front().x, caterpillar.front().y, grid_size, grid_size};

                        //3. Set draw color and draw it
                        SDL_SetRenderDrawColor(gRenderer, 115,115,115,255);
                        SDL_RenderFillRect(gRenderer,&rect);
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
