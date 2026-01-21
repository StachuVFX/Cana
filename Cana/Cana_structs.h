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
    
    /**
     * Multiply a 2D vector by a constant factor
     */
    void multiply(const float factor);
};
/**
 * 2D integer vector struct
 */
struct Cana_Vec2_int
{
    /* Variables */
    int x, y;
    
    /* Methods */
    Cana_Vec2_int();
    /**
     * Create a 2D integer vector
     */
    Cana_Vec2_int(const int x, const int y);
    
    /**
     * Modify a 2D integer vector
     */
    void set(const int x, const int y);
};
/**
 * 3D vector struct
 */
struct Cana_Vec3
{
    /* Variables */
    float x, y, z;
    
    /* Methods */
    Cana_Vec3();
    /**
     * Create a 3D vector
     */
    Cana_Vec3(const float x, const float y, const float z);
    
    /**
     * Modify a 3D vector
     */
    void set(const float x, const float y, const float z);
    
    /**
     * Multiply a 3D vector by a constant factor
     */
    void multiply(const float factor);
};
/**
 * 3D integer vector struct
 */
struct Cana_Vec3_int
{
    /* Variables */
    int x, y, z;
    
    /* Methods */
    Cana_Vec3_int();
    /**
     * Create a 3D integer vector
     */
    Cana_Vec3_int(const int x, const int y, const int z);
    
    /**
     * Modify a 3D integer vector
     */
    void set(const int x, const int y, const int z);
};
