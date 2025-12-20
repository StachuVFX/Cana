//
//  Main.cpp
//  Cana
//
//  Created by Stachu on 16.12.2025.
//

/*
    Possible optimizations:
- inline functions
 
    TODO:
 - add drawTriangle function
 - create Cana class
 - maybe change functions arguments to references
 - implement timing
 - test if references and pointers are faster
 
    DONE:
 - make color struct (learn how to use structs)
 - made variables static (Cherno C++ 21)
*/

//  System Includes
#include <iostream>
#include <thread>

//  SDL Includes
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

//  Custom Includes
#include "Cana_screen.h"
#include "Cana_draw.h"

//  Defines
#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 900
#define DRAW_WIDTH 120
#define DRAW_HEIGHT 90

//  Structs

//  Function declarations

//  Variable declarations
Uint32 Cana_Color::black;
Uint32 Cana_Color::white;
Uint32 Cana_Color::red;
Uint32 Cana_Color::green;
Uint32 Cana_Color::blue;
Uint32 Cana_Color::cyan;
Uint32 Cana_Color::magenta;
Uint32 Cana_Color::yellow;

//  Main function
int main(int argc, char* argv[]) {
/* Startup */
    static SDL_Window *window = NULL;
    static SDL_Renderer *renderer = NULL;
    /* Set up app metadata */
    SDL_SetAppMetadata("Cana", "0.1.1", "name.stachu.Cana");
    /* Check if SDL Video works */
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    /* Create window and renderer (renderer mandatory in SDL3) */
    if (!SDL_CreateWindowAndRenderer("Cana", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create a window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
/* Game setup */
    /* Variables */
    static SDL_Event event;
    static bool running = true;
    static int screen_width = 0;
    static int screen_height = 0;
    static int draw_width = DRAW_WIDTH;
    static int draw_height = DRAW_HEIGHT;
    SDL_GetWindowSize(window, &screen_width, &screen_height);
    /* Create texture for the renderer and usable surfaces */
    static SDL_Texture* rendererTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screen_width, screen_height);
    static SDL_Surface* windowSurface = SDL_CreateSurface(screen_width, screen_height, SDL_PIXELFORMAT_ARGB8888);
    static SDL_Surface* drawingSurface = SDL_CreateSurface(draw_width, draw_height, SDL_PIXELFORMAT_ARGB8888);
    /* Prepare pixel buffer pointers for surfaces and texture */
    Uint32* drawingSurface_pixels = (Uint32*)drawingSurface->pixels; /* (assign only to remember how, the surface is not locked anyway) */
//    void* rendererTexture_pixels;
//    int rendererTexture_pitch;
    
    /* Colors */
    Cana_Color::black = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 0, 0, 0);
    Cana_Color::white = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 255, 255, 255);
    Cana_Color::red = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 255, 0, 0);
    Cana_Color::green = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 0, 255, 0);
    Cana_Color::blue = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 0, 0, 255);
    Cana_Color::cyan = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 0, 255, 255);
    Cana_Color::magenta = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 255, 0, 255);
    Cana_Color::yellow = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 255, 255, 0);
    
/* Game loop */
    while (running) {
        /* Sleep in case of memory leaks lol */
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
    /* Events */
        while (SDL_PollEvent(&event)) {
            /* Keyboard */
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                    running = false;
                }
            }
            /* Window resized */
            else if (event.type == SDL_EVENT_WINDOW_RESIZED) {  /* set window texture and surface again */
                SDL_GetWindowSize(window, &screen_width, &screen_height);
                SDL_DestroyTexture(rendererTexture);
                rendererTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screen_width, screen_height);
                SDL_DestroySurface(windowSurface);
                windowSurface = SDL_CreateSurface(screen_width, screen_height, SDL_PIXELFORMAT_ARGB8888);
            }
            /* Window quit */
            else if (event.type == SDL_EVENT_QUIT) {   /* stop the game loop */
                running = false;
            }
        }
        
    /* Render */
        /*   Drawing start */
        /*    (if ever draws incorrectly, the reason might be using width instead of pitch) */
        /* Lock drawing surface and assign pixel buffer pointer */
        SDL_LockSurface(drawingSurface);
        drawingSurface_pixels = (Uint32*)drawingSurface->pixels;
        
//        clear(drawingSurface_pixels, draw_width, draw_height, blue);
        Cana_clear(drawingSurface_pixels, draw_width * draw_height, Cana_Color::blue);
        
        //drawSquare_old(pixels, draw_width, draw_height, 100, red);
//        drawSquare(pixels, draw_width, draw_height, 200, 400, 300, white);
        Cana_drawSquare(drawingSurface_pixels, draw_width, draw_height, 0, 0, 70, Cana_Color::green);

//        drawLine(pixels, draw_width, draw_height, Point(100, 100), Point(300, 500), red);
//        drawLine(pixels, draw_width, draw_height, Point(100, 500), Point(300, 100), red);
        Cana_drawLine(drawingSurface_pixels, Cana_Point(draw_width, draw_height), Cana_Point(25, 30), Cana_Point(95, 60), Cana_Color::red);

        //drawTriangle(pixels, draw_width, draw_height, Point(600, 100), Point(500, 500), Point(700, 500), green, 1);
//        drawTriangle(pixels, draw_width, draw_height, Point(-150, 550), Point(550, -50), Point(950, 650), green, 1);

        /* Unlock drawing surface */
        SDL_UnlockSurface(drawingSurface);
        /*   Drawing end */

        /*   Swapping buffers */
        /* Scale surface */
        Cana_scalePixels(drawingSurface, windowSurface, KeepRatio_Fit);
        /* Copy window surface to window texture */
        Cana_copyPixels(windowSurface, rendererTexture, screen_width * screen_height);
        /* Swap buffers */
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, rendererTexture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
    
/* Shutdown */
    /* Cleaning */
    SDL_DestroySurface(drawingSurface);
    SDL_DestroySurface(windowSurface);
    SDL_DestroyTexture(rendererTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return SDL_APP_SUCCESS;
}
