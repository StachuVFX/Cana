//
//  Cana_structs.h
//  Cana
//
//  Created by Stachu on 22.12.2025.
//

#pragma once

#include <SDL3/SDL.h>

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
/* Int vectors */
/**
 * 2D int vector struct
 */
struct Cana_Vec2_int
{
    /* Variables */
    int x, y;
    
    /* Methods */
    Cana_Vec2_int();
    /**
     * Create a 2D int vector
     */
    Cana_Vec2_int(const int x, const int y);
    
    /**
     * Modify the 2D int vector
     */
    void set(const int x, const int y);
};
/**
 * 3D int vector struct
 */
struct Cana_Vec3_int
{
    /* Variables */
    int x, y, z;
    
    /* Methods */
    Cana_Vec3_int();
    /**
     * Create a 3D int vector
     */
    Cana_Vec3_int(const int x, const int y, const int z);
    
    /**
     * Modify the 3D int vector
     */
    void set(const int x, const int y, const int z);
};

/* Float vectors */
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
     * Modify the 2D vector
     */
    void set(const float x, const float y);
    
    /**
     * Add a 2D vector to this 2D vector
     */
    void add(const Cana_Vec2 vector);
    
    /**
     * Multiply this 2D vector by a constant factor
     */
    void multiply(const float factor);
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
     * Modify the 3D vector
     */
    void set(const float x, const float y, const float z);
    
    /**
     * Add a 3D vector to this 3D vector
     */
    void add(const Cana_Vec3 vector);
    
    /**
     * Multiply this 3D vector by a constant factor
     */
    void multiply(const float factor);
};
