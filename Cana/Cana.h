//
//  Cana.h
//  Cana
//
//  Created by Stachu on 20.12.2025.
//

#pragma once

#include <SDL3/SDL.h>
#include "Cana_draw.h"
#include "Cana_screen.h"

enum WindowType {
    WindowType_Windowed = SDL_WINDOW_RESIZABLE, WindowType_Boderless = SDL_WINDOW_BORDERLESS, WindowType_Fullscreen = SDL_WINDOW_FULLSCREEN
};

class Cana
{
private:
/* Variables */
    /* Window pointers */
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* rendererTexture;
    /* Drawing pointers */
    SDL_Surface* windowSurface;
    SDL_Surface* drawingSurface;
    Uint32* drawingSurface_pixels;
    /* Dimensions */
    Cana_Point screenDimensions;
    Cana_Point drawDimensions;
    /* Other */
    SDL_Event event;
    Cana_Color colors;
public:
    bool running;
public:
    /**
     * Create Cana object
     */
    Cana(const char* program_name, const char* program_version, const char* product_identifier);
    
    /**
     * Create a window
     */
    void createWindow(const char* window_name, const int screen_width, const int screen_height, const WindowType window_type);
    
    /**
     * Create a drawing surface
     */
    void createDrawingSurface(const int surface_width, const int surface_height);
    
    /**
     * Map colors
     *
     * Switch to dictionary asap lmao
     */
    Cana_Color mapColors();
    
    /**
     * Check and handle events
     */
    void checkEvents();
    
    /**
     * Start the drawing process
     */
    void drawingStart();
    
    /**
     * Clear the surface
     */
    void clear(const Uint32 color);
    
    /**
     * Draw a square
     */
    void drawSquare(const Cana_Point position, const int size, const Uint32 color);
    
    /**
     * Draw a line
     */
    void drawLine(const Cana_Point pointA, const Cana_Point pointB, const Uint32 color);
    
    /**
     * Finish the drawing process
     */
    void drawingFinish();
    
    /**
     * Scale the surface
     */
    void scale();
    
    /**
     * Swap the screen
     */
    void swap();
    
    /**
     * Quit and clean up
     */
    void quit();
};
