//
//  Cana_draw.h
//  Cana
//
//  Created by Stachu on 16.12.2025.
//
#pragma once

struct Cana_Point {
    const int x, y;
    Cana_Point(int x, int y);
};

/**
 * Clear a pixel buffer with a color
 *
 * \param pixels Pixel buffer
 * \param width Buffer width
 * \param height Buffer height
 * \param color Color
 */
void Cana_clear(Uint32* pixels, const int width, const int height, const Uint32 color);
/**
 * Clear a pixel buffer with a color
 *
 * \param pixels Pixel buffer
 * \param length Buffer length (usually width x height)
 * \param color Color
 */
void Cana_clear(Uint32* pixels, const int length, const Uint32 color);

/**
 * Draw a square with a color on a pixel buffer
 *
 * \param pixels Pixel buffer
 * \param width Buffer width
 * \param height Buffer height
 * \param x Square position X (retative to center)
 * \param y Square position Y (retative to center)
 * \param size Side length of the square (in pixels)
 * \param color Color
 */
void Cana_drawSquare(Uint32* pixels, const int width, const int height, const int x, const int y, const int size, const Uint32 color);
/**
 * Draw a square with a color on a pixel buffer
 *
 * \param pixels Pixel buffer
 * \param dimensions Buffer dimensions
 * \param position Square position (relative to center)
 * \param size Side length of the square (in pixels)
 * \param color Color
 */
void Cana_drawSquare(Uint32* pixels, const Cana_Point dimensions, const Cana_Point position, const int size, const Uint32 color);

/**
 * Draw a line from point A to point B with a color on a pixel buffer
 *
 * \param pixels Pixel buffer
 * \param dimensions Buffer dimensions
 * \param pointA Start point
 * \param pointB End point
 * \param color Line color
 */
void Cana_drawLine(Uint32* pixels, const Cana_Point dimensions, const Cana_Point pointA, const Cana_Point pointB, const Uint32 color);
