//
//  Cana.h
//  Cana
//
//  Created by Stachu on 20.12.2025.
//

#pragma once

#include <SDL3/SDL.h>

enum WindowType {
    WindowType_Windowed, WindowType_Boderless, WindowType_Fullscreen
};

enum Cana_KeepRatio
{
    KeepRatio_Fill, KeepRatio_Fit
};

struct Cana_Color {
public:
    Uint32 black;
    Uint32 white;
    Uint32 red;
    Uint32 green;
    Uint32 blue;
    Uint32 cyan;
    Uint32 magenta;
    Uint32 yellow;
};

struct Cana_Point
{
public:
    int x, y;
public:
    Cana_Point();
    Cana_Point(const int x, const int y);
    
    void set(const int x, const int y);
};

class Cana
{
private:
    Cana_Color colors;
    
    static SDL_Window* window;
    static SDL_Renderer* renderer;
    
    static SDL_Event event;
    static bool running;
    
    Cana_Point screenDimensions;
    static Cana_Point drawDimensions;
    
    static SDL_Texture* rendererTexture;
    static SDL_Surface* windowSurface;
    static SDL_Surface* drawingSurface;
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
    
    void clear(const Cana_Color color);
    
    void drawSquare(const Cana_Point position, const int size, const Uint32 color);
    
    void drawLine(const Cana_Point pointA, const Cana_Point pointB, const Uint32 color);
    
    void drawingStop();
    
    void scale();
    
    void swap();
    
    void quit();
};
