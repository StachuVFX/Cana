//
//  Cana_renderer.cpp
//  Cana
//
//  Created by Stachu on 21.12.2025.
//

#include "Cana_renderer.h"
#include "Cana_math.h"

#define LINE_PIXEL_AMOUNT PixelAmount_LessPixels
#define TRIANGLE_PIXEL_AMOUNT PixelAmount_LessPixels
#define FOV 90

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
    /* Set up 3D */
    fov = FOV;
    zV = -1 / SDL_tanf(RAD(fov / 2.0f));
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
    *bufferX = ((float)drawWidth + unified.x * (float)drawWidth) / 2.0f;
    *bufferY = ((float)drawHeight - unified.y * (float)drawWidth) / 2.0f;
}

Cana_Vec2 Cana_Renderer::project3D(const Cana_Vec3 point_3D)
{
    Cana_Vec2 point_2D;
    
    point_2D.x = (-zV * point_3D.x) / (point_3D.z - zV);
    point_2D.y = (-zV * point_3D.y) / (point_3D.z - zV);
    
    return point_2D;
}

void Cana_Renderer::drawPixel(const Cana_Vec2 position, const Uint32 color)
{
    int targetH = SDL_floorf(((float)drawHeight - position.y * (float)drawWidth) / 2.0f); // floor somehow fixes point-line missmatch lol
    int targetW = SDL_floorf(((float)drawWidth + position.x * (float)drawWidth) / 2.0f);
    /* Out of bounds protection */
    if (targetH < 0 || targetH > (drawHeight - 1) || targetW < 0 || targetW > (drawWidth - 1)) {
        return;
    }
    surfacePixels[targetH * drawWidth + targetW] = color;
}

void Cana_Renderer::drawSquare(const Cana_Vec2 position, const float size, const Uint32 color)
{
    float directSize = size * (float)drawWidth / 2.0f;
    for (int i = 0; i < directSize; i++) {
        int targetH = SDL_floorf(((float)drawHeight - position.y * (float)drawWidth - directSize) / 2.0f + (float)i);
        /* Out of bounds protection (height) */
        if (targetH < 0 || targetH > (drawHeight - 1)) {
            continue;
        }
        for (int j = 0; j < directSize; j++) {
            int targetW = SDL_floorf(((float)drawWidth + position.x * (float)drawWidth - directSize) / 2.0f + (float)j);
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
    float lineWidth = pointB.x - pointA.x;
    float widthSign = SIGN(lineWidth);
    lineWidth *= widthSign;
    
    float lineHeight = pointB.y - pointA.y;
    float heightSign = SIGN(lineHeight);
    lineHeight *= heightSign;
    
    float linePixelLength;
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
        float localH = SDL_roundf(lineHeight * (float)i / linePixelLength);
        float localW = SDL_roundf(lineWidth * (float)i / linePixelLength);
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

void Cana_Renderer::drawTriangle_direct(const Cana_Vec2 pointA, const Cana_Vec2 pointB, const Cana_Vec2 pointC, const Uint32 color)
{
    /*    Phase 1 - Setup */
    /* Line AB */
    float lineABWidth = pointB.x - pointA.x;
    float widthSignAB = SIGN(lineABWidth);
    lineABWidth *= widthSignAB;
    
    float lineABHeight = pointB.y - pointA.y;
    float heightSignAB = SIGN(lineABHeight);
    lineABHeight *= heightSignAB;
    
    /* Line AC */
    float lineACWidth = pointC.x - pointA.x;
    float widthSignAC = SIGN(lineACWidth);
    lineACWidth *= widthSignAC;
    
    float lineACHeight = pointC.y - pointA.y;
    float heightSignAC = SIGN(lineACHeight);
    lineACHeight *= heightSignAC;
    
    /* Specific pixel amount */
    PixelAmount trianglePixelAmount = TRIANGLE_PIXEL_AMOUNT;
    
    /* Longer line */
    float linePixelLength;
    switch (trianglePixelAmount) {
        case PixelAmount_LessPixels:
            linePixelLength = MAX(MAX(lineABWidth, lineABHeight), MAX(lineACWidth, lineACHeight));
            break;
        case PixelAmount_MorePixels:
            linePixelLength = MAX(lineABWidth + lineABHeight, lineACWidth + lineACHeight);
            break;
        default:
            break;
    }
    /* Phase 2 - Going through lines */
    for (int i = 0; i < linePixelLength; i++) {
        /* Line AB */
        float localABH = SDL_roundf(lineABHeight * (float)i / linePixelLength);
        float localABW = SDL_roundf(lineABWidth * (float)i / linePixelLength);
        int globalABH = pointA.y + localABH * heightSignAB;
        int globalABW = pointA.x + localABW * widthSignAB;
        
        /* Line AC */
        float localACH = SDL_roundf(lineACHeight * (float)i / linePixelLength);
        float localACW = SDL_roundf(lineACWidth * (float)i / linePixelLength);
        int globalACH = pointA.y + localACH * heightSignAC;
        int globalACW = pointA.x + localACW * widthSignAC;
        
        /* Drawing lines */
        drawLine_direct(Cana_Vec2(globalABW, globalABH), Cana_Vec2(globalACW, globalACH), color, PixelAmount_MorePixels);
    }
}

void Cana_Renderer::drawTriangle_unified(const Cana_Vec2 pointA, const Cana_Vec2 pointB, const Cana_Vec2 pointC, const Uint32 color)
{
    Cana_Vec2 directPointA;
    Cana_Vec2 directPointB;
    Cana_Vec2 directPointC;
    
    unified2direct(pointA, &(directPointA.x), &(directPointA.y));
    unified2direct(pointB, &(directPointB.x), &(directPointB.y));
    unified2direct(pointC, &(directPointC.x), &(directPointC.y));
    
    drawTriangle_direct(directPointA, directPointB, directPointC, color);
}

void Cana_Renderer::drawPoint_3D(const Cana_Vec3 point3D, const float size, const Uint32 color)
{
    Cana_Vec2 point2D;
    point2D.x = (-zV * point3D.x) / (point3D.z - zV);
    point2D.y = (-zV * point3D.y) / (point3D.z - zV);
    
//    drawSquare(point2D, size, color);
    drawPixel(point2D, color);
}

void Cana_Renderer::drawLine_3D(const Cana_Vec3 pointA_3D, const Cana_Vec3 pointB_3D, const Uint32 color)
{
    Cana_Vec2 pointA_2D = project3D(pointA_3D);
    Cana_Vec2 pointB_2D = project3D(pointB_3D);
    
    drawLine_unified(pointA_2D, pointB_2D, color);
}

void Cana_Renderer::drawTriangle_3D(const Cana_Vec3 pointA_3D, const Cana_Vec3 pointB_3D, const Cana_Vec3 pointC_3D, const Uint32 color)
{
    Cana_Vec2 pointA_2D = project3D(pointA_3D);
    Cana_Vec2 pointB_2D = project3D(pointB_3D);
    Cana_Vec2 pointC_2D = project3D(pointC_3D);
    
    drawTriangle_unified(pointA_2D, pointB_2D, pointC_2D, color);
}

void Cana_Renderer::quit()
{
    /* Cleaning */
    SDL_DestroySurface(drawingSurface);
}
