//
//  Cana_screen.h
//  Cana
//
//  Created by Stachu on 15.12.2025.
//

#pragma once

#include <SDL3/SDL.h>
#include "Cana_structs.h"

/* Enums */
/**
 * Windowed / Borderless / Fullscreen
 */
enum WindowType {
    WindowType_Windowed = SDL_WINDOW_RESIZABLE,
    WindowType_Boderless = SDL_WINDOW_BORDERLESS,
    WindowType_Fullscreen = SDL_WINDOW_FULLSCREEN
};
/**
 * Scale fit type
 */
enum KeepRatio
{
    KeepRatio_Fill, KeepRatio_Fit
};

/* Cana_Screen class */
/**
 * Class responsible for window surface, SDL renderer texture, and related functions
 */
class Cana_Screen
{
/* Variables */
private:
public:
    /* Window pointers */
    SDL_Window* window;
    SDL_Renderer* sdl_renderer;
    SDL_Texture* rendererTexture;
    SDL_Surface* windowSurface;
    int windowLength;
    /* Dimensions */
    Cana_Vec2 screenDimensions;
    
/* Methods */
private:
public:
    /**
     * Generate the window
     *
     * \param window_name Name of the window
     * \param screen_width Width of the screen
     * \param screen_height Height of the screen
     * \param window_type Windowed / Borderless / Fullscreen
     */
    bool createWindow(const char* window_name, const int screen_width, const int screen_height, const WindowType window_type);
    
    /**
     * Resize screen to actual window dimensions
     */
    void resizeScreen();
    
    /**
     * Copy pixel data from one pixel buffer to another
     *
     * Only buffers with equal dimensions should be passed as parameters.
     *
     * \param bufferA Source buffer
     * \param bufferB Destination buffer
     * \param length Buffer length (usually width x height)
     */
    void copyPixels(Uint32* bufferA, Uint32* bufferB, const int length);
    /**
     * Copy pixel data from an SDL\_Surface to an SDL\_Texture
     *
     * Surface and texture should have equal dimensions.
     *
     * \param surface SDL_Surface (data source)
     * \param texture SDL_Texture (destination)
     * \param length Buffer length (usually width x height)
     */
    void copyPixels(SDL_Surface* surface, SDL_Texture* texture, const int length);
    
    /**
     * Scale one pixel buffer into another
     *
     * Int based, no float, no blur
     *
     * \param sourcePixels Buffer to be scaled
     * \param destinationPixels Buffer to scale into
     * \param sourceH Source buffer height
     * \param sourceW Source buffer width
     * \param destinationH Destination buffer height
     * \param destinationW Destination buffer width
     * \param ratio FIT or FILL
     */
    void scalePixels(Uint32* sourcePixels, Uint32* destinationPixels, const int sourceH, const int sourceW, const int destinationH, const int destinationW, const KeepRatio ratio);
    /**
     * Scale an SDL\_Surface into another SDL\_Surface
     *
     * Int based, no float, no blur
     *
     * \param source Surface to be scaled
     * \param destination Surface to scale into
     * \param ratio FIT or FILL
     */
    void scalePixels(SDL_Surface* source, SDL_Surface* destination, const KeepRatio ratio);
    
    /**
     * Swap screen
     *
     * Copy pixels from window surface to SDL renderer texture
     */
    void swap();
    
    /**
     * Quit screen
     *
     * Clean up screen memory
     */
    void quit();
};
