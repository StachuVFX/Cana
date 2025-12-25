//
//  Cana_structs.h
//  Cana
//
//  Created by Stachu on 22.12.2025.
//

#pragma once

#include <SDL3/SDL.h>

#define SIGN(X) ((X > 0) - (X < 0))
#define MAX(X, Y) (X > Y ? X : Y)

struct Cana_Color
{
    Uint32 black;
    Uint32 white;
    Uint32 red;
    Uint32 green;
    Uint32 blue;
    Uint32 cyan;
    Uint32 magenta;
    Uint32 yellow;
};

struct Cana_Vec2   // change to Cana_Vec2
{
    /* Variables */
    int x, y;
    
    /* Methods */
    Cana_Vec2();
    Cana_Vec2(const int x, const int y);
    
    void set(const int x, const int y);
};
