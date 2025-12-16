//
//  draw.h
//  SDL Graphics
//
//  Created by Stachu on 15.12.2025.
//

#ifndef draw_h_
#define draw_h_

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

#endif // !draw_h_
