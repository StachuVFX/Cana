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
    running = screen.createWindow(window_name, screen_width, screen_height, window_type);
}

void Cana::createDrawingSurface(const int surface_width, const int surface_height)
{
    /* Create drawing surface */
    cana_renderer.createDrawingSurface(surface_width, surface_height);
}

Cana_Color Cana::mapColors()
{
    /* Colors */
    colors.black = SDL_MapRGB(SDL_GetPixelFormatDetails(cana_renderer.drawingSurface->format), NULL, 0, 0, 0);
    colors.white = SDL_MapRGB(SDL_GetPixelFormatDetails(cana_renderer.drawingSurface->format), NULL, 255, 255, 255);
    colors.red = SDL_MapRGB(SDL_GetPixelFormatDetails(cana_renderer.drawingSurface->format), NULL, 255, 0, 0);
    colors.green = SDL_MapRGB(SDL_GetPixelFormatDetails(cana_renderer.drawingSurface->format), NULL, 0, 255, 0);
    colors.blue = SDL_MapRGB(SDL_GetPixelFormatDetails(cana_renderer.drawingSurface->format), NULL, 0, 0, 255);
    colors.cyan = SDL_MapRGB(SDL_GetPixelFormatDetails(cana_renderer.drawingSurface->format), NULL, 0, 255, 255);
    colors.magenta = SDL_MapRGB(SDL_GetPixelFormatDetails(cana_renderer.drawingSurface->format), NULL, 255, 0, 255);
    colors.yellow = SDL_MapRGB(SDL_GetPixelFormatDetails(cana_renderer.drawingSurface->format), NULL, 255, 255, 0);
    
    return colors;
}

void Cana::checkEvents()
{
    /* Events */
    while (SDL_PollEvent(&event)) {
        /* Keyboard */
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
                running = false;
                break;
            }
        }
        /* Window resized */
        else if (event.type == SDL_EVENT_WINDOW_RESIZED) {  /* set window texture and surface again */
            SDL_GetWindowSize(screen.window, &screen.screenDimensions.x, &screen.screenDimensions.y);
            SDL_DestroyTexture(screen.rendererTexture);
            screen.rendererTexture = SDL_CreateTexture(screen.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screen.screenDimensions.x, screen.screenDimensions.y);
            SDL_DestroySurface(screen.windowSurface);
            screen.windowSurface = SDL_CreateSurface(screen.screenDimensions.x, screen.screenDimensions.y, SDL_PIXELFORMAT_ARGB8888);
        }
        /* Window quit */
        else if (event.type == SDL_EVENT_QUIT) {   /* stop the game loop */
            running = false;
            break;
        }
    }
}

void Cana::drawingStart()   // move to renderer
{
    /* Lock drawing surface and assign pixel buffer pointer */
    SDL_LockSurface(cana_renderer.drawingSurface);
    cana_renderer.surfacePixels = (Uint32*)cana_renderer.drawingSurface->pixels;
}

void Cana::clear(const Uint32 color)
{
    cana_renderer.clear(color);
}

void Cana::drawSquare(const Cana_Point position, const int size, const Uint32 color)
{
    cana_renderer.drawSquare(position, size, color);
}

void Cana::drawLine(const Cana_Point pointA, const Cana_Point pointB, const Uint32 color)
{
    cana_renderer.drawLine(pointA, pointB, color);
}

void Cana::drawingFinish()
{
    /* Unlock drawing surface */
    SDL_UnlockSurface(cana_renderer.drawingSurface);
}

void Cana::scale()
{
    /* Scale surface */
    screen.scalePixels(cana_renderer.drawingSurface, screen.windowSurface, KeepRatio_Fit);
}

void Cana::swap()
{
    /* Copy window surface to window texture */
    screen.copyPixels(screen.windowSurface, screen.rendererTexture, screen.screenDimensions.x * screen.screenDimensions.y);
    /* Swap buffers */
    SDL_RenderClear(screen.renderer);
    SDL_RenderTexture(screen.renderer, screen.rendererTexture, nullptr, nullptr);
    SDL_RenderPresent(screen.renderer);
}

void Cana::quit()
{
    /* Cleaning */
    SDL_DestroySurface(cana_renderer.drawingSurface);
    SDL_DestroySurface(screen.windowSurface);
    SDL_DestroyTexture(screen.rendererTexture);
    SDL_DestroyRenderer(screen.renderer);
    SDL_DestroyWindow(screen.window);
    SDL_Quit();
}
