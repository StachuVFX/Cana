//
//  Cana_renderer.cpp
//  Cana
//
//  Created by Stachu on 21.12.2025.
//

#include "Cana_renderer.h"

#define LINE_PIXEL_AMOUNT PixelAmount_LessPixels

/* Cana_Renderer */
void Cana_Renderer::createDrawingSurface(const int surface_width, const int surface_height)
{
    /* Create drawing surface */
    drawWidth = surface_width;
    drawHeight = surface_height;
    drawingSurface = SDL_CreateSurface(drawWidth, drawHeight, SDL_PIXELFORMAT_ARGB8888);
    /* Prepare pixel buffer pointers for surfaces and texture */
    surfacePixels = (Uint32*)drawingSurface->pixels; /* (assign only to remember how, the surface is not locked anyway) */
    surfaceLength = surface_width * surface_height;
    surfaceRatio = (float)surface_height / (float)surface_width;
}

void Cana_Renderer::drawingStart()
{
    /* Lock drawing surface and assign pixel buffer pointer */
    SDL_LockSurface(drawingSurface);
    surfacePixels = (Uint32*)drawingSurface->pixels;
}

void Cana_Renderer::drawingFinish()
{
    /* Unlock drawing surface */
    SDL_UnlockSurface(drawingSurface);
}

void Cana_Renderer::clear(const Uint32 color)
{
    for (int i = 0; i < surfaceLength; i++) {
        surfacePixels[i] = color;
    }
}

void Cana_Renderer::unified2direct(const Cana_Vec2 unified, float* bufferX, float* bufferY)
{
    /* Can be optimized */
    *bufferX = (float)drawWidth / 2.0 + unified.x * (float)drawWidth / 2.0;
    *bufferY = (float)drawHeight / 2.0 - unified.y * (float)drawWidth / 2.0;
}

void Cana_Renderer::drawSquare(const Cana_Vec2 position, const float size, const Uint32 color)
{
    int directSize = size * (float)drawWidth / 2.0;
    for (int i = 0; i < directSize; i++) {
        int targetH = drawHeight / 2 - position.y - (directSize / 2) + i;
        /* Out of bounds protection (height) */
        if (targetH < 0 || targetH > (drawHeight - 1)) {
            continue;
        }
        for (int j = 0; j < directSize; j++) {
            int targetW = drawWidth / 2 + position.x - (directSize / 2) + j;
            /* Out of bounds protection (width) */
            if (targetW < 0 || targetW > (drawWidth - 1)) {
                continue;
            }
            surfacePixels[targetH * drawWidth + targetW] = color;
        }
    }
}

void Cana_Renderer::drawLine_direct(const Cana_Vec2 pointA, const Cana_Vec2 pointB, const Uint32 color, const PixelAmount pixelAmount)
{
    int lineWidth = pointB.x - pointA.x;
    int widthSign = SIGN(lineWidth);
    lineWidth *= widthSign;
    
    int lineHeight = pointB.y - pointA.y;
    int heightSign = SIGN(lineHeight);
    lineHeight *= heightSign;
    
    int linePixelLength;
    switch (pixelAmount) {
        case PixelAmount_MorePixels:
            linePixelLength = lineWidth + lineHeight;
            break;
        case PixelAmount_LessPixels:
            linePixelLength = MAX(lineWidth, lineHeight);
            break;
        default:
            break;
    }
    for (int i = 0; i < linePixelLength; i++) {
        int localH = lineHeight * i / linePixelLength;
        int localW = lineWidth * i / linePixelLength;
        int globalH = pointA.y + localH * heightSign;
        int globalW = pointA.x + localW * widthSign;
        /* Out of bounds protection */
        if ( ( globalH < 0 || globalH > (drawHeight - 1) ) || ( globalW < 0 || globalW > (drawWidth - 1) ) ) {
            continue;
        }
        /* Drawing pixels */
        surfacePixels[globalH * drawWidth + globalW] = color;
    }
}

void Cana_Renderer::drawLine_unified(const Cana_Vec2 pointA, const Cana_Vec2 pointB, const Uint32 color)
{
    Cana_Vec2 directPointA;
    Cana_Vec2 directPointB;
    
    unified2direct(pointA, &(directPointA.x), &(directPointA.y));
    unified2direct(pointB, &(directPointB.x), &(directPointB.y));
    
    drawLine_direct(directPointA, directPointB, color, LINE_PIXEL_AMOUNT);
}

void Cana_Renderer::drawTriangle_direct(Cana_Vec2 pointA, Cana_Vec2 pointB, Cana_Vec2 pointC, Uint32 color)
{
    /*    Phase 1 - Setup */
    /* Line AB */
    int lineABWidth = pointB.x - pointA.x;
    int widthSignAB = SIGN(lineABWidth);
    lineABWidth *= widthSignAB;
    
    int lineABHeight = pointB.y - pointA.y;
    int heightSignAB = SIGN(lineABHeight);
    lineABHeight *= heightSignAB;
    
    /* Line AC */
    int lineACWidth = pointC.x - pointA.x;
    int widthSignAC = SIGN(lineACWidth);
    lineACWidth *= widthSignAC;
    
    int lineACHeight = pointC.y - pointA.y;
    int heightSignAC = SIGN(lineACHeight);
    lineACHeight *= heightSignAC;
    
    /* Specific pixel amount */
    PixelAmount trianglePixelAmount = PixelAmount_LessPixels;
    
    /* Longer line */
    int linePixelLength;
    switch (trianglePixelAmount) {
        case PixelAmount_MorePixels:
            linePixelLength = MAX(lineABWidth + lineABHeight, lineACWidth + lineACHeight);
            break;
        case PixelAmount_LessPixels:
            linePixelLength = MAX(MAX(lineABWidth, lineABHeight), MAX(lineACWidth, lineACHeight));
            break;
        default:
            break;
    }
    /* Phase 2 - Going through lines */
    for (int i = 0; i < linePixelLength; i++) {
        /* Line AB */
        int localABH = lineABHeight * i / linePixelLength;
        int localABW = lineABWidth * i / linePixelLength;
        int globalABH = pointA.y + localABH * heightSignAB;
        int globalABW = pointA.x + localABW * widthSignAB;
        
        /* Line AC */
        int localACH = lineACHeight * i / linePixelLength;
        int localACW = lineACWidth * i / linePixelLength;
        int globalACH = pointA.y + localACH * heightSignAC;
        int globalACW = pointA.x + localACW * widthSignAC;
        
        /* Drawing lines */
        drawLine_direct(Cana_Vec2(globalABW, globalABH), Cana_Vec2(globalACW, globalACH), color, PixelAmount_MorePixels);
    }
}

void Cana_Renderer::drawTriangle_unified(Cana_Vec2 pointA, Cana_Vec2 pointB, Cana_Vec2 pointC, Uint32 color)
{
    Cana_Vec2 directPointA;
    Cana_Vec2 directPointB;
    Cana_Vec2 directPointC;
    
    unified2direct(pointA, &(directPointA.x), &(directPointA.y));
    unified2direct(pointB, &(directPointB.x), &(directPointB.y));
    unified2direct(pointC, &(directPointC.x), &(directPointC.y));
    
    drawTriangle_direct(directPointA, directPointB, directPointC, color);
}

void Cana_Renderer::quit()
{
    /* Cleaning */
    SDL_DestroySurface(drawingSurface);
}
