//
//  Cana_screen.cpp
//  Cana
//
//  Created by Stachu on 15.12.2025.
//

#include "Cana_screen.h"

bool Cana_Screen::createWindow(const char* window_name, const int screen_width, const int screen_height, const WindowType window_type)
{
    /* SDL window and renderer setup */
    window = NULL;
    sdl_renderer = NULL;
    /* Check if SDL Video works */
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
//        running = false;
        return false;
    }
    /* Create window and sdl_renderer (sdl_renderer mandatory in SDL3) */
    if (!SDL_CreateWindowAndRenderer("Cana", screen_width, screen_height, SDL_WINDOW_FULLSCREEN, &window, &sdl_renderer)) {
        SDL_Log("Couldn't create a window and sdl_renderer: %s", SDL_GetError());
//        running = false;
        return false;
    }
    /* Create texture for the sdl_renderer and window surface */
    SDL_GetWindowSize(window, &window_width, &window_height);
    rendererTexture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
    windowSurface = SDL_CreateSurface(window_width, window_height, SDL_PIXELFORMAT_ARGB8888);
    windowLength = window_width * window_height;
    
    return true;
}

void Cana_Screen::resizeScreen()
{
    /* Set window texture and surface again */
    SDL_GetWindowSize(window, &window_width, &window_height);
    SDL_DestroyTexture(rendererTexture);
    rendererTexture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
    SDL_DestroySurface(windowSurface);
    windowSurface = SDL_CreateSurface(window_width, window_height, SDL_PIXELFORMAT_ARGB8888);
    windowLength = window_width * window_height;
}

void Cana_Screen::copyPixels(Uint32* bufferA, Uint32* bufferB, const int length)
{
    /* Copy all pixels from bufferA to bufferB */
    for (int i = 0; i < length; i++) {
        bufferB[i] = bufferA[i];
    }
}
void Cana_Screen::copyPixels(SDL_Surface* surface, SDL_Texture* texture, const int length)
{
    /* Copy all pixels from surface to texture */
    /*    Using buffer version of copyPixels */
    SDL_LockSurface(surface);
    Uint32* surfacePixels = (Uint32*)surface->pixels;
    
    Uint32* texturePixels;
    int texturePitch;
    SDL_LockTexture(texture, nullptr, (void**)&texturePixels, &texturePitch);
    
    copyPixels(surfacePixels, texturePixels, length);
    
    SDL_UnlockTexture(texture);
    SDL_UnlockSurface(surface);
}

void Cana_Screen::scalePixels(Uint32* sourcePixels, Uint32* destinationPixels, const int sourceW, const int sourceH, const int destinationW, const int destinationH, const KeepRatio ratio)
{
    /* Scale all pixels from sourcePixels to destinationPixels */
    /*    - int based, no float, no blur */
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
void Cana_Screen::scalePixels(SDL_Surface* source, SDL_Surface* destination, const KeepRatio ratio)
{
    /* Scale all pixels from source surface to destination surface */
    /*    Using buffer version of scalePixels() */
    SDL_LockSurface(source);
    SDL_LockSurface(destination);

    scalePixels((Uint32*)source->pixels, (Uint32*)destination->pixels, source->w, source->h, destination->w, destination->h, ratio);
    
    SDL_UnlockSurface(source);
    SDL_UnlockSurface(destination);
}

void Cana_Screen::swap()
{
    /* Copy window surface to window texture */
    copyPixels(windowSurface, rendererTexture, windowLength);
    /* Swap screen (render texture and present it) */
    SDL_RenderClear(sdl_renderer);
    SDL_RenderTexture(sdl_renderer, rendererTexture, nullptr, nullptr);
    SDL_RenderPresent(sdl_renderer);
}

void Cana_Screen::quit()
{
    /* Cleaning */
    SDL_DestroySurface(windowSurface);
    SDL_DestroyTexture(rendererTexture);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(window);
}
