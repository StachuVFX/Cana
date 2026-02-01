//
//  Cana_objects.h
//  Cana
//
//  Created by Stachu on 29.12.2025.
//

#pragma once

#include "Cana_structs.h"

/* For learning purposes - Interfaces */
    /* Interface - Drawable */
class Example_Drawable {
public:
    virtual void draw() = 0;   // pure virtual function (child classes are forced to implement it)
};
    /* Box clsss - Drawable */
class Example_Box : public Example_Drawable {
public:
    Cana_Vec2 vertices[4] = {Cana_Vec2(-1, -1), Cana_Vec2(1, -1), Cana_Vec2(1, 1), Cana_Vec2(-1, 1)};
    const Cana_Vec3 indices[2] = {Cana_Vec3(1, 2, 3), Cana_Vec3(3, 4, 1)};
    float size = 0.5f;
    
    void draw() override   // has to exist (because it's pure virtual), otherwise class can't be instantiated
    {
        // draw the box
        // (the actual draw function will be in renderer, objects will only need to have an ibo)
    }
};

/**
 * Class for 2D vertex and index arrays
 */
class Cana_VertexArrayObject2 {
/* Member variables */
private:
    /* Constructors */
    Cana_VertexArrayObject2(const int vertexCount, const int indexCount, const int outlineIndexCount);   // not used
    
    Cana_Vec2* m_vertices;
    int m_vertexCount;
    Cana_Vec3_int* m_indices;
    int m_indexCount;
    Cana_Vec2_int* m_outlineIndices;
    int m_outlineIndexCount;
    
/* Methods */
public:
    /* Constructors */
    Cana_VertexArrayObject2();
    /* Destructor */
    ~Cana_VertexArrayObject2();
    
    /* Base */
        /* Init */
    void createArrays(const int vertexCount, const int indexCount, const int outlineIndexCount);
        /* Vertices */
    const Cana_Vec2* getVertices() const;
    const int getVertexCount() const;
    void setVertex(const int vertex_id, const Cana_Vec2 vertex);
        /* Indices */
    const Cana_Vec3_int* getIndices() const;
    const int getIndexCount() const;
    void setIndex(const int index_id, const Cana_Vec3_int index);
        /* Outline indices */
    const Cana_Vec2_int* getOutlineIndices() const;
    const int getOutlineIndexCount() const;
    void setOutlineIndex(const int index_id, const Cana_Vec2_int index);
};

/**
 * 2D drawable class
 *
 * Base class for any drawable 2D object
 *
 * Can't be instantiated
 */
class Cana_Drawable2 {
/* Member variables */
protected:
    /* Constructors */
    Cana_Drawable2();   // can't be instantiated, but child classes can (because it's protected)
    
    /* Base */
        /* VAO */
    Cana_VertexArrayObject2 m_vertexArrayObject;
        /* Appearance */
    Cana_Vec2 m_position;   // 1 unit - 1 meter
    float m_scale;
    
/* Methods */
public:
    /* Base */
        /* VAO */
    const Cana_VertexArrayObject2* getVertexArrayObject() const;
        /* Appearance */
    const Cana_Vec2 getPosition() const;
    const float getScale() const;
};
/**
 * 2D primitive class
 *
 * Base class for Cana\_Object2
 *
 * Extends Cana\_Drawable2 with methods
 */
class Cana_Primitive2 : public Cana_Drawable2 {
/* Member variables */
protected:
    /* Constructors */
    Cana_Primitive2();
    Cana_Primitive2(const Cana_Vec2 position, const float scale);
    
    /* Inherited (from Cana_Drawable2) */   // need to be declared for member initializer list
        /* VAO */
//    Cana_VertexArrayObject2 m_vertexArrayObject;
        /* Appearance */
//    Cana_Vec2 m_position;   // 1 unit - 1 meter
//    float m_scale;
    
/* Methods */
public:
    /* Inherited */
        /* VAO, position and scale (from Cana_Drawable2) */
    const Cana_VertexArrayObject2 getVertexArrayObject() const;
    const Cana_Vec2 getPosition() const;
    const float getScale() const;
    
