//
//  Cana_structs.h
//  Cana
//
//  Created by Stachu on 22.12.2025.
//

#pragma once

#include <SDL3/SDL.h>

/* Math defines */
#define SIGN(X) ((X > 0) - (X < 0))
#define MAX(X, Y) (X > Y ? X : Y)

/* Colors */
/**
 * \struct Cana\_Color
 *
 * Temporary struct holding color values
 */
struct Cana_Color
{
    Uint32 black;
    Uint32 gray;
    Uint32 white;
    Uint32 red;
    Uint32 green;
    Uint32 blue;
    Uint32 cyan;
    Uint32 magenta;
    Uint32 yellow;
};

/* Vector structures */
/**
 * 2D vector struct
 */
struct Cana_Vec2
{
    /* Variables */
    float x, y;
    
    /* Methods */
    Cana_Vec2();
    /**
     * Create a 2D vector
     */
    Cana_Vec2(const float x, const float y);
    
    /**
     * Modify a 2D vector
     */
    void set(const float x, const float y);
};
