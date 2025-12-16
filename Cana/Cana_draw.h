//
//  Cana_draw.h
//  Cana
//
//  Created by Stachu on 16.12.2025.
//

#ifndef draw_h_
#define draw_h_

struct Cana_Point {
    int x, y;
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
void Cana_clear(Uint32* pixels, int width, int height, Uint32 color);
/**
 * Clear a pixel buffer with a color
 *
 * \param pixels Pixel buffer
 * \param length Buffer length (usually width x height)
 * \param color Color
 */
void Cana_clear(Uint32* pixels, int length, Uint32 color);

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
void Cana_drawSquare(Uint32* pixels, int width, int height, int x, int y, int size, Uint32 color);

/**
 * Draw a line from point A to point B with a color on a pixel buffer
 *
 * \param pixels Pixel buffer
 * \param dimensions Buffer dimensions
 * \param pointA Start point
 * \param pointB End point
 * \param color Line color
 */
void Cana_drawLine(Uint32* pixels, Cana_Point dimensions, Cana_Point pointA, Cana_Point pointB, Uint32 color);

#endif // !draw_h_
