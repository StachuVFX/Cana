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
    WindowType_Windowed, WindowType_Boderless, WindowType_Fullscreen
};

class Cana
{
private:
    Cana_Color colors;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    SDL_Event event;
    bool running;
    
    Cana_Point screenDimensions;
    Cana_Point drawDimensions;
    
    SDL_Texture* rendererTexture;
    SDL_Surface* windowSurface;
    SDL_Surface* drawingSurface;
    Uint32* drawingSurface_pixels;
public:
    Cana(const char* program_name, const char* program_version, const char* product_identifier);
    
    void createWindow(const char* window_name, const int screen_width, const int screen_height, const WindowType window_type);
    
    void createDrawingSurface(const int surface_width, const int surface_height);
    
    /**
     * Map colors
     *
     * Switch to dictionary asap lmao
     */
    Cana_Color mapColors();
    
    void checkEvents();
    
    void drawingStart();
    
    void clear(const Uint32 color);
    
    void drawSquare(const Cana_Point position, const int size, const Uint32 color);
    
    void drawLine(const Cana_Point pointA, const Cana_Point pointB, const Uint32 color);
    
    void drawingStop();
    
    void scale();
    
    void swap();
    
    void quit();
};