    /* New */
    void setPosition(const Cana_Vec2 location);
    void changePosition(const Cana_Vec2 vector);
    void setScale(const float scale);
    void changeScale(const float factor);
        /* Vitrual */
    virtual void reset();   // for learning purposes
};
/**
 * 2D static object class
 *
 * Inherits from Cana\_Primitive2
 */
class Cana_Object2 : public Cana_Primitive2 {
/* Member variables */
protected:
    /* Constructors */
        /* Old */
    Cana_Object2();
        /* New */
    Cana_Object2(const Cana_Vec2 position);
    Cana_Object2(const Cana_Vec2 position, const float orientationAngle, const float scale);
    
    /* Inherited (from Cana_Drawable2) */   // need to be declared for member initializer list
//        /* VAO */
//    Cana_VertexArrayObject2 m_vertexArrayObject;
//        /* Appearance */
//    Cana_Vec2 m_position;   // 1 unit - 1 meter
//    float m_scale;
    
    /* New */
    float m_orientationAngle;   // rotation
    
/* Methods */
public:
    /* Inherited */      // (don't need to be declared, but good for readability)
        /* VAO, position and scale (from Cana_Drawable2) */
    const Cana_VertexArrayObject2 getVertexArrayObject() const;
    const Cana_Vec2 getPosition() const;
    const float getScale() const;
        /* Position and scale (from Cana_Primitive2) */
    void setPosition(const Cana_Vec2 location);
    void changePosition(const Cana_Vec2 vector);
    void setScale(const float scale);
    void changeScale(const float factor);
    
    /* Override (from Cana_Primitive2) */
    void reset() override;
    
    /* New */
        /* Orientation (in degrees) */
    const float getOrientationAngle() const;
    void setOrientationAngle(const float angle);
    void changeOrientationAngle(const float angle);
};

/**
 * 2D square class
 *
 * Extends Cana\_Primitive2
 */
class Cana_Square : public Cana_Primitive2 {
/* Member variables */
protected:
    /* Constructors */
    Cana_Square();
    
    /* Inherited (from Cana_Drawable2) */   // need to be declared for member initializer list
        /* VAO */
//    Cana_VertexArrayObject2 m_vertexArrayObject;
        /* Appearance */
//    Cana_Vec2 m_position;   // 1 unit - 1 meter
//    float m_scale;
    
/* Methods */
public:
    /* Constructors */
    Cana_Square(const Cana_Vec2 position, const float scale);
    
    /* Inherited */      // (don't need to be declared, but good for readability)
        /* VAO, position and scale (from Cana_Drawable2) */
    const Cana_VertexArrayObject2 getVertexArrayObject() const;
    const Cana_Vec2 getPosition() const;
    const float getScale() const;
        /* Position and scale (from Cana_Primitive2) */
    void setPosition(const Cana_Vec2 location);
    void changePosition(const Cana_Vec2 vector);
    void setScale(const float scale);
    void changeScale(const float factor);
    
    /* New */
    
    /* Override (from Cana_Primitive2) */
    void reset() override;
};
/**
 * 2D equal-arm triangle class
 *
 * Extends Cana\_Primitive2
 */
class Cana_EqualArmTriangle : public Cana_Primitive2 {
/* Member variables */
protected:
    /* Constructors */
    Cana_EqualArmTriangle();
    
    /* Inherited (from Cana_Drawable2) */   // need to be declared for member initializer list
        /* VAO */
//    Cana_VertexArrayObject2 m_vertexArrayObject;
        /* Appearance */
//    Cana_Vec2 m_position;   // 1 unit - 1 meter
//    float m_scale;
    
/* Methods */
public:
    /* Constructors */
    Cana_EqualArmTriangle(const Cana_Vec2 position, const float scale);
    
    /* Inherited */      // (don't need to be declared, but good for readability)
        /* VAO, position and scale (from Cana_Drawable2) */
    const Cana_VertexArrayObject2 getVertexArrayObject() const;
    const Cana_Vec2 getPosition() const;
    const float getScale() const;
        /* Position and scale (from Cana_Primitive2) */
    void setPosition(const Cana_Vec2 location);
    void changePosition(const Cana_Vec2 vector);
    void setScale(const float scale);
    void changeScale(const float factor);
    
    /* New */
    
    /* Override (from Cana_Primitive2) */
    void reset() override;
};
