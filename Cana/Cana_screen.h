//
//  Cana_screen.h
//  Cana
//
//  Created by Stachu on 15.12.2025.
//
#pragma once

enum Cana_KeepRatio
{
    FILL = 0,
    FIT = 1
};

/**
 * Copy pixel data from one pixel buffer to another
 *
 * Only buffers with equal dimensions should be passed as parameters.
 *
 * \param bufferA Source buffer
 * \param bufferB Destination buffer
 * \param length Buffer length (usually width x height)
 */
void Cana_copyPixels(Uint32* bufferA, Uint32* bufferB, const int length);
/**
 * Copy pixel data from an SDL\_Surface to an SDL\_Texture
 *
 * Surface and texture should have equal dimensions.
 *
 * \param surface SDL_Surface (data source)
 * \param texture SDL_Texture (destination)
 * \param length Buffer length (usually width x height)
 */
void Cana_copyPixels(SDL_Surface* surface, SDL_Texture* texture, const int length);

/**
 * Scale one pixel buffer into another
 *
 * \param sourcePixels Buffer to be scaled
 * \param destinationPixels Buffer to scale into
 * \param sourceH Source buffer height
 * \param sourceW Source buffer width
 * \param destinationH Destination buffer height
 * \param destinationW Destination buffer width
 * \param ratio FIT or FILL
 */
void Cana_scalePixels(Uint32* sourcePixels, Uint32* destinationPixels, const int sourceH, const int sourceW, const int destinationH, const int destinationW, const Cana_KeepRatio ratio);
/**
 * Scale an SDL\_Surface into another SDL\_Surface
 *
 * \param source Surface to be scaled
 * \param destination Surface to scale into
 * \param ratio FIT or FILL
 */
void Cana_scalePixels(SDL_Surface* source, SDL_Surface* destination, const Cana_KeepRatio ratio);
