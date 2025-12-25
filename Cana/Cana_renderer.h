//
//  Cana_renderer.h
//  Cana
//
//  Created by Stachu on 21.12.2025.
//

#pragma once

#include <SDL3/SDL.h>
#include "Cana_structs.h"

enum PixelAmount {
    PixelAmount_LessPixels, PixelAmount_MorePixels
};

int Cana_max(const int a, const int b);

class Cana_Renderer
{
    /* Variables */
private:
    Cana_Vec2 drawDimensions;
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
     * Prepare renderer to start drawing
     *
     * Lock drawing surface
     */
    void drawingStart();
    /**
     * Confirm drawing finish
     *
     * Unlock drawing surface
     */
    void drawingFinish();
    
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
    void drawSquare(const Cana_Vec2 position, const int size, const Uint32 color);

    /**
     * Draw a line from point A to point B with a color on a pixel buffer
     *
     * \param pointA Start point
     * \param pointB End point
     * \param color Line color
     */
    void drawLine(const Cana_Vec2 pointA, const Cana_Vec2 pointB, const Uint32 color, PixelAmount pixelAmount);
    
//    void drawTriangle(Cana_Vec2 pointA, Cana_Vec2 pointB, Cana_Vec2 pointC, Uint32 color);
    
    /**
     * Quit renderer
     *
     * Clean up renderer memory
     */
    void quit();
};
