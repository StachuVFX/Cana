//
//  Cana_renderer.h
//  Cana
//
//  Created by Stachu on 21.12.2025.
//

#pragma once

#include <SDL3/SDL.h>
#include "Cana_structs.h"

/* Enums */
/**
 * Amount of pixels being drawn in a line
 *
 * Less pixels means length of greater dimension.
 * More pixels means sum of dimension lengths.
 */
enum PixelAmount {
    PixelAmount_LessPixels, PixelAmount_MorePixels
};

/* Cana_Renderer class */
/**
 * Class responsible for rendering
 */
class Cana_Renderer
{
/* Variables */
private:
    int drawWidth;
    int drawHeight;
    int surfaceLength;
    float surfaceRatio;
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
     * Convert Vec2 from unified to direct
     *
     * \param unified 2D vector in unified dimensions
     * \param bufferX Pointer for width in direct dimensions
     * \param bufferY Pointer for height in direct dimensions
     */
    void unified2buffer(const Cana_Vec2 unified, float* bufferX, float* bufferY);

    /**
     * Draw a square with a color on a pixel buffer
     *
     * Int based. Unified dimensions.
     *
     * \param position Position of the square (relative to center)
     * \param size Side length of the square (in pixels)
     * \param color Color
     */
    void drawSquare(const Cana_Vec2 position, const float size, const Uint32 color);

    /**
     * Draw a line from point A to point B with a color on a pixel buffer
     *
     * Int based. Direct dimensions. (size still in pixels)
     *
     * \param pointA Start point
     * \param pointB End point
     * \param color Line color
     * \param pixelAmount Amount of pixels drawn (Less / More)
     */
    void drawLine_direct(const Cana_Vec2 pointA, const Cana_Vec2 pointB, const Uint32 color, PixelAmount pixelAmount);
    /**
     * Draw a line from point A to point B with a color on a pixel buffer
     *
     * Int based. Unified dimensions.
     *
     * \param pointA Start point
     * \param pointB End point
     * \param color Line color
     * \param pixelAmount Amount of pixels drawn (Less / More)
     */
    void drawLine_unified(const Cana_Vec2 pointA, const Cana_Vec2 pointB, const Uint32 color, PixelAmount pixelAmount);
    
//    void drawTriangle(Cana_Vec2 pointA, Cana_Vec2 pointB, Cana_Vec2 pointC, Uint32 color);
    
    /**
     * Quit renderer
     *
     * Clean up renderer memory
     */
    void quit();
};
