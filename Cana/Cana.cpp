//
//  Cana.cpp
//  Cana
//
//  Created by Stachu on 20.12.2025.
//

#include "Cana.h"

Cana::Cana(const char* program_name, const char* program_version, const char* product_identifier)
{
    /* Set up app metadata */
    SDL_SetAppMetadata(program_name, program_version, product_identifier);
}

void Cana::createWindow(const char* window_name, const int screen_width, const int screen_height, const WindowType window_type)
{
    window = NULL;
    renderer = NULL;
    running = true;
    /* Check if SDL Video works */
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
//        return SDL_APP_FAILURE;
        running = false;
    }
    /* Create window and renderer (renderer mandatory in SDL3) */
    if (!SDL_CreateWindowAndRenderer("Cana", screen_width, screen_height, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create a window and renderer: %s", SDL_GetError());
//        return SDL_APP_FAILURE;
        running = false;
    }
    SDL_GetWindowSize(window, &screenDimensions.x, &screenDimensions.y);
    rendererTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screenDimensions.x, screenDimensions.y);
}

void Cana::createDrawingSurface(const int surface_width, const int surface_height)
{
    drawDimensions.set(surface_width, surface_height);
    windowSurface = SDL_CreateSurface(screenDimensions.x, screenDimensions.y, SDL_PIXELFORMAT_ARGB8888);
    drawingSurface = SDL_CreateSurface(drawDimensions.x, drawDimensions.y, SDL_PIXELFORMAT_ARGB8888);
    drawingSurface_pixels = (Uint32*)drawingSurface->pixels;
}

Cana_Color Cana::mapColors()
{
    colors.black = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 0, 0, 0);
    colors.white = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 255, 255, 255);
    colors.red = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 255, 0, 0);
    colors.green = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 0, 255, 0);
    colors.blue = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 0, 0, 255);
    colors.cyan = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 0, 255, 255);
    colors.magenta = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 255, 0, 255);
    colors.yellow = SDL_MapRGB(SDL_GetPixelFormatDetails(drawingSurface->format), NULL, 255, 255, 0);
    
    return colors;
}

void Cana::checkEvents()
{
    while (SDL_PollEvent(&event)) {
        /* Keyboard */
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                running = false;
            }
        }
        /* Window resized */
        else if (event.type == SDL_EVENT_WINDOW_RESIZED) {  /* set window texture and surface again */
            SDL_GetWindowSize(window, &screenDimensions.x, &screenDimensions.y);
            SDL_DestroyTexture(rendererTexture);
            rendererTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screenDimensions.x, screenDimensions.y);
            SDL_DestroySurface(windowSurface);
            windowSurface = SDL_CreateSurface(screenDimensions.x, screenDimensions.y, SDL_PIXELFORMAT_ARGB8888);
        }
        /* Window quit */
        else if (event.type == SDL_EVENT_QUIT) {   /* stop the game loop */
            running = false;
        }
    }
}

void Cana::drawingStart()
{
    SDL_LockSurface(drawingSurface);
    drawingSurface_pixels = (Uint32*)drawingSurface->pixels;
}

void Cana::clear(const Uint32 color)
{
    Cana_clear(drawingSurface_pixels, drawDimensions.x * drawDimensions.y, color);
}

void Cana::drawSquare(const Cana_Point position, const int size, const Uint32 color)
{
    Cana_drawSquare(drawingSurface_pixels, drawDimensions.x, drawDimensions.y, position.x, position.y, size, color);
}

void Cana::drawLine(const Cana_Point pointA, const Cana_Point pointB, const Uint32 color)
{
    Cana_drawLine(drawingSurface_pixels, drawDimensions, pointA, pointB, color);
}

void Cana::drawingStop()
{
    SDL_UnlockSurface(drawingSurface);
}

void Cana::scale()
{
    Cana_scalePixels(drawingSurface, windowSurface, KeepRatio_Fit);
}

void Cana::swap()
{
    /* Copy window surface to window texture */
    Cana_copyPixels(windowSurface, rendererTexture, screenDimensions.x * screenDimensions.y);
    /* Swap buffers */
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, rendererTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Cana::quit()
{
    /* Cleaning */
    SDL_DestroySurface(drawingSurface);
    SDL_DestroySurface(windowSurface);
    SDL_DestroyTexture(rendererTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
