//
//  Cana.cpp
//  Cana
//
//  Created by Stachu on 20.12.2025.
//

#include "Cana.h"

Cana::Cana(const char* program_name, const char* program_version, const char* product_identifier)
{
    /* Set up SDL app metadata */
    SDL_SetAppMetadata(program_name, program_version, product_identifier);
}

void Cana::createWindow(const char* window_name, const int screen_width, const int screen_height, const WindowType window_type)
{
    /* Create SDL window*/
    running = screen.createWindow(window_name, screen_width, screen_height, window_type);
}

Cana_Renderer Cana::createRenderer(const int surface_width, const int surface_height)
{
    /* Create drawing surface */
    renderer.createDrawingSurface(surface_width, surface_height);
    return renderer;
}

Cana_Color Cana::mapColors()
{
    /* Set colors */
    colors.black = SDL_MapRGB(SDL_GetPixelFormatDetails(renderer.drawingSurface->format), NULL, 0, 0, 0);
    colors.white = SDL_MapRGB(SDL_GetPixelFormatDetails(renderer.drawingSurface->format), NULL, 255, 255, 255);
    colors.red = SDL_MapRGB(SDL_GetPixelFormatDetails(renderer.drawingSurface->format), NULL, 255, 0, 0);
    colors.green = SDL_MapRGB(SDL_GetPixelFormatDetails(renderer.drawingSurface->format), NULL, 0, 255, 0);
    colors.blue = SDL_MapRGB(SDL_GetPixelFormatDetails(renderer.drawingSurface->format), NULL, 0, 0, 255);
    colors.cyan = SDL_MapRGB(SDL_GetPixelFormatDetails(renderer.drawingSurface->format), NULL, 0, 255, 255);
    colors.magenta = SDL_MapRGB(SDL_GetPixelFormatDetails(renderer.drawingSurface->format), NULL, 255, 0, 255);
    colors.yellow = SDL_MapRGB(SDL_GetPixelFormatDetails(renderer.drawingSurface->format), NULL, 255, 255, 0);
    
    return colors;
}

void Cana::checkEvents()
{
    /* Poll events */
    while (SDL_PollEvent(&event)) {
        /* Keyboard */
        if (event.type == SDL_EVENT_KEY_DOWN) {
            /* ESC */
            if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                running = false;
                break;
            }
        }
        /* Window resized */
        else if (event.type == SDL_EVENT_WINDOW_RESIZED) {  /* set window texture and surface again */
            screen.resizeScreen();
        }
        /* Window quit */
        else if (event.type == SDL_EVENT_QUIT) {   /* stop the game loop */
            running = false;
            break;
        }
    }
}

void Cana::drawingStart()
{
    /* Start drawing process - Lock drawing surface */
    renderer.drawingStart();
}

void Cana::drawingFinish()
{
    /* Finish drawing process - Unlock drawing surface */
    renderer.drawingFinish();
}

void Cana::scale()
{
    /* Scale drawing surface to window surface */
    screen.scalePixels(renderer.drawingSurface, screen.windowSurface, KeepRatio_Fit);
}

void Cana::swap()
{
    /* Swap screen */
    screen.swap();
}

void Cana::quit()
{
    /* Cleaning */
    renderer.quit();
    screen.quit();
    SDL_Quit();
}
