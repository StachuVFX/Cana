//
//  Cana_renderer.h
//  Cana
//
//  Created by Stachu on 21.12.2025.
//

#pragma once

#include <SDL3/SDL.h>

#define SIGN(X) ((X > 0) - (X < 0))

struct Cana_Color
{
    Uint32 black;
    Uint32 white;
    Uint32 red;
    Uint32 green;
    Uint32 blue;
    Uint32 cyan;
    Uint32 magenta;
    Uint32 yellow;
};

struct Cana_Point   // change to Cana_Vec2
{
    /* Variables */
    int x, y;
    
    /* Methods */
    Cana_Point();
    Cana_Point(const int x, const int y);
    
    void set(const int x, const int y);
};

class Cana_Renderer
{
    /* Variables */
private:
    Cana_Point drawDimensions;
    int surfaceLength;
public:
    SDL_Surface* drawingSurface;
    Uint32* surfacePixels;   // move to private
    /* Methods */
private:
public:
    /**
     * Create a drawing surface
     *
     * \param surface_width Width of the surface
     * \param surface_height Height of the surface
     */
    void createDrawingSurface(const int surface_width, const int surface_height);
    
    /**
     * Clear a pixel buffer with a color
     *
     * \param color Color to draw with
     */
    void clear(const Uint32 color);

    /**
     * Draw a square with a color on a pixel buffer
     *
     * \param position Position of the square (relative to center)
     * \param size Side length of the square (in pixels)
     * \param color Color
     */
    void drawSquare(const Cana_Point position, const int size, const Uint32 color);

    /**
     * Draw a line from point A to point B with a color on a pixel buffer
     *
     * \param pointA Start point
     * \param pointB End point
     * \param color Line color
     */
    void drawLine(const Cana_Point pointA, const Cana_Point pointB, const Uint32 color);
};
