//
//  Cana_renderer.cpp
//  Cana
//
//  Created by Stachu on 21.12.2025.
//

#include "Cana_renderer.h"

/* Cana_Point */
Cana_Point::Cana_Point() : x(0), y(0) {};
Cana_Point::Cana_Point(const int X, const int Y) : x(X), y(Y) {};

void Cana_Point::set(const int X, const int Y)
{
    this->x = X;
    this->y = Y;
}

/* Cana_Renderer */
void Cana_Renderer::createDrawingSurface(const int surface_width, const int surface_height)
{
    /* Create drawing surface */
    drawDimensions.set(surface_width, surface_height);
    drawingSurface = SDL_CreateSurface(drawDimensions.x, drawDimensions.y, SDL_PIXELFORMAT_ARGB8888);
    /* Prepare pixel buffer pointers for surfaces and texture */
    surfacePixels = (Uint32*)drawingSurface->pixels; /* (assign only to remember how, the surface is not locked anyway) */
    surfaceLength = surface_width * surface_height;
}

void Cana_Renderer::clear(const Uint32 color)
{
    for (int i = 0; i < surfaceLength; i++) {
        surfacePixels[i] = color;
    }
}

void Cana_Renderer::drawSquare(const Cana_Point position, const int size, const Uint32 color)
{
    for (int i = 0; i < size; i++) {
        int targetH = drawDimensions.y / 2 + position.y - (size / 2) + i;
        for (int j = 0; j < size; j++) {
            int targetW = drawDimensions.x / 2 + position.x - (size / 2) + j;
            surfacePixels[targetH * drawDimensions.x + targetW] = color;
        }
    }
}

void Cana_Renderer::drawLine(const Cana_Point pointA, const Cana_Point pointB, const Uint32 color)
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
        surfacePixels[globalH * drawDimensions.x + globalW] = color;
    }
}
