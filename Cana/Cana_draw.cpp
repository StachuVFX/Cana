//
//  Cana_draw.cpp
//  Cana
//
//  Created by Stachu on 16.12.2025.
//

#include <SDL3/SDL.h>
#include "Cana_draw.h"

#define SIGN(X) ((X > 0) - (X < 0))

Cana_Point::Cana_Point(int x, int y) : x(x), y(y) {};

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

void Cana_drawSquare(Uint32* pixels, int width, int height, int x, int y, int size, Uint32 color)
{
    for (int i = 0; i < size; i++) {
        int targetH = height / 2 + y - (size / 2) + i;
        for (int j = 0; j < size; j++) {
            int targetW = width / 2 + x - (size / 2) + j;
            pixels[targetH * width + targetW] = color;
        }
    }
}
void Cana_drawSquare(Uint32* pixels, Cana_Point dimensions, Cana_Point position, int size, Uint32 color)
{
    for (int i = 0; i < size; i++) {
        int targetH = dimensions.y / 2 + position.y - (size / 2) + i;
        for (int j = 0; j < size; j++) {
            int targetW = dimensions.x / 2 + position.x - (size / 2) + j;
            pixels[targetH * dimensions.x + targetW] = color;
        }
    }
}

void Cana_drawLine(Uint32* pixels, Cana_Point dimensions, Cana_Point pointA, Cana_Point pointB, Uint32 color)
{
    int lineWidth = pointB.x - pointA.x;
    int widthSign = SIGN(lineWidth);
    lineWidth *= widthSign;
    
    int lineHeight = pointB.y - pointA.y;
    int heightSign = SIGN(lineHeight);
    lineHeight *= heightSign;
    
    int linePixelLength = lineWidth + lineHeight;
    for (int i = 0; i < linePixelLength; i++) {
        int localH = lineHeight * i / linePixelLength;
        int localW = lineWidth * i / linePixelLength;
        int globalH = pointA.y + localH * heightSign;
        int globalW = pointA.x + localW * widthSign;
        pixels[globalH * dimensions.x + globalW] = color;
    }
}
