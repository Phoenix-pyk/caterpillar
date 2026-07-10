//
// Created by Phoo Yamon Kyaw on 7/10/26.

#include <SDL.h>
#include <stdio.h>

//Screen dimensions
const int SCREEN_WIDTH =    500;
const int SCREEN_LENGTH =   500;

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

int main( int argc, char* args[]) {
            if (!init()) {
                printf("Failed to initialize \n");
            }
            else {
                //Game States
                bool quit = false;
                SDL_Event e;

                int rectx = 45;
                int recty = 45;
                const int rectwidth = 30;
                const int rectlength = 30;
                Direction current_direction = NONE;
                int movespeed = 5;

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
                        switch (current_direction) {
                            case NONE:  break;
                            case UP:    recty -= movespeed; break;
                            case DOWN:  recty += movespeed; break;
                            case LEFT:  rectx -= movespeed; break;
                            case RIGHT: rectx += movespeed; break;
                        }
                        //Render to the screen

                        //1. Clear first
                        SDL_SetRenderDrawColor(gRenderer,0,0,0,255);
                        SDL_RenderClear(gRenderer);

                        //2. Build the rectangle
                        SDL_Rect    rect = {rectx, recty, rectwidth, rectlength};

                        //3. Set draw color and draw it
                        SDL_SetRenderDrawColor(gRenderer, 115,115,115,255);
                        SDL_RenderFillRect(gRenderer,&rect);

                        //4. Present the Screen
                        SDL_RenderPresent(gRenderer);
                    }

                }
            }
    close();
    return 0;
        }
