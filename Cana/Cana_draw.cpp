//
//  draw.cpp
//  SDL Graphics
//
//  Created by Stachu on 15.12.2025.
//

#include <SDL3/SDL.h>

void Cana_clear(Uint32* pixels, int width, int height, Uint32 color)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixels[i * (width) + j] = color;
        }
    }
}
void Cana_clear(Uint32* pixels, int length, Uint32 color)
{
    for (int i = 0; i < length; i++) {
        pixels[i] = color;
    }
}
