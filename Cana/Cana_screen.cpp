//
//  Cana_screen.cpp
//  Cana
//
//  Created by Stachu on 15.12.2025.
//

#include <SDL3/SDL.h>
#include "Cana_screen.h"

void Cana_copyPixels(Uint32* bufferA, Uint32* bufferB, const int length)
{
    for (int i = 0; i < length; i++) {
        bufferB[i] = bufferA[i];
    }
}
void Cana_copyPixels(SDL_Surface* surface, SDL_Texture* texture, const int length)
{
    SDL_LockSurface(surface);
    Uint32* surfacePixels = (Uint32*)surface->pixels;
    
    Uint32* texturePixels;
    int texturePitch;
    SDL_LockTexture(texture, nullptr, (void**)&texturePixels, &texturePitch);
    
//    Cana_copyPixels(surfacePixels, texturePixels, length);
    for (int i = 0; i < length; i++) {
        texturePixels[i] = surfacePixels[i];
    }
    
    SDL_UnlockTexture(texture);
    SDL_UnlockSurface(surface);
}

void Cana_scalePixels(Uint32* sourcePixels, Uint32* destinationPixels, const int sourceH, const int sourceW, const int destinationH, const int destinationW, const Cana_KeepRatio ratio)
{
    int fitToHeight = 1;
//    float sh = (float)sourceH;
//    float dh = (float)destinationH;
//    float sw = (float)sourceW;
//    float dw = (float)destinationW;
    float hScale = (float)sourceH / (float)destinationH;
    float wScale = (float)sourceW / (float)destinationW;
    switch (ratio)
    {
    case KeepRatio_Fit:
        if (wScale > hScale) {
            fitToHeight = 0;
        }
                // probably can be optimized
        switch (fitToHeight)
        {
        case 1:
            for (int i = 0; i < destinationH; i++) {
                for (int j = 0; j < destinationW * (wScale / hScale); j++) {
                    int targetH = i * hScale;
                    int wShift = (1 - (wScale / hScale)) * destinationW / 2;
                    int targetW = j * hScale;
                    destinationPixels[i * destinationW + j + wShift] = sourcePixels[targetH * sourceW + targetW];
                }
            }
            break;
        case 0:
            for (int i = 0; i < destinationH * (hScale / wScale); i++) {
                for (int j = 0; j < destinationW; j++) {
                    int targetH = i * wScale;
                    int hShift = (1 - (hScale / wScale)) * destinationH / 2;
                    int targetW = j * wScale;
                    destinationPixels[(i + hShift) * destinationW + j] = sourcePixels[targetH * sourceW + targetW];
                }
            }
            break;
        default:
            break;
        }
        break;
    case KeepRatio_Fill:
                    // can be optimized
        for (int  i = 0; i < destinationH; i++) {
            for (int j = 0; j < destinationW; j++) {
                float hScale = (float)sourceH / (float)destinationH;
                float wScale = (float)sourceW / (float)destinationW;
                int targetH = i * hScale;
                int targetW = j * wScale;
                destinationPixels[i * destinationW + j] = sourcePixels[targetH * sourceW + targetW];
            }
        }
        break;
    default:
        break;
    }
}
void Cana_scalePixels(SDL_Surface* source, SDL_Surface* destination, const Cana_KeepRatio ratio)
{
    SDL_LockSurface(source);
    SDL_LockSurface(destination);

    Uint32* sourcePixels = (Uint32*)source->pixels;
    Uint32* destinationPixels = (Uint32*)destination->pixels;

    int fitToHeight = 1;
//    float sh = (float)source->h;
//    float dh = (float)destination->h;
//    float sw = (float)source->w;
//    float dw = (float)destination->w;
    float hScale = (float)source->h / (float)destination->h;
    float wScale = (float)source->w / (float)destination->w;
    switch (ratio)
    {
    case KeepRatio_Fit:
        if (wScale > hScale) {
            fitToHeight = 0;
        }
                // probably can be optimized
        switch (fitToHeight)
        {
        case 1:
            for (int i = 0; i < destination->h; i++) {
                for (int j = 0; j < destination->w * (wScale / hScale); j++) {
                    int targetH = i * hScale;
                    int wShift = (1 - (wScale / hScale)) * destination->w / 2;
                    int targetW = j * hScale;
                    destinationPixels[i * destination->w + j + wShift] = sourcePixels[targetH * source->w + targetW];
                }
            }
            break;
        case 0:
            for (int i = 0; i < destination->h * (hScale / wScale); i++) {
                for (int j = 0; j < destination->w; j++) {
                    int targetH = i * wScale;
                    int hShift = (1 - (hScale / wScale)) * destination->h / 2;
                    int targetW = j * wScale;
                    destinationPixels[(i + hShift) * destination->w + j] = sourcePixels[targetH * source->w + targetW];
                }
            }
            break;
        default:
            break;
        }
        break;
    case KeepRatio_Fill:
                    // can be optimized
        for (int  i = 0; i < destination->h; i++) {
            for (int j = 0; j < destination->w; j++) {
                float hScale = (float)source->h / (float)destination->h;
                float wScale = (float)source->w / (float)destination->w;
                int targetH = i * hScale;
                int targetW = j * wScale;
                destinationPixels[i * destination->w + j] = sourcePixels[targetH * source->w + targetW];
            }
        }
        break;
    default:
        break;
    }

    SDL_UnlockSurface(source);
    SDL_UnlockSurface(destination);
}
