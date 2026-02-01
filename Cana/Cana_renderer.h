//
//  Cana_renderer.h
//  Cana
//
//  Created by Stachu on 21.12.2025.
//

#pragma once

#include <SDL3/SDL.h>
#include "Cana_structs.h"
#include "Cana_objects2.h"
#include "Cana_objects3.h"

#include <math.h>

#define PI 3.1415f
#define RAD(DEG) (DEG * PI / 180)

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
    int fov;
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
    void unified2direct(const Cana_Vec2 unified, float* bufferX, float* bufferY);

    /**
     * Draw a square with a color
     *
     * Int based. Unified dimensions.
     *
     * \param position Position of the square (relative to center)
     * \param size Side length of the square (in pixels)
     * \param color Color
     */
    void drawSquare(const Cana_Vec2 position, const float size, const Uint32 color);

    /**
     * Draw a line from point A to point B with a color
     *
     * Int based. Direct dimensions.
     *
     * \param pointA Start point
     * \param pointB End point
     * \param color Line color
     */
    void drawLine_direct(const Cana_Vec2 pointA, const Cana_Vec2 pointB, const Uint32 color, const PixelAmount pixelAmount);
    /**
     * Draw a line from point A to point B with a color
     *
     * Int based. Unified dimensions.
     *
     * \param pointA Start point
     * \param pointB End point
     * \param color Line color
     */
    void drawLine_unified(const Cana_Vec2 pointA, const Cana_Vec2 pointB, const Uint32 color);
    
    /**
     * Draw a triangle between point A, point B and point C with a color
     *
     * Int based. Direct dimensions.
     *
     * Version 2:
     * - lines between two sides
     * - simultanous (starting from one vertex, ending at the other vertices at the same time)
     * - inefficient
     *
     * \param pointA First vertex
     * \param pointB Second veertex
     * \param pointC Third vertex
     * \param color Triangle color
     */
    void drawTriangle_direct(Cana_Vec2 pointA, Cana_Vec2 pointB, Cana_Vec2 pointC, Uint32 color);
    
    /**
     * Draw a triangle between point A, point B and point C with a color
     *
     * Int based. Unified dimensions.
     *
     * \param pointA First vertex
     * \param pointB Second veertex
     * \param pointC Third vertex
     * \param color Triangle color
     */
    void drawTriangle_unified(Cana_Vec2 pointA, Cana_Vec2 pointB, Cana_Vec2 pointC, Uint32 color);
    
    /**
     * Draw an object as triangles
     *
     * \param drawable Cana\_Drawable2 object
     *
     * Drawable has to go by reference, otherwise its destructor will attempt to free VAO twice
     */
    void drawObject_triangles(Cana_Drawable2& drawable, Uint32 color);
    /**
     * Draw an object as lines
     *
     * \param drawable Cana\_Drawable2 object
     *
     * Drawable has to go by reference, otherwise its destructor will attempt to free VAO twice
     */
    void drawObject_lines(Cana_Drawable2& drawable, Uint32 color);
    
    /**
     * Project a 3D vertex onto the screen
     *
     * \param vertex The vertex to be projected
     * \return Point on the screen projected from the vertex
     */
    Cana_Vec2 projectVertex(Cana_Vec3 vertex);
    /**
     * Draw a 3D object as lines
     *
     * \param drawable Cana\_Drawable3 object
     *
     * Drawable has to go by reference, otherwise its destructor will attempt to free VAO twice
     */
    void draw3D_lines(Cana_Drawable3& drawable, Uint32 color);
    
    /**
     * Quit renderer
     *
     * Clean up renderer memory
     */
    void quit();
};
