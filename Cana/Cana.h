//
//  Cana.h
//  Cana
//
//  Created by Stachu on 20.12.2025.
//

#pragma once

#include <SDL3/SDL.h>
#include "Cana_screen.h"
#include "Cana_renderer.h"

/**
 * Simple 3D CPU renderer
 */
class Cana
{
    /* Variables */
private:
    /* Screen and renderer */
    Cana_Screen screen;
    Cana_Renderer renderer;
    /* Other */
    SDL_Event event;
    Cana_Color colors;
public:
    bool running;
    
    /* Methods */
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
     * Create a renderer
     */
    Cana_Renderer createRenderer(const int surface_width, const int surface_height, const int fov);
    
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
